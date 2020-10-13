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
typedef struct {
    lv_coord_t col_dsc[2];
    lv_grid_t grid;
}lv_iconbtn_ext_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_coord_t grid_fr1 = LV_GRID_FR(1);
static const lv_grid_t grid = {
        .col_dsc = &grid_fr1,
        .col_dsc_len = 1,
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_list_create(lv_obj_t * parent)
{
    lv_obj_t * list = lv_obj_create(parent, NULL);
    lv_obj_set_grid(list, &grid);

    return list;
}

lv_obj_t * lv_list_add_text(lv_obj_t * list, const char * txt)
{
    lv_obj_t * label = lv_label_create(list, NULL);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_obj_set_pos(label, LV_GRID_AUTO_STRETCH, LV_GRID_AUTO_START);
    return label;
}

lv_obj_t * lv_list_add_btn(lv_obj_t * list, const char * txt)
{
    lv_obj_t * label = lv_label_create(list, NULL);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_obj_set_pos(label, LV_GRID_AUTO_STRETCH, LV_GRID_AUTO_START);
    lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE);
    return label;
}

lv_obj_t * lv_list_add_btn_with_icon(lv_obj_t * list, const char * icon, const char * txt)
{
    lv_obj_t * btn = lv_btn_create(list, NULL);

    lv_obj_t * img = lv_img_create(btn, NULL);
    lv_img_set_src(img, icon);
    lv_obj_set_pos(img, LV_GRID_AUTO_START, LV_GRID_AUTO_CENTER);

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, txt);
    lv_obj_set_pos(label, LV_GRID_AUTO_STRETCH, LV_GRID_AUTO_CENTER);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);

    lv_iconbtn_ext_t * ext = lv_obj_allocate_ext_attr(btn, sizeof(lv_iconbtn_ext_t));
    _lv_memset_00(ext, sizeof(lv_iconbtn_ext_t));
    ext->col_dsc[0] = lv_obj_get_width(img);
    ext->col_dsc[1] = LV_GRID_FR(1);
    ext->grid.col_dsc = ext->col_dsc;
    ext->grid.col_dsc_len = 2;
    ext->grid.col_gap = LV_DPI / 10;

    lv_obj_set_grid(btn, &ext->grid);
    lv_obj_set_pos(btn, LV_GRID_AUTO_STRETCH, LV_GRID_AUTO_START);

    return label;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
