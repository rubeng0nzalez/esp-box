// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

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

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(char tpms1[], char tpms2[], char tpms3[], char tpms4[], char tpms5[], char tpms6[])
{

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

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

    lv_obj_add_flag(ui_Image13, LV_OBJ_FLAG_HIDDEN);
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

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
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

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_HIDDEN);
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

    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
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

    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
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

    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_HIDDEN);
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

}

void ui_Screen1_screen_update(int tpms[])
{
	char buff_0[] = "---------";
	char buff_1[] = "---------";
	char buff_2[] = "---------";
	char buff_3[] = "---------";
	char buff_4[] = "---------";
	char buff_5[] = "---------";

	if(tpms[0] <=35 || tpms[0] >= 60){
		lv_obj_clear_flag(ui_Image13, LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		lv_obj_add_flag(ui_Image13, LV_OBJ_FLAG_HIDDEN);
	}

	if(tpms[1] <=35 || tpms[1] >= 60){
		lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
	}

	if(tpms[2] <=35 || tpms[2] >= 60){
		lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
	}

	if(tpms[3] <=35 || tpms[3] >= 60){
		lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_HIDDEN);
	}

	if(tpms[4] <=35 || tpms[4] >= 60){
		lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
	}

	if(tpms[5] <=35 || tpms[5] >= 60){
		lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_HIDDEN);
	}
	else{
		lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_HIDDEN);
	}

    lv_label_set_text(ui_LblTPMS1, strcat(itoa(tpms[0], buff_0, 10), " PSI"));
	lv_label_set_text(ui_LblTPMS2, strcat(itoa(tpms[1], buff_1, 10), " PSI"));
	lv_label_set_text(ui_LblTPMS3, strcat(itoa(tpms[2], buff_2, 10), " PSI"));
	lv_label_set_text(ui_LblTPMS4, strcat(itoa(tpms[3], buff_3, 10), " PSI"));
	lv_label_set_text(ui_LblTPMS5, strcat(itoa(tpms[4], buff_4, 10), " PSI"));
	lv_label_set_text(ui_LblTPMS6, strcat(itoa(tpms[5], buff_5, 10), " PSI"));
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init("0 PSI","0 PSI","0 PSI","0 PSI","0 PSI","0 PSI");
    lv_disp_load_scr(ui_Screen1);
}

