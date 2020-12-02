/**
 * @file lv_colorwheel.h
 *
 */

#ifndef LV_COLORWHEEL_H
#define LV_COLORWHEEL_H

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

enum {
    LV_COLORWHEEL_MODE_HUE,
    LV_COLORWHEEL_MODE_SATURATION,
    LV_COLORWHEEL_MODE_VALUE
};
typedef uint8_t lv_colorwheel_mode_t;


/*Data of color picker*/
typedef struct {
    lv_color_hsv_t hsv;
    struct {
        lv_style_list_t style_list;
        lv_point_t pos;
        uint8_t recolor     : 1;
    } knob;
    uint32_t last_click_time;
    uint32_t last_change_time;
    lv_point_t last_press_point;
    lv_colorwheel_mode_t mode  : 2;
    uint8_t mode_fixed            : 1;
} lv_colorwheel_ext_t;

/*Parts*/
enum {
    LV_COLORWHEEL_PART_MAIN = LV_OBJ_PART_MAIN,
    LV_COLORWHEEL_PART_KNOB,
    _LV_COLORWHEEL_PART_VIRTUAL_LAST,
};


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a color picker objects with disc shape
 * @param parent pointer to an object, it will be the parent of the new color picker
 * @param knob_recolor true: set the knob's color to the current color
 * @return pointer to the created color picker
 */
lv_obj_t * lv_colorwheel_create(lv_obj_t * parent, bool knob_recolor);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the current hsv of a color picker.
 * @param colorwheel pointer to color picker object
 * @param hsv current selected hsv
 * @return true if changed, otherwise false
 */
bool lv_colorwheel_set_hsv(lv_obj_t * colorwheel, lv_color_hsv_t hsv);

/**
 * Set the current color of a color picker.
 * @param colorwheel pointer to color picker object
 * @param color current selected color
 * @return true if changed, otherwise false
 */
bool lv_colorwheel_set_rgb(lv_obj_t * colorwheel, lv_color_t color);

/**
 * Set the current color mode.
 * @param colorwheel pointer to color picker object
 * @param mode color mode (hue/sat/val)
 */
void lv_colorwheel_set_mode(lv_obj_t * colorwheel, lv_colorwheel_mode_t mode);

/**
 * Set if the color mode is changed on long press on center
 * @param colorwheel pointer to color picker object
 * @param fixed color mode cannot be changed on long press
 */
void lv_colorwheel_set_fixed_mode(lv_obj_t * colorwheel, bool fixed);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the current color mode.
 * @param colorwheel pointer to color picker object
 * @return color mode (hue/sat/val)
 */
lv_colorwheel_mode_t lv_colorwheel_get_mode(lv_obj_t * colorwheel);

/**
 * Get the current hue of a color picker.
 * @param colorwheel pointer to color picker object
 * @return current selected hue
 */
lv_color_hsv_t lv_colorwheel_get_hsv(lv_obj_t * colorwheel);

/**
 * Get the current selected color of a color picker.
 * @param colorwheel pointer to color picker object
 * @return current selected color
 */
lv_color_t lv_colorwheel_get_rgb(lv_obj_t * colorwheel);

/**
 * Get if the color mode is changed on long press on center
 * @param colorwheel pointer to color picker object
 * @return mode cannot be changed on long press
 */
bool lv_colorwheel_get_fix_mode(lv_obj_t * colorwheel);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif  /*LV_USE_CPICKER*/

#ifdef __cplusplus
} /* extern "C" */
#endif

