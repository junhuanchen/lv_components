/**
 * @file lv_win.h
 *
 */

#ifndef LV_WIN_H
#define LV_WIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * lv_win_create(lv_obj_t * parent,  const char * title, lv_coord_t header_height, lv_coord_t btn_w, lv_coord_t btn_h);

lv_obj_t * lv_win_add_btn(lv_obj_t * win, lv_dir_t dir, const void * icon, lv_event_cb_t event_cb);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_WIN_H*/
