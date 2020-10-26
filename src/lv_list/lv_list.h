/**
 * @file lv_win.h
 *
 */

#ifndef LV_LIST_H
#define LV_LIST_H

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

lv_obj_t * lv_list_create(lv_obj_t * parent);

lv_obj_t * lv_list_add_text(lv_obj_t * list, const char * txt);

lv_obj_t * lv_list_add_btn(lv_obj_t * list, const char * txt);

lv_obj_t * lv_list_add_btn_with_icon(lv_obj_t * list, const char * icon, const char * txt);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_LIST_H*/
