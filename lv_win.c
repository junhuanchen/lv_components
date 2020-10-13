/**
 * @file lv_win.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_win.h"

/*********************
 *      DEFINES
 *********************/
#define LV_WIN_BTN_CONF(left, right) ((left) << 8) + right)

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_obj_t * title;
    lv_grid_t grid_main;
    lv_grid_t grid_header;
    lv_coord_t grid_main_row_dsc[2];
    lv_coord_t btn_w;
    lv_coord_t btn_h;
}lv_win_ext_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_coord_t grid_fr1 = LV_GRID_FR(1);

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_win_create(lv_obj_t * parent,  const char * title, lv_coord_t header_height, lv_coord_t btn_w, lv_coord_t btn_h)
{
    lv_obj_t * win = lv_obj_create(parent, NULL);
    lv_win_ext_t * ext = lv_obj_allocate_ext_attr(win, sizeof(lv_win_ext_t));

    _lv_memset_00(ext, sizeof(lv_win_ext_t));

    ext->btn_w = btn_w;
    ext->btn_h = btn_h;

    ext->grid_main_row_dsc[0] = header_height;
    ext->grid_main_row_dsc[1] = LV_GRID_FR(1);

    ext->grid_main.col_dsc = &grid_fr1;
    ext->grid_main.col_dsc_len = 1;
    ext->grid_main.row_dsc = ext->grid_main_row_dsc;
    ext->grid_main.row_dsc_len = 2;


    lv_obj_set_size(win, 220, 200);
    lv_obj_set_grid(win, &ext->grid_main);

    lv_coord_t * grid_header_col_dsc = lv_mem_alloc(sizeof(lv_coord_t));
    grid_header_col_dsc[0] = LV_GRID_FR(1);

    ext->grid_header.col_dsc_len = 1;
    ext->grid_header.col_dsc = grid_header_col_dsc;
    ext->grid_header.col_gap = 10;
    ext->grid_header.row_place = LV_GRID_CENTER;

    lv_obj_t * header = lv_obj_create(win, NULL);
    lv_obj_set_pos(header, LV_GRID_CELL_STRETCH(0, 1), LV_GRID_CELL_STRETCH(0, 1));
    lv_obj_set_grid(header, &ext->grid_header);

    ext->title = lv_label_create(header, NULL);
    lv_obj_set_pos(ext->title, LV_GRID_CELL_STRETCH(0, 1), LV_GRID_CELL_CENTER(0, 1));
    lv_label_set_long_mode(ext->title, LV_LABEL_LONG_DOT);
    lv_label_set_text(ext->title, title);

    lv_obj_t * cont = lv_obj_create(win, NULL);
    lv_obj_set_pos(cont, LV_GRID_CELL_STRETCH(0, 1), LV_GRID_CELL_STRETCH(1, 1));

   lv_obj_t * c =  lv_label_create(cont, NULL);
   lv_label_set_text(c, "adssssssssssss\n\n\n\n\n\n\n\nvasdas\n\n\n\n\ndfddd\n\n\nd");

   return win;
}

lv_obj_t * lv_win_add_btn(lv_obj_t * win, lv_dir_t dir, const void * icon, lv_event_cb_t event_cb)
{
    lv_win_ext_t * ext = lv_obj_get_ext_attr(win);

    lv_obj_t * header = lv_obj_get_child_back(win, NULL);
    lv_obj_t * btn = lv_btn_create(header, NULL);
    lv_obj_set_size(btn, ext->btn_w, ext->btn_h);
    ext->grid_header.col_dsc = lv_mem_realloc(ext->grid_header.col_dsc, (ext->grid_header.col_dsc_len + 1) * sizeof(lv_coord_t));
    ext->grid_header.col_dsc_len++;
    lv_coord_t * col_tmp = (lv_coord_t *) ext->grid_header.col_dsc;
    uint8_t i;
    if(dir == LV_DIR_LEFT) {
        for(i = ext->grid_header.col_dsc_len - 1; i > 0; i--) {
            col_tmp[i] = col_tmp[i -1];
        }
        col_tmp[i] = ext->btn_w;
        lv_obj_move_background(btn);
        lv_obj_set_pos(btn, LV_GRID_CELL_CENTER(0, 1), LV_GRID_CELL_CENTER(0, 1));
    }
    else if(dir == LV_DIR_RIGHT) {
        col_tmp[ext->grid_header.col_dsc_len - 1] = ext->btn_w;
        lv_obj_set_pos(btn, LV_GRID_CELL_CENTER(0, 1), LV_GRID_CELL_CENTER(0, 1));
    }

    lv_obj_t * img = lv_img_create(btn, NULL);
    lv_img_set_src(img, icon);
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);

    return btn;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
