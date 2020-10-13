/**
 * @file lv_led.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_led.h"

/*********************
 *      DEFINES
 *********************/

#define LV_LED_WIDTH_DEF (LV_DPI / 3)
#define LV_LED_HEIGHT_DEF (LV_DPI / 3)

#ifndef LV_LED_BRIGHT_MIN
# define LV_LED_BRIGHT_MIN 120
#endif

#ifndef LV_LED_BRIGHT_MAX
# define LV_LED_BRIGHT_MAX 255
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_design_res_t lv_led_design(lv_obj_t * led, const lv_area_t * clip_area, lv_design_mode_t mode);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_design_cb_t ancestor_design;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a led objects
 * @param par pointer to an object, it will be the parent of the new led
 * @param copy pointer to a led object, if not NULL then the new object will be copied from it
 * @return pointer to the created led
 */
lv_obj_t * lv_led_create(lv_obj_t * parent)
{
    LV_LOG_TRACE("led create started");

    /*Create the ancestor basic object*/
    lv_obj_t * led = lv_obj_create(parent, NULL);
    LV_ASSERT_MEM(led);
    if(led == NULL) return NULL;

    if(ancestor_design == NULL) ancestor_design = lv_obj_get_design_cb(led);

    /*Allocate the object type specific extended data*/
    lv_led_ext_t * ext = lv_obj_allocate_ext_attr(led, sizeof(lv_led_ext_t));
    LV_ASSERT_MEM(ext);
    if(ext == NULL) {
        lv_obj_del(led);
        return NULL;
    }

    ext->bright = LV_LED_BRIGHT_MAX;

    lv_obj_set_design_cb(led, lv_led_design);
    lv_obj_set_size(led, LV_LED_WIDTH_DEF, LV_LED_HEIGHT_DEF);

    LV_LOG_INFO("led created");

    return led;
}

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the brightness of a LED object
 * @param led pointer to a LED object
 * @param bright LV_LED_BRIGHT_MIN (max. dark) ... LV_LED_BRIGHT_MAX (max. light)
 */
void lv_led_set_bright(lv_obj_t * led, uint8_t bright)
{
    LV_ASSERT_OBJ(led, LV_OBJX_NAME);

    /*Set the brightness*/
    lv_led_ext_t * ext = lv_obj_get_ext_attr(led);
    if(ext->bright == bright) return;

    if(bright <= LV_LED_BRIGHT_MIN) bright = LV_LED_BRIGHT_MIN;
    if(bright >= LV_LED_BRIGHT_MAX) bright = LV_LED_BRIGHT_MAX;

    ext->bright = bright;

    /*Invalidate the object there fore it will be redrawn*/
    lv_obj_invalidate(led);
}

/**
 * Light on a LED
 * @param led pointer to a LED object
 */
void lv_led_on(lv_obj_t * led)
{
    LV_ASSERT_OBJ(led, LV_OBJX_NAME);

    lv_led_set_bright(led, LV_LED_BRIGHT_MAX);
}

/**
 * Light off a LED
 * @param led pointer to a LED object
 */
void lv_led_off(lv_obj_t * led)
{
    LV_ASSERT_OBJ(led, LV_OBJX_NAME);

    lv_led_set_bright(led, LV_LED_BRIGHT_MIN);
}

/**
 * Toggle the state of a LED
 * @param led pointer to a LED object
 */
void lv_led_toggle(lv_obj_t * led)
{
    LV_ASSERT_OBJ(led, LV_OBJX_NAME);

    uint8_t bright = lv_led_get_bright(led);
    if(bright > (LV_LED_BRIGHT_MIN + LV_LED_BRIGHT_MAX) >> 1)
        lv_led_off(led);
    else
        lv_led_on(led);
}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the brightness of a LEd object
 * @param led pointer to LED object
 * @return bright 0 (max. dark) ... 255 (max. light)
 */
uint8_t lv_led_get_bright(const lv_obj_t * led)
{
    LV_ASSERT_OBJ(led, LV_OBJX_NAME);

    lv_led_ext_t * ext = lv_obj_get_ext_attr(led);
    return ext->bright;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Handle the drawing related tasks of the leds
 * @param led pointer to an object
 * @param clip_area the object will be drawn only in this area
 * @param mode LV_DESIGN_COVER_CHK: only check if the object fully covers the 'mask_p' area
 *                                  (return 'true' if yes)
 *             LV_DESIGN_DRAW: draw the object (always return 'true')
 *             LV_DESIGN_DRAW_POST: drawing after every children are drawn
 * @param return an element of `lv_design_res_t`
 */
static lv_design_res_t lv_led_design(lv_obj_t * led, const lv_area_t * clip_area, lv_design_mode_t mode)
{
    if(mode == LV_DESIGN_COVER_CHK) {
        /*Return false if the object is not covers the clip_area area*/
        return ancestor_design(led, clip_area, mode);
    }
    else if(mode == LV_DESIGN_DRAW_MAIN) {
        /*Make darker colors in a temporary style according to the brightness*/
        lv_led_ext_t * ext       = lv_obj_get_ext_attr(led);

        lv_draw_rect_dsc_t rect_dsc;
        lv_draw_rect_dsc_init(&rect_dsc);
        lv_obj_init_draw_rect_dsc(led, LV_OBJ_PART_MAIN, &rect_dsc);

        /*Mix. the color with black proportionally with brightness*/
        rect_dsc.bg_color   = lv_color_mix(rect_dsc.bg_color, LV_COLOR_BLACK, ext->bright);
        rect_dsc.bg_grad_color   = lv_color_mix(rect_dsc.bg_grad_color, LV_COLOR_BLACK, ext->bright);
        rect_dsc.border_color = lv_color_mix(rect_dsc.border_color, LV_COLOR_BLACK, ext->bright);
        rect_dsc.shadow_color = lv_color_mix(rect_dsc.shadow_color, LV_COLOR_BLACK, ext->bright);

        /*Set the current shadow width according to brightness proportionally between LV_LED_BRIGHT_OFF
         * and LV_LED_BRIGHT_ON*/
        rect_dsc.shadow_width = ((ext->bright - LV_LED_BRIGHT_MIN) * rect_dsc.shadow_width) /
                                (LV_LED_BRIGHT_MAX - LV_LED_BRIGHT_MIN);
        rect_dsc.shadow_spread = ((ext->bright - LV_LED_BRIGHT_MIN) * rect_dsc.shadow_spread) /
                                 (LV_LED_BRIGHT_MAX - LV_LED_BRIGHT_MIN);

        lv_draw_rect(&led->coords, clip_area, &rect_dsc);
    }
    return LV_DESIGN_RES_OK;
}
