// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include <stdio.h>

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_LblTPMS1;
lv_obj_t * ui_LblTPMS2;
lv_obj_t * ui_trailer;
lv_obj_t * ui_Image12;
lv_obj_t * ui_Image13;
lv_obj_t * ui_Image1;
lv_obj_t * ui_LblTPMS3;
lv_obj_t * ui_LblTPMS4;
lv_obj_t * ui_Image2;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Image4;
lv_obj_t * ui_Image5;
lv_obj_t * ui_LblTPMS5;
lv_obj_t * ui_LblTPMS6;
lv_obj_t * ui_Button1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Image8;
lv_obj_t * ui_LblWeight1;
lv_obj_t * ui_LblWeight2;
lv_obj_t * ui_LblWeight3;
lv_obj_t * ui_LblWeight4;
lv_obj_t * ui_Image14;
lv_obj_t * ui_Image7;
lv_obj_t * ui_Image9;
lv_obj_t * ui_Image10;
lv_obj_t * ui_Image6;
lv_obj_t * ui_Button3;
lv_obj_t * ui_Label1;
lv_obj_t * ui_LblLoadStatus;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "#error LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_Image4(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        _ui_flag_modify(ui_Image4, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
static void ui_event_Button1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0);
    }
}
static void ui_event_Button3(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(char tpms1[], char tpms2[], char tpms3[], char tpms4[], char tpms5[], char tpms6[])
{

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LblTPMS1

    ui_LblTPMS1 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LblTPMS1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblTPMS1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblTPMS1, -70);
    lv_obj_set_y(ui_LblTPMS1, -75);

    lv_obj_set_align(ui_LblTPMS1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblTPMS1, tpms1);

    // ui_LblTPMS2

    ui_LblTPMS2 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LblTPMS2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblTPMS2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblTPMS2, 70);
    lv_obj_set_y(ui_LblTPMS2, -75);

    lv_obj_set_align(ui_LblTPMS2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblTPMS2, tpms2);

    // ui_trailer

    ui_trailer = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_trailer, &ui_img_rsz_picture4_png);

    lv_obj_set_width(ui_trailer, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_trailer, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_trailer, 0);
    lv_obj_set_y(ui_trailer, 0);

    lv_obj_set_align(ui_trailer, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_trailer, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_trailer, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image12

    ui_Image12 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image12, &ui_img_rsz_dexter_big_png);

    lv_obj_set_width(ui_Image12, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image12, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image12, -132);
    lv_obj_set_y(ui_Image12, -99);

    lv_obj_set_align(ui_Image12, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image12, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image12, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image13

    ui_Image13 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image13, &ui_img_rsz_tpmsicon_png);

    lv_obj_set_width(ui_Image13, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image13, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image13, -70);
    lv_obj_set_y(ui_Image13, -102);

    lv_obj_set_align(ui_Image13, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image13, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image13, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image1

    ui_Image1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image1, &ui_img_rsz_tpmsicon_png);

    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image1, 70);
    lv_obj_set_y(ui_Image1, -102);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LblTPMS3

    ui_LblTPMS3 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LblTPMS3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblTPMS3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblTPMS3, -70);
    lv_obj_set_y(ui_LblTPMS3, 48);

    lv_obj_set_align(ui_LblTPMS3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblTPMS3, tpms3);

    // ui_LblTPMS4

    ui_LblTPMS4 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LblTPMS4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblTPMS4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblTPMS4, 70);
    lv_obj_set_y(ui_LblTPMS4, 48);

    lv_obj_set_align(ui_LblTPMS4, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblTPMS4, tpms4);

    // ui_Image2

    ui_Image2 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image2, &ui_img_rsz_tpmsicon_png);

    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image2, 70);
    lv_obj_set_y(ui_Image2, 21);

    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image3

    ui_Image3 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image3, &ui_img_rsz_tpmsicon_png);

    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image3, -70);
    lv_obj_set_y(ui_Image3, 21);

    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image4

    ui_Image4 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image4, &ui_img_rsz_tpmsicon_png);

    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image4, -70);
    lv_obj_set_y(ui_Image4, 102);

    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Image4, ui_event_Image4, LV_EVENT_ALL, NULL);

    // ui_Image5

    ui_Image5 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image5, &ui_img_rsz_tpmsicon_png);

    lv_obj_set_width(ui_Image5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image5, 70);
    lv_obj_set_y(ui_Image5, 102);

    lv_obj_set_align(ui_Image5, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LblTPMS5

    ui_LblTPMS5 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LblTPMS5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblTPMS5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblTPMS5, -70);
    lv_obj_set_y(ui_LblTPMS5, 74);

    lv_obj_set_align(ui_LblTPMS5, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblTPMS5, tpms5);

    // ui_LblTPMS6

    ui_LblTPMS6 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LblTPMS6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblTPMS6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblTPMS6, 70);
    lv_obj_set_y(ui_LblTPMS6, 74);

    lv_obj_set_align(ui_LblTPMS6, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblTPMS6, tpms6);

    // ui_Button1

    ui_Button1 = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_Button1, 35);
    lv_obj_set_height(ui_Button1, 28);

    lv_obj_set_x(ui_Button1, 148);
    lv_obj_set_y(ui_Button1, -103);

    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);

    // ui_Label2

    ui_Label2 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label2, 148);
    lv_obj_set_y(ui_Label2, -103);

    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label2, ">");

    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Screen2_screen_init(char weight1[], char weight2[], char weight3[], char weight4[])
{

    // ui_Screen2

    ui_Screen2 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image8

    ui_Image8 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image8, &ui_img_weight_truck_png);

    lv_obj_set_width(ui_Image8, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image8, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image8, -1);
    lv_obj_set_y(ui_Image8, 6);

    lv_obj_set_align(ui_Image8, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image8, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image8, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LblWeight1

    ui_LblWeight1 = lv_label_create(ui_Screen2);

    lv_obj_set_width(ui_LblWeight1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblWeight1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblWeight1, -122);
    lv_obj_set_y(ui_LblWeight1, 24);

    lv_obj_set_align(ui_LblWeight1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblWeight1, weight1);

    // ui_LblWeight2

    ui_LblWeight2 = lv_label_create(ui_Screen2);

    lv_obj_set_width(ui_LblWeight2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblWeight2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblWeight2, -92);
    lv_obj_set_y(ui_LblWeight2, 55);

    lv_obj_set_align(ui_LblWeight2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblWeight2, weight2);

    // ui_LblWeight3

    ui_LblWeight3 = lv_label_create(ui_Screen2);

    lv_obj_set_width(ui_LblWeight3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblWeight3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblWeight3, 113);
    lv_obj_set_y(ui_LblWeight3, -17);

    lv_obj_set_align(ui_LblWeight3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblWeight3, weight3);

    // ui_LblWeight4

    ui_LblWeight4 = lv_label_create(ui_Screen2);

    lv_obj_set_width(ui_LblWeight4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblWeight4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblWeight4, 118);
    lv_obj_set_y(ui_LblWeight4, 75);

    lv_obj_set_align(ui_LblWeight4, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblWeight4, weight4);

    // ui_Image14

    ui_Image14 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image14, &ui_img_weight_s_png);

    lv_obj_set_width(ui_Image14, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image14, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image14, -122);
    lv_obj_set_y(ui_Image14, 0);

    lv_obj_set_align(ui_Image14, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image14, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image14, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image7

    ui_Image7 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image7, &ui_img_weight_s_png);

    lv_obj_set_width(ui_Image7, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image7, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image7, -92);
    lv_obj_set_y(ui_Image7, 78);

    lv_obj_set_align(ui_Image7, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image7, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image7, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image9

    ui_Image9 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image9, &ui_img_weight_s_png);

    lv_obj_set_width(ui_Image9, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image9, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image9, 112);
    lv_obj_set_y(ui_Image9, -41);

    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image10

    ui_Image10 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image10, &ui_img_weight_s_png);

    lv_obj_set_width(ui_Image10, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image10, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image10, 118);
    lv_obj_set_y(ui_Image10, 48);

    lv_obj_set_align(ui_Image10, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image10, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image10, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image6

    ui_Image6 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image6, &ui_img_rsz_dexter_big_png);

    lv_obj_set_width(ui_Image6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image6, 130);
    lv_obj_set_y(ui_Image6, -99);

    lv_obj_set_align(ui_Image6, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image6, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image6, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Button3

    ui_Button3 = lv_btn_create(ui_Screen2);

    lv_obj_set_width(ui_Button3, 35);
    lv_obj_set_height(ui_Button3, 28);

    lv_obj_set_x(ui_Button3, -148);
    lv_obj_set_y(ui_Button3, -103);

    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button3, ui_event_Button3, LV_EVENT_ALL, NULL);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_Screen2);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, -148);
    lv_obj_set_y(ui_Label1, -103);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "<");

    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LblLoadStatus

    ui_LblLoadStatus = lv_label_create(ui_Screen2);

    lv_obj_set_width(ui_LblLoadStatus, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LblLoadStatus, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LblLoadStatus, -6);
    lv_obj_set_y(ui_LblLoadStatus, -108);

    lv_obj_set_align(ui_LblLoadStatus, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LblLoadStatus, "Load balanced");

    lv_obj_set_style_text_color(ui_LblLoadStatus, lv_color_hex(0x2B6A16), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LblLoadStatus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_ScreenX_screen_update(int data[])
{
	char buff_0[] = "--------";
	char buff_1[] = "--------";
	char buff_2[] = "--------";
	char buff_3[] = "--------";
	char buff_4[] = "--------";
	char buff_5[] = "--------";
	char buff_w0[] = "--------";
	char buff_w1[] = "--------";
	char buff_w2[] = "--------";
	char buff_w3[] = "--------";

	if(data[0] <=35 || data[0] >= 60){
		lv_obj_clear_flag(ui_Image13, LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		lv_obj_add_flag(ui_Image13, LV_OBJ_FLAG_HIDDEN);
	}

	if(data[1] <=35 || data[1] >= 60){
		lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
	}

	if(data[2] <=35 || data[2] >= 60){
		lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
	}

	if(data[3] <=35 || data[3] >= 60){
		lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_HIDDEN);
	}

	if(data[4] <=35 || data[4] >= 60){
		lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
	}

	if(data[5] <=35 || data[5] >= 60){
		lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_HIDDEN);
	}

    lv_label_set_text(ui_LblTPMS1, strcat(itoa(data[0], buff_0, 10), " PSI"));
    printf("buff_0: %s\n", buff_0);
	lv_label_set_text(ui_LblTPMS2, strcat(itoa(data[1], buff_1, 10), " PSI"));
	printf("buff_1: %s\n", buff_1);
	lv_label_set_text(ui_LblTPMS3, strcat(itoa(data[2], buff_2, 10), " PSI"));
	printf("buff_2: %s\n", buff_2);
	lv_label_set_text(ui_LblTPMS4, strcat(itoa(data[3], buff_3, 10), " PSI"));
	printf("buff_3: %s\n", buff_3);
	lv_label_set_text(ui_LblTPMS5, strcat(itoa(data[4], buff_4, 10), " PSI"));
	printf("buff_4: %s\n", buff_4);
	lv_label_set_text(ui_LblTPMS6, strcat(itoa(data[5], buff_5, 10), " PSI"));
	printf("buff_5: %s\n", buff_5);

    lv_label_set_text(ui_LblWeight1, strcat(itoa(data[6], buff_w0, 10), " LBS"));
    printf("buff_w0: %s\n", buff_w0);
    lv_label_set_text(ui_LblWeight2, strcat(itoa(data[7], buff_w1, 10), " LBS"));
    printf("buff_w1: %s\n", buff_w1);
    lv_label_set_text(ui_LblWeight3, strcat(itoa(data[8], buff_w2, 10), " LBS"));
    printf("buff_w2: %s\n", buff_w2);
    lv_label_set_text(ui_LblWeight4, strcat(itoa(data[9], buff_w3, 10), " LBS"));
    printf("buff_w3: %s\n", buff_w3);
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init("0 PSI","0 PSI","0 PSI","0 PSI","0 PSI","0 PSI");
    ui_Screen2_screen_init("0 LBS", "0 LBS", "0 LBS", "0 LBS");
    lv_disp_load_scr(ui_Screen1);
}

