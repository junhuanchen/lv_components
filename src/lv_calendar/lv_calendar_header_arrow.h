/**
 * @file lv_calendar_header_arrow.h
 *
 */

#ifndef LV_CALENDAR_HEADER_ARROW_H
#define LV_CALENDAR_HEADER_ARROW_H

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
typedef struct {
    lv_obj_t * calendar;
    const char ** month_names;
}lv_calendar_header_arrow_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a calendar objects
 * @param par pointer to an object, it will be the parent of the new calendar
 * @param copy pointer to a calendar object, if not NULL then the new object will be copied from it
 * @return pointer to the created calendar
 */
lv_obj_t * lv_calendar_header_arrow_create(lv_obj_t * parent, lv_obj_t * calendar, const char * month_names[], lv_coord_t btn_size);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_CALENDAR_H*/
