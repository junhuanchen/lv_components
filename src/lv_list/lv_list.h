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
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif

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

lv_obj_t * lv_list_add_btn(lv_obj_t * list, const char * icon, const char * txt, lv_event_cb_t event_cb);

const char * lv_list_get_btn_text(lv_obj_t * btn);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_LIST_H*/
