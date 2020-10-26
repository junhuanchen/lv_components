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

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_list_create(lv_obj_t * parent)
{
    lv_obj_t * list = lv_obj_create(parent, NULL);
    list->flex_cont.dir = LV_FLEX_DIR_COLUMN;

    return list;
}

lv_obj_t * lv_list_add_text(lv_obj_t * list, const char * txt)
{
    lv_obj_t * label = lv_label_create(list, NULL);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_obj_set_flex_item(label, LV_FLEX_START);
    lv_obj_set_width(label, LV_COORD_PCT(100));
    return label;
}

lv_obj_t * lv_list_add_btn(lv_obj_t * list, const char * txt)
{
    lv_obj_t * btn = lv_btn_create(list, NULL);
    lv_obj_set_flex_item(btn, LV_FLEX_START);
    lv_obj_set_width(btn, LV_COORD_PCT(100));

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);

    return label;
}

lv_obj_t * lv_list_add_btn_with_icon(lv_obj_t * list, const char * icon, const char * txt)
{
    lv_obj_t * btn = lv_btn_create(list, NULL);
    lv_obj_set_flex_item(btn, LV_FLEX_START);
    lv_obj_set_width(btn, LV_COORD_PCT(100));

    lv_obj_t * img = lv_img_create(btn, NULL);
    lv_img_set_src(img, icon);
    lv_obj_set_flex_item(img, LV_FLEX_START);
    lv_obj_set_style_local_margin_right(img, 0, 0, 10);

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_obj_set_width(label, LV_FLEX_GROW(1));
    lv_obj_set_flex_item(label, LV_FLEX_START);

    btn->flex_cont.dir = LV_FLEX_DIR_ROW;
    _lv_flex_refresh(btn);

    return label;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
