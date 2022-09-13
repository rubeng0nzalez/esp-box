/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/



/****************************************************************************
*
* This demo showcases BLE GATT client. It can scan BLE devices and connect to one device.
* Run the gatt_server demo, the client demo will automatically connect to the gatt_server demo.
* Client demo will enable gatt_server's notify after connection. The two devices will then exchange
* data.
*
****************************************************************************/

#include <time.h>//RG:USED TO PRINT TIMESTAMP

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gattc_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GATTC_TAG "GATTC_DEMO"
#define REMOTE_SERVICE_UUID        0x00FF //RG:IMPORTANT - SERVICE UUID OF THE SERVER THAT CLIENT IS INTERESTED IN
#define REMOTE_NOTIFY_CHAR_UUID    0xFF01 //RG:IMPORTANT - CHARACTERISTIC UUID OF THE SERVER THAT CLIENT IS INTERESTED IN
#define PROFILE_NUM      1
#define PROFILE_A_APP_ID 0
#define INVALID_HANDLE   0

static const char remote_device_name[] = "ESP_GATTS_DEMO"; //RG:IMPORTANT - NAME OF THE SERVER THAT CLIENT IS INTERESTED IN
static bool connect    = false;
static bool get_server = false;		//RG:FLAG TO KNOW IF SERVER HAS BEEN GOTTEN
static esp_gattc_char_elem_t *char_elem_result   = NULL; //RG:CHARACTERISTIC ELEMENT
static esp_gattc_descr_elem_t *descr_elem_result = NULL; //RG:DESCRIPTION ELEMENT

/* Declare static functions */
//static void Timestamp();
static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);
static void gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);

static esp_bt_uuid_t remote_filter_service_uuid = {
    .len = ESP_UUID_LEN_16,
    .uuid = {.uuid16 = REMOTE_SERVICE_UUID,},
};

static esp_bt_uuid_t remote_filter_char_uuid = {
    .len = ESP_UUID_LEN_16,
    .uuid = {.uuid16 = REMOTE_NOTIFY_CHAR_UUID,},
};

static esp_bt_uuid_t notify_descr_uuid = {
    .len = ESP_UUID_LEN_16,
    .uuid = {.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG,},//RG:THERE ARE MANY CHARACTERISTIC DESCRIPTORS DEFINED IN THE
														//BLUETOOTH SPECIFICATION. HOWEVER, IN THIS CASE WE ARE INTERESTED
														//IN WRITING TO THE DESCRIPTOR THAT DEALS WITH ENABLING NOTIFICATIONS,
														//WHICH IS CLIENT CONFIGURATION DESCRIPTOR
};

static esp_ble_scan_params_t ble_scan_params = {
    .scan_type              = BLE_SCAN_TYPE_ACTIVE,//RG:SCAN TYPE
    .own_addr_type          = BLE_ADDR_TYPE_PUBLIC,//RG:OWNER ADDRESS TYPE
    .scan_filter_policy     = BLE_SCAN_FILTER_ALLOW_ALL,//RG:SCAN FILTER POLICY
    .scan_interval          = 0x50,//RG:THIS IS DEFINED AS THE TIME INTERVAL FROM WHEN THE CONTROLLER
								   //RG:STARTED ITS LAST LE SCAN
								   //RG:UNTIL IT BEGINS THE SUBSEQUENT LE SCAN
								   //RG:DEFAULT : 0x0050 (120 MS)
								   //RG:TIME = N * 1.25 MSEC
								   //RG:TIME RANGE: 2.5 MSEC to 10.24 SECONDS
    .scan_window            = 0x30,//RG:THE DURATION OF THE LE SCAN
    .scan_duplicate         = BLE_SCAN_DUPLICATE_DISABLE
};

struct gattc_profile_inst {
    esp_gattc_cb_t gattc_cb;//RG:CALLBACK PARAMETER
    uint16_t gattc_if;//RG: GATT SERVER INTERFACE
    uint16_t app_id;//RG: GATT APP ID
    uint16_t conn_id;//RG: GATT CONNECTION ID
    uint16_t service_start_handle;
    uint16_t service_end_handle;
    uint16_t char_handle;//RG:CHARACTERISTIC HANDLER
    esp_bd_addr_t remote_bda;//RG: REMOTE DEVICE ADDRESS CONNECTED TO THIS CLIENT (BDA BLUETOOTH DEVICE ADDRESS)
};

/* One gatt-based profile one app_id and one gattc_if, this array will store the gattc_if returned by ESP_GATTS_REG_EVT */
static struct gattc_profile_inst gl_profile_tab[PROFILE_NUM] = {
    [PROFILE_A_APP_ID] = {
        .gattc_cb = gattc_profile_event_handler,
        .gattc_if = ESP_GATT_IF_NONE,       /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
    },
};

static void gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
    esp_ble_gattc_cb_param_t *p_data = (esp_ble_gattc_cb_param_t *)param;

    switch (event) {
    case ESP_GATTC_REG_EVT://RG:ONCE THE PROFILE REGISTRATION IS COMPLETED, TRIGGERS AN ESP_GATTC_REG_EVT EVENT

    	ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_REG_EVT SUCCESS");
        esp_err_t scan_ret = esp_ble_gap_set_scan_params(&ble_scan_params);//RG:SET THE SCAN PARAMETERS
        if (scan_ret){//RG:IF THERE IS AN ERROR
            ESP_LOGE(GATTC_TAG, "set scan params error, error code = %x", scan_ret);
        }
        break;

    case ESP_GATTC_CONNECT_EVT:{//RG:AFTER OPENING THE CONNECTION, AN ESP_GATTC_CONNECT_EVT IS TRIGGERED

    	ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_CONNECT_EVT conn_id %d, if %d", p_data->connect.conn_id, gattc_if);
        //RG:THE CONNECTION ID AND THE ADDRESS OF THE SERVER ARE STORED IN THE APPLICATION PROFILE TABLE
        gl_profile_tab[PROFILE_A_APP_ID].conn_id = p_data->connect.conn_id;
        memcpy(gl_profile_tab[PROFILE_A_APP_ID].remote_bda, p_data->connect.remote_bda, sizeof(esp_bd_addr_t));

        ESP_LOGI(GATTC_TAG, "GATT PROFILE - REMOTE BDA (BLUETOOTH DEVICE ADDRESS):");
        esp_log_buffer_hex(GATTC_TAG, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, sizeof(esp_bd_addr_t));

        esp_err_t mtu_ret = esp_ble_gattc_send_mtu_req (gattc_if, p_data->connect.conn_id);//RG:SENDS THE MTU CONFIGURATION

        //RG:IN CASE THE MTU CONFIGURATION FAILS
        if (mtu_ret){
            ESP_LOGE(GATTC_TAG, "Error, when config MTU, error code = %x", mtu_ret);
        }
        break;
    }
    case ESP_GATTC_OPEN_EVT:
        if (param->open.status != ESP_GATT_OK){//RG:IF ERRORS OCCURRED
            ESP_LOGE(GATTC_TAG, "Error, when open failed, status %d", p_data->open.status);
            break;
        }

        ESP_LOGI(GATTC_TAG, "GATT PROFILE - (ESP_GATTC_OPEN_EVT) open success");
        break;
    case ESP_GATTC_DIS_SRVC_CMPL_EVT://EVENT TRIGGERED WHEN DISCOVERY SERVICE IS COMPLETED
        if (param->dis_srvc_cmpl.status != ESP_GATT_OK){//RG:IF ERRORS OCCURRED
            ESP_LOGE(GATTC_TAG, "Error, when discover service failed, status %d", param->dis_srvc_cmpl.status);
            break;
        }

        ESP_LOGI(GATTC_TAG, "GATT PROFILE - (ESP_GATTC_DIS_SRVC_CMPL_EVT) Discover service complete conn_id %d", param->dis_srvc_cmpl.conn_id);
        esp_ble_gattc_search_service(gattc_if, param->cfg_mtu.conn_id, &remote_filter_service_uuid);
        break;
    case ESP_GATTC_CFG_MTU_EVT:
        if (param->cfg_mtu.status != ESP_GATT_OK){//RG:IF ERRORS OCCURRED
            ESP_LOGE(GATTC_TAG,"Error, when config mtu failed, error status = %x", param->cfg_mtu.status);
        }
        ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_CFG_MTU_EVT, Status %d, MTU %d, conn_id %d", param->cfg_mtu.status, param->cfg_mtu.mtu, param->cfg_mtu.conn_id);
        break;
    case ESP_GATTC_SEARCH_RES_EVT: {//RG:EVENT TRIGGERED WHEN SERVICE FOUND

    	ESP_LOGI(GATTC_TAG, "GATT PROFILE - (ESP_GATTC_SEARCH_RES_EVT) SEARCH RES: conn_id = %x is primary service %d", p_data->search_res.conn_id, p_data->search_res.is_primary);
        ESP_LOGI(GATTC_TAG, "GATT PROFILE - (ESP_GATTC_SEARCH_RES_EVT) Start handle %d end handle %d current handle value %d", p_data->search_res.start_handle, p_data->search_res.end_handle, p_data->search_res.srvc_id.inst_id);
        //RG:IF THE SERVICE IS THE ONE WE ARE LOOKING FOR
        if (p_data->search_res.srvc_id.uuid.len == ESP_UUID_LEN_16 && p_data->search_res.srvc_id.uuid.uuid.uuid16 == REMOTE_SERVICE_UUID) {
            ESP_LOGI(GATTC_TAG, "GATT PROFILE - (ESP_GATTC_SEARCH_RES_EVT) Service found");
            get_server = true;//RG:THE SERVER FOUND FLAG IS RAISED
            //RG:HANDLES ARE SAVED TO BE USED TO GET ALL THE CHARACTERISTICS
            gl_profile_tab[PROFILE_A_APP_ID].service_start_handle = p_data->search_res.start_handle;
            gl_profile_tab[PROFILE_A_APP_ID].service_end_handle = p_data->search_res.end_handle;
            ESP_LOGI(GATTC_TAG, "GATT PROFILE - Service UUID16: %x", p_data->search_res.srvc_id.uuid.uuid.uuid16);
        }
        break;
    }
    //RG: EVENT TRIGGERED AFTER THE SEARCH SERVICE IS COMPLETED AND THE CLIENT HAS FOUND THE SERVICE THAT IT WAS LOOKING FOR
    case ESP_GATTC_SEARCH_CMPL_EVT:
        if (p_data->search_cmpl.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "Error, when search service failed, error status = %x", p_data->search_cmpl.status);
            break;
        }
        if(p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_REMOTE_DEVICE) {

            ESP_LOGI(GATTC_TAG, "GATT PROFILE - Get service information from remote device");
        } else if (p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_NVS_FLASH) {

        	ESP_LOGI(GATTC_TAG, "GATT PROFILE - Get service information from flash");
        } else {
            ESP_LOGI(GATTC_TAG, "Error, when unknown service source");
        }
        ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_SEARCH_CMPL_EVT");
        if (get_server){
            uint16_t count = 0;//RG:ATTRIBUTES COUNTER
            //RG: COUNT ATTRIBUTES FOR THE GIVEN SERVICE IN THE GATTC CACHE
            esp_gatt_status_t status = esp_ble_gattc_get_attr_count( gattc_if,
                                                                     p_data->search_cmpl.conn_id,
                                                                     ESP_GATT_DB_CHARACTERISTIC,
                                                                     gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
                                                                     gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
                                                                     INVALID_HANDLE,
                                                                     &count);
            if (status != ESP_GATT_OK){//RG:IF THE ATTRIBUTES WERE NOT GOTTEN
                ESP_LOGE(GATTC_TAG, "Error, when esp_ble_gattc_get_attr_count");
            }

            if (count > 0){//RG:GET THE CHARACTERISTICS AVAILABLE IN THE GATTC CACHE REGARDING THE ATTRIBUTE TYPE
                char_elem_result = (esp_gattc_char_elem_t *)malloc(sizeof(esp_gattc_char_elem_t) * count);
                if (!char_elem_result){//NO ATTRIBUTES IN THE GATTC CACHE
                    ESP_LOGE(GATTC_TAG, "GATT PROFILE - gattc no mem");
                }else{
                    //RG:ALLOCATE A BUFFER TO SAVE THE CHARACTERISTIC INFORMATION REGARDING THE UUID CHARACTERISTIC
                    status = esp_ble_gattc_get_char_by_uuid( gattc_if,
                                                             p_data->search_cmpl.conn_id,
                                                             gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
                                                             gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
                                                             remote_filter_char_uuid,
                                                             char_elem_result,
                                                             &count);
                    if (status != ESP_GATT_OK){
                        ESP_LOGE(GATTC_TAG, "Error, when esp_ble_gattc_get_char_by_uuid");
                    }

                    /*  Every service have only one char in our 'ESP_GATTS_DEMO' demo, so we used first 'char_elem_result' */
                    if (count > 0//IF THERE IS A CHARACTERISTIC IN THE SERVICE
                    		&& (char_elem_result[0].properties //RG:POINTER TO CHARACTERISTIC OF THE SERVICE
                    		& ESP_GATT_CHAR_PROP_BIT_NOTIFY)){
                        gl_profile_tab[PROFILE_A_APP_ID].char_handle = char_elem_result[0].char_handle;
                        //RG:THE CLIENT CAN REGISTER TO RECEIVE NOTIFICATIONS FROM THE SERVER EVERY TIME THE CHARACTERISTIC VALUE CHANGES
                        esp_ble_gattc_register_for_notify (gattc_if, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, char_elem_result[0].char_handle);
                    }
                }
                /* free char_elem_result */
                free(char_elem_result);
            }else{
                ESP_LOGE(GATTC_TAG, "no char found");//RG:NO CHARACTERISTIC WAS FOUND
            }
        }
         break;
    case ESP_GATTC_REG_FOR_NOTIFY_EVT: {//TRIGGER WHEN THERE IS CHANGE ON THE SERVER CHARACTERISTIC

    	ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_REG_FOR_NOTIFY_EVT");
        if (p_data->reg_for_notify.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "Error, REG FOR NOTIFY failed: error status = %d", p_data->reg_for_notify.status);
        }else{
            uint16_t count = 0;//CHARACTERISTICS COUNTER
            //uint16_t notify_en = 1;//RG:THE VALUE TO WRITE IS “1” TO ENABLE NOTIFICATIONS
            esp_gatt_status_t ret_status = esp_ble_gattc_get_attr_count( gattc_if,
                                                                         gl_profile_tab[PROFILE_A_APP_ID].conn_id,
                                                                         ESP_GATT_DB_DESCRIPTOR,
                                                                         gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
                                                                         gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
                                                                         gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                                                         &count);
            if (ret_status != ESP_GATT_OK){//RG:IF ERRORS
                ESP_LOGE(GATTC_TAG, "Error, when esp_ble_gattc_get_attr_count");
            }
            if (count > 0){//GET ALL CHARACTERISTICS OF SERVICE
                descr_elem_result = malloc(sizeof(esp_gattc_descr_elem_t) * count);
                if (!descr_elem_result){
                    ESP_LOGE(GATTC_TAG, "Error, when malloc, gattc no mem");
                }else{
                    ret_status = esp_ble_gattc_get_descr_by_char_handle( gattc_if,
                                                                         gl_profile_tab[PROFILE_A_APP_ID].conn_id,
                                                                         p_data->reg_for_notify.handle,
                                                                         notify_descr_uuid,
                                                                         descr_elem_result,
                                                                         &count);
                    if (ret_status != ESP_GATT_OK){//RG:IF ERRORS
                        ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_descr_by_char_handle error");
                    }
                    /* Every char has only one descriptor in our 'ESP_GATTS_DEMO' demo, so we used first 'descr_elem_result' */
                    /*if (count > 0 && descr_elem_result[0].uuid.len == ESP_UUID_LEN_16 && descr_elem_result[0].uuid.uuid.uuid16 == ESP_GATT_UUID_CHAR_CLIENT_CONFIG){
                        ret_status = esp_ble_gattc_write_char_descr( gattc_if,
                                                                     gl_profile_tab[PROFILE_A_APP_ID].conn_id,
                                                                     descr_elem_result[0].handle,
                                                                     sizeof(notify_en),
                                                                     (uint8_t *)&notify_en,
                                                                     ESP_GATT_WRITE_TYPE_RSP,//RG:ESP_GATT_WRITE_TYPE_RSP TO REQUEST THAT THE SERVER RESPONDS TO THE REQUEST OF ENABLING NOTIFICATIONS
                                                                     ESP_GATT_AUTH_REQ_NONE);//RG:ESP_GATT_AUTH_REQ_NONE TO INDICATE THAT THE WRITE REQUEST DOES NOT NEED AUTHORIZATION
                    }

                    if (ret_status != ESP_GATT_OK){//RG:IF ERRORS
                        ESP_LOGE(GATTC_TAG, "esp_ble_gattc_write_char_descr error");
                    }*/

                    if (count > 0 && descr_elem_result[0].uuid.len == ESP_UUID_LEN_16 && descr_elem_result[0].uuid.uuid.uuid16 == ESP_GATT_UUID_CHAR_CLIENT_CONFIG){
                        ret_status = esp_ble_gattc_read_char_descr( gattc_if,
																 gl_profile_tab[PROFILE_A_APP_ID].conn_id,
																 descr_elem_result[0].handle,
																 ESP_GATT_AUTH_REQ_NONE);//RG:ESP_GATT_AUTH_REQ_NONE TO INDICATE THAT THE WRITE REQUEST DOES NOT NEED AUTHORIZATION
                    }

                    if (ret_status != ESP_GATT_OK){//RG:IF ERRORS
                        ESP_LOGE(GATTC_TAG, "esp_ble_gattc_read_char_descr error");
                    }

                    //xTaskCreatePinnedToCore(&Timestamp, "Timestamp_task", 2048, gattc_if, 5, NULL, 1);

                    /* free descr_elem_result */
                    //free(descr_elem_result);

                }
            }
            else{
                ESP_LOGE(GATTC_TAG, "Error, decsr not found");
            }

        }
        break;
    }
    case ESP_GATTC_NOTIFY_EVT:
        if (p_data->notify.is_notify){
            ESP_LOGI(GATTC_TAG, "ESP_GATTC_NOTIFY_EVT, receive notify value:");
        }else{
            ESP_LOGI(GATTC_TAG, "ESP_GATTC_NOTIFY_EVT, receive indicate value:");
        }

        //RG:VALUE RECEIVED FROM THE NOTIFICATION EVENT(15 CHARACTERS)
        ESP_LOGI(GATTC_TAG, "VALUE RECEIVED FROM THE NOTIFICATION EVENT (15 CHARACTERS):");
        esp_log_buffer_hex(GATTC_TAG, p_data->notify.value, p_data->notify.value_len);

        break;
    case ESP_GATTC_READ_DESCR_EVT:
    	if (p_data->write.status != ESP_GATT_OK){
			ESP_LOGE(GATTC_TAG, "Error, when read descr failed, error status = %x", p_data->write.status);
			break;
		}
    	//RG: READ EVENT FROM CLIENT TO SERVER
    	//ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_READ_DESCR_EVT Read Descr Success ");

	    	   printf("\t    ____A____\t   ____B____\n");
			   printf("\t   |= = = = =|\t  |= = = = =|\n");
			   printf("\t   |= %02dPSI =|\t  |= %02dPSI =|\n",p_data->read.value[0],p_data->read.value[1]);
			   printf("\t   |=_=_=_=_=|\t  |=_=_=_=_=|\n");
			 printf("     _____________________________________\n");
			printf("    /\t\t\t\t\t  |\n");
		   printf("   /\t\t\t\t\t  |\n");
		  printf("  /\t\t\t\t\t  |\n");
		 printf(" /\t\t\t\t\t  |\n");
		printf("/\t\t\t\t\t  |\n");
		printf("\\ \t\t\t\t\t  |\n");
		 printf(" \\ \t\t\t\t\t  |\n");
		  printf("  \\ \t\t\t\t\t  |\n");
		   printf("   \\______________________________________|\n");
			   printf("\t    _________\t   _________\n");
			   printf("\t   |= = = = =|\t  |= = = = =|\n");
			   printf("\t   |= %02dPSI =|\t  |= %02dPSI =|\n",p_data->read.value[2],p_data->read.value[3]);
			   printf("\t   |=_=_=_=_=|\t  |_=_=_=_=_|\n");
		       printf("\t\tC\t       D\n");





    	/*
        ESP_LOGI(GATTC_TAG, "\n---------------\nWheel A = %d PSI\nWheel B = %d PSI\nWheel C = %d PSI\nWheel D = %d PSI", p_data->read.value[0],
        															p_data->read.value[1],
																	p_data->read.value[2],
																	p_data->read.value[3]);
*/
//        printf("\n-----DISPLAY-----\nWheel A = %d PSI\nWheel B = %d PSI\nWheel C = %d PSI\nWheel D = %d PSI\n", p_data->read.value[0],
//                															p_data->read.value[1],
//        																	p_data->read.value[2],
//        																	p_data->read.value[3]);
/*
        printf("\t      _\n");
		printf("\t     / \\ \n");
		printf("\t    /   \\ \n");
		printf("\t   /     \\ \n");
		printf(" _________/_______\\_________\n");
		printf("|   A\t|\t    |\tB   |\n");
		printf("|  %02d\t|\t    |\t%02d  |\n",p_data->read.value[0],p_data->read.value[1]);
		printf("|_______|           |_______|\n");
		printf("\t|           |\n");
		printf(" _______|           |_______\n");
		printf("|   C   |\t    |\tD   |\n");
		printf("|  %02d\t|\t    |\t%02d  |\n",p_data->read.value[2],p_data->read.value[3]);
		printf("|_______|           |_______|\n");
		printf("\t|           |\n");
		printf("\t|___________|\n");
*/


        vTaskDelay(8000 / portTICK_PERIOD_MS);
        esp_gatt_status_t ret_status = esp_ble_gattc_read_char_descr( gattc_if,
												 gl_profile_tab[PROFILE_A_APP_ID].conn_id,
												 descr_elem_result[0].handle,
												 ESP_GATT_AUTH_REQ_NONE);//RG:ESP_GATT_AUTH_REQ_NONE TO INDICATE THAT THE WRITE REQUEST DOES NOT NEED AUTHORIZATION

        if (ret_status != ESP_GATT_OK){//RG:IF ERRORS
            ESP_LOGE(GATTC_TAG, "esp_ble_gattc_read_char_descr error");
        }

		break;
    case ESP_GATTC_WRITE_DESCR_EVT:
        if (p_data->write.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "Error, when write descr failed, error status = %x", p_data->write.status);
            break;
        }
        //RG: WRITE EVENT FROM CLIENT TO SERVER DESCRIPTION
        ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_WRITE_DESCR_EVT Write Descr Success ");

        uint8_t write_char_data[35];

        for (int i = 0; i < sizeof(write_char_data); ++i)
        {
            write_char_data[i] = i % 256;
        }

        //RG:SENDS INFORMATION TO SERVER (WRITES)
        esp_ble_gattc_write_char( gattc_if,
                                  gl_profile_tab[PROFILE_A_APP_ID].conn_id,
                                  gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                  sizeof(write_char_data),
                                  write_char_data,
                                  ESP_GATT_WRITE_TYPE_RSP,
                                  ESP_GATT_AUTH_REQ_NONE);

        break;
    case ESP_GATTC_SRVC_CHG_EVT: {
        esp_bd_addr_t bda;
        memcpy(bda, p_data->srvc_chg.remote_bda, sizeof(esp_bd_addr_t));
        ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_SRVC_CHG_EVT, bd_addr:");
        esp_log_buffer_hex(GATTC_TAG, bda, sizeof(esp_bd_addr_t));
        break;
    }
    case ESP_GATTC_READ_CHAR_EVT:
        if (p_data->write.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "Error, char failed, error status = %x", p_data->write.status);
            break;
        }

        break;
    case ESP_GATTC_WRITE_CHAR_EVT:
        if (p_data->write.status != ESP_GATT_OK){
            ESP_LOGE(GATTC_TAG, "Error, write char failed, error status = %x", p_data->write.status);
            break;
        }
        ESP_LOGI(GATTC_TAG, "GATT PROFILE - Write ESP_GATTC_WRITE_CHAR_EVT char success ");
        break;
    case ESP_GATTC_DISCONNECT_EVT:
        connect = false;
        get_server = false;
        ESP_LOGI(GATTC_TAG, "GATT PROFILE - ESP_GATTC_DISCONNECT_EVT, reason = %d", p_data->disconnect.reason);
        break;
    default:
        break;
    }
}

static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;
    switch (event) {
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {//RG:TRIGGERED AFTER THE SCAN PARAMETERS ARE SET (GATTC PROFILE EVENT HANDLER)
        //RG:START THE SCANNING OF NEARBY GATT SERVERS
    	//the unit of the duration is second
        uint32_t duration = 30;
        esp_ble_gap_start_scanning(duration);//RG:START THE SCANNING. ONCE IT'S ENDED, AN ESP_GAP_SEARCH_INQ_CMPL_EVT EVENT IS TRIGGERED
        break;
    }
    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        //scan start complete event to indicate scan start successfully or failed
        if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTC_TAG, "Error, scan start failed, error status = %x", param->scan_start_cmpl.status);
            break;
        }
        ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_BLE_SCAN_START_COMPLETE_EVT) Scan start success");

        break;
    case ESP_GAP_BLE_SCAN_RESULT_EVT: {
        esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;//RG:GET THE DEVICE PARAMETERS
        switch (scan_result->scan_rst.search_evt) {
			case ESP_GAP_SEARCH_INQ_RES_EVT://RG:EVENT CALLED EVERY TIME A NEW DEVICE IS FOUND

				ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_SEARCH_INQ_RES_EVT) Remote Device Address:");
				esp_log_buffer_hex(GATTC_TAG, scan_result->scan_rst.bda, 6);

				ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_SEARCH_INQ_RES_EVT) searched Adv Data Len %d, Scan Response Len %d", scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);

				//RG:GETS THE DEVICE NAME JUST FOUND
				adv_name = esp_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
													ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);//RG:USED TO EXTRACT THE DEVICE NAME AND LENGTH

				ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_SEARCH_INQ_RES_EVT) Searched Device Name Len %d", adv_name_len);
				esp_log_buffer_char(GATTC_TAG, adv_name, adv_name_len);

	#if CONFIG_EXAMPLE_DUMP_ADV_DATA_AND_SCAN_RESP
				if (scan_result->scan_rst.adv_data_len > 0) {
					ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_SEARCH_INQ_RES_EVT) adv data:");
					esp_log_buffer_hex(GATTC_TAG, &scan_result->scan_rst.ble_adv[0], scan_result->scan_rst.adv_data_len);
				}
				if (scan_result->scan_rst.scan_rsp_len > 0) {
					ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_SEARCH_INQ_RES_EVT) scan resp:");
					esp_log_buffer_hex(GATTC_TAG, &scan_result->scan_rst.ble_adv[scan_result->scan_rst.adv_data_len], scan_result->scan_rst.scan_rsp_len);
				}
	#endif
				ESP_LOGI(GATTC_TAG, "\n");

				if (adv_name != NULL) {//RG:THERE IS A DEVICE NAME
					//RG:IF IT EQUALS TO THE DEVICE NAME OF THE GATT SERVER WE ARE INTERESTED IN
					if (strlen(remote_device_name) == adv_name_len && strncmp((char *)adv_name, remote_device_name, adv_name_len) == 0) {
						ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_SEARCH_INQ_RES_EVT) Success. We found the SERVER %s\n", remote_device_name);
						if (connect == false) {//RG:USED TO INDICATE IF THE CONNECTION IS DONE DIRECTLY OR IF IT'S DONE IN THE BACKGROUND (AUTO-CONNECTION)
							connect = true;//RG:STABLISH CONNECTION TO THE SERVER
							ESP_LOGI(GATTC_TAG, "GAP (ESP_GAP_SEARCH_INQ_RES_EVT) Connect to the remote device.");
							esp_ble_gap_stop_scanning();//RG:STOP SCANNING SINCE THE SERVER WAS FOUND
							//RG:CLIENT OPENS A VIRTUAL CONNEXTION TO THE SERVER
							//RG:THE VIRTUAL CONNECTION IS THE CONNECTION BETWEEN THE APPLICATION PROFILE AND THE REMOTE SERVER
							esp_ble_gattc_open(gl_profile_tab[PROFILE_A_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
						}
					}
				}
				break;
			case ESP_GAP_SEARCH_INQ_CMPL_EVT://RG:TRIGGERED WHEN THE DURATION OF THE SCANNING IS COMPLETED
											 //RG:AND CAN BE USED TO RESTART THE SCANNING PROCEDURE
				break;
			default:
				break;
        }
        break;
    }

    case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
        if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){
            ESP_LOGE(GATTC_TAG, "scan stop failed, error status = %x", param->scan_stop_cmpl.status);
            break;
        }
        ESP_LOGI(GATTC_TAG, "stop scan successfully");
        break;

    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){
            ESP_LOGE(GATTC_TAG, "adv stop failed, error status = %x", param->adv_stop_cmpl.status);
            break;
        }
        ESP_LOGI(GATTC_TAG, "stop adv successfully");
        break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
         ESP_LOGI(GATTC_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
        break;
    default:
        break;
    }
}

static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
	//RG:REGISTRATION FOR APPLICATION PROFILES

    /* If event is register event, store the gattc_if for each profile */
    if (event == ESP_GATTC_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            gl_profile_tab[param->reg.app_id].gattc_if = gattc_if;
        } else {
            ESP_LOGI(GATTC_TAG, "Error, reg app failed, app_id %04x, status %d",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gattc_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    //RG: PROFILES CALLBACK
    do {
        int idx;
        for (idx = 0; idx < PROFILE_NUM; idx++) {
            if (gattc_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gattc_if == gl_profile_tab[idx].gattc_if) {
                if (gl_profile_tab[idx].gattc_cb) {
                    gl_profile_tab[idx].gattc_cb(event, gattc_if, param);//RG:INVOKES THE CORRESPONDING EVENT HANDLER FOR EACH PROFILE IN THE gl_profile_tab TABLE
                }
            }
        }
    } while (0);//RG:IT RUNS ONCE
}


/*void Timestamp(esp_gatt_if_t *pgattc_if)
{
	time_t rawtime;
	struct tm * timeinfo;
	char timeBuffer [80];
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    while(1) {
        vTaskDelay(2000 / portTICK_PERIOD_MS);

    	time (&rawtime);
    	timeinfo = localtime (&rawtime);

    	strftime (timeBuffer,80,"%r",timeinfo);
    	puts (timeBuffer);

		esp_gatt_status_t ret_status = esp_ble_gattc_read_char_descr(pgattc_if,
												 gl_profile_tab[PROFILE_A_APP_ID].conn_id,
												 descr_elem_result[0].handle,
												 ESP_GATT_AUTH_REQ_NONE);//RG:ESP_GATT_AUTH_REQ_NONE TO INDICATE THAT THE WRITE REQUEST DOES NOT NEED AUTHORIZATION

		if (ret_status != ESP_GATT_OK){//RG:IF ERRORS
			ESP_LOGE(GATTC_TAG, "esp_ble_gattc_read_char_descr error");
		}
    }
}*/


/*void Timestamp(){
	time_t rawtime;
	struct tm * timeinfo;
	char timeBuffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (timeBuffer,80,"%r",timeinfo);
	puts (timeBuffer);
}*/

void app_main(void)
{
	// Initialize NVS.
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());//RG: ERRASE THE WHOLE PARTITION
        ret = nvs_flash_init();//RG: INITIALIZE THE NVS
    }
    ESP_ERROR_CHECK( ret );//RG: CHECK AGAIN IF ERRORS EXIST

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();//RG: DECLARES THE BLUETOOTH CONFIGURATION VARIABLE
    ret = esp_bt_controller_init(&bt_cfg);//RG: INITIALIZE THE BLUETOOTH CONFIGURATION AND PASSES ITS LOCATION IN MEMORY
    if (ret) {//RG: IF VALUE RETURNED IS AN ERROR
        ESP_LOGE(GATTC_TAG, "Error, %s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;//RG: ENDS THE PROGRAM
    }

    //RG: NO ERROR WAS DETECTED SO THE BLUETOOTH CONTROLLER CAN BE ENABLE
    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {//RG: IF VALUE RETURNED IS AN ERROR
        ESP_LOGE(GATTC_TAG, "Error, %s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;//RG: ENDS THE PROGRAM
    }
    //RG: NO ERROR WAS DETECTED SO THE BLUEDROID OPTION CAN BE INITIALIZED

    ret = esp_bluedroid_init();//RG: INITIALIZE BLUEDROID

    if (ret) {//RG: IF VALUE RETURNED IS AN ERROR
        ESP_LOGE(GATTC_TAG, "Error, %s init bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;//RG: ENDS THE PROGRAM
    }

    ret = esp_bluedroid_enable();//RG: IF VALUE RETURNED IS AN ERROR
    if (ret) {
        ESP_LOGE(GATTC_TAG, "Error, %s enable bluetooth failed: %s\n", __func__, esp_err_to_name(ret));
        return;//RG: ENDS THE PROGRAM
    }
    //RG: THE BLUETOOTH STACK IS UP AND RUNNING
    //RG: THE MAIN FUNCTION ENDS BY REGISTERING THE GAP AND GATT EVENT HANDLERS AS WELL AS THE APPLICATION PROFILE
    //RG: AND SET THE MAXIMUM MTU (MAXIMUM TRANSMISSION UNIT) SIZE

    //register the  callback function to the gap module
    //RG: THE GAP EVENT HANDLER TAKES CARE OF SCANNING AND CONNECTING TO SERVERS
    ret = esp_ble_gap_register_callback(esp_gap_cb);
    if (ret){
        ESP_LOGE(GATTC_TAG, "%s gap register failed, error code = %x\n", __func__, ret);
        return;//RG: ENDS THE PROGRAM
    }

    //register the callback function to the gattc module
    //RG: GATT HANDLER MANAGES EVENTS THAT HAPPEN AFTER THE CLIENT HAS CONNECTED TO A SERVER,
    //RG: SUCH AS SEARCHING FOR SERVICES AND WRITING AND READING DATA
    ret = esp_ble_gattc_register_callback(esp_gattc_cb);
    if(ret){
        ESP_LOGE(GATTC_TAG, "%s gattc register failed, error code = %x\n", __func__, ret);
        return;//RG: ENDS THE PROGRAM
    }

	ret = esp_ble_gattc_app_register(PROFILE_A_APP_ID);
	if (ret){
		ESP_LOGE(GATTC_TAG, "%s gattc app register failed, error code = %x\n", __func__, ret);
	}

	esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
	if (local_mtu_ret){
		ESP_LOGE(GATTC_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
	}
}
