/**
 * @file lv_spinner.h
 *
 */

#ifndef LV_SPINNER_H
#define LV_SPINNER_H

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

/*Testing of dependencies*/
#if LV_USE_ARC == 0
#error "lv_spinner: lv_arc is required. Enable it in lv_conf.h (LV_USE_ARC  1) "
#endif

#if LV_USE_ANIMATION == 0
#error "lv_spinner: animations are required. Enable it in lv_conf.h (LV_USE_ANIMATION  1) "
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

lv_obj_t * lv_spinner_create(lv_obj_t * par, uint32_t time, uint32_t arc_length);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_SPINNER_H*/
