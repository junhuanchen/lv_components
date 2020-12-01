/**
 * @file lv_templ.h
 *
 */

#ifndef LV_TABVIEW_H
#define LV_TABVIEW_H

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
lv_obj_t * lv_tabview_create(lv_obj_t * parent, lv_dir_t tab_pos, lv_coord_t tab_size);


lv_obj_t * lv_tabview_add_tab(lv_obj_t * tv, const char * name);

lv_obj_t * lv_tabview_get_content(lv_obj_t * tv);

lv_obj_t * lv_tabview_get_tab_btns(lv_obj_t * tv);

void lv_tabview_set_act(lv_obj_t * tv, uint32_t id);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TABVIEW_H*/
