/**
 * @file lv_components.h
 *
 */

#ifndef LV_COMPONENTS_H
#define LV_COMPONENTS_H

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

#if defined(LV_COMP_CONF_PATH)
#define __LV_TO_STR_AUX(x) #x
#define __LV_TO_STR(x) __LV_TO_STR_AUX(x)
#include __LV_TO_STR(LV_COMP_CONF_PATH)
#undef __LV_TO_STR_AUX
#undef __LV_TO_STR
#elif defined(LV_COMP_CONF_INCLUDE_SIMPLE)
#include "lv_comp_conf.h"
#else
#include "../lv_comp_conf.h"
#endif

#include "src/lv_calendar/lv_calendar.h"
#include "src/lv_calendar/lv_calendar_header_arrow.h"
#include "src/lv_colorwheel/lv_colorwheel.h"
#include "src/lv_keyboard/lv_keyboard.h"
#include "src/lv_led/lv_led.h"
#include "src/lv_list/lv_list.h"
#include "src/lv_msgbox/lv_msgbox.h"
#include "src/lv_spinbox/lv_spinbox.h"
#include "src/lv_spinner/lv_spinner.h"
#include "src/lv_tabview/lv_tabview.h"
#include "src/lv_tileview/lv_tileview.h"
#include "src/lv_win/lv_win.h"

/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#if LV_VERSION_CHECK(8, 0, 0) == 0
#error "lv_components: Wrong lvgl version"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_COMPONENTS_H*/
