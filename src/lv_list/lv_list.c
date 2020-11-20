/**
 * @file lv_list.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_list.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static bool inited;
static lv_style_t style_bg;
static lv_style_t style_btn;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_list_create(lv_obj_t * parent)
{
    if(!inited) {
        lv_style_init(&style_bg);
        lv_style_set_clip_corner(&style_bg, LV_STATE_DEFAULT, true);
        lv_style_set_pad_ver(&style_bg, LV_STATE_DEFAULT, 0);

        lv_style_init(&style_btn);
        lv_style_set_bg_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_TRANSP);
        lv_style_set_bg_opa(&style_btn, LV_STATE_PRESSED, LV_OPA_20);
        lv_style_set_bg_opa(&style_btn, LV_STATE_CHECKED, LV_OPA_COVER);
        lv_style_set_bg_opa(&style_btn, LV_STATE_FOCUSED, LV_OPA_COVER);

        lv_style_set_bg_color(&style_btn, LV_STATE_PRESSED, LV_COLOR_GRAY);

        lv_style_set_border_side(&style_btn, LV_STATE_DEFAULT, LV_BORDER_SIDE_BOTTOM);
        lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED, lv_theme_get_color_primary());
        lv_style_set_border_width(&style_btn, LV_STATE_DEFAULT, LV_DPX(1));
        lv_style_set_transform_width(&style_btn, LV_STATE_PRESSED, 30);

        lv_style_set_pad_all(&style_btn, LV_STATE_DEFAULT, 0);


        inited = true;
    }

    lv_obj_t * list = lv_obj_create(parent, NULL);
    lv_obj_add_style(list, LV_OBJ_PART_MAIN, &style_bg);
    lv_obj_set_flex_dir(list, LV_FLEX_DIR_COLUMN);

    return list;
}

lv_obj_t * lv_list_add_text(lv_obj_t * list, const char * txt)
{
    lv_obj_t * label = lv_label_create(list, NULL);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_obj_set_flex_item(label, true);
    lv_obj_set_width(label, LV_COORD_PCT(100));
    return label;
}

lv_obj_t * lv_list_add_btn(lv_obj_t * list, const char * icon, const char * txt, lv_event_cb_t event_cb)
{
    lv_obj_t * btn = lv_obj_create(list, NULL);
    lv_obj_add_style(btn, LV_OBJ_PART_MAIN, &style_btn);
    lv_obj_set_flex_item(btn, true);
    lv_obj_set_width(btn, LV_COORD_PCT(100));
    lv_obj_set_event_cb(btn, event_cb);

    if(icon) {
        lv_obj_t * img = lv_img_create(btn, NULL);
        lv_img_set_src(img, icon);
        lv_obj_set_flex_item(img, true);
    }

    if(txt) {
        lv_obj_t * label = lv_label_create(btn, NULL);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
        lv_obj_set_width(label, LV_FLEX_GROW(1));
        lv_obj_set_flex_item(label, true);

//        lv_obj_set_flex_gap(btn, LV_DPX(5));
        lv_obj_set_flex_place(btn, LV_FLEX_PLACE_START, LV_FLEX_PLACE_CENTER);
        lv_obj_set_flex_dir(btn, LV_FLEX_DIR_ROW);
    }

    return btn;
}

const char * lv_list_get_btn_text(lv_obj_t * btn)
{
    lv_obj_t * child = lv_obj_get_child(btn, NULL);

    while(child) {
        if(lv_obj_is_instance_of(child, "lv_label")) {
            return lv_label_get_text(child);
        }
        child = lv_obj_get_child(btn, child);
    }

    return "";
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
