/**
 * @file lv_calendar_header_arrow.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_calendar_header_arrow.h"
#include "lv_calendar.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void month_event_cb(lv_obj_t * btn, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
static bool inited = false;
static const char * month_names_def[12] = {"January", "February", "March",     "April",   "May",      "June",
                                      "July",    "August",   "September", "October", "November", "December"
                                     };

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_calendar_header_arrow_create(lv_obj_t * parent, lv_obj_t * calendar, const char * month_names[], lv_coord_t btn_size)
{
    static lv_style_t style_bg;
    if(!inited) {
        lv_style_init(&style_bg);
        lv_style_set_radius(&style_bg, LV_STATE_DEFAULT, 0);
        lv_style_set_pad_all(&style_bg, LV_STATE_DEFAULT, 10);
        lv_style_set_border_side(&style_bg, LV_STATE_DEFAULT, LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_TOP);
    }

    lv_obj_t * header = lv_obj_create(parent, NULL);

    lv_calendar_header_arrow_ext_t * ext = lv_obj_allocate_ext_attr(header, sizeof(lv_calendar_header_arrow_ext_t));
    _lv_memset_00(ext, sizeof(lv_calendar_header_arrow_ext_t));
    ext->calendar = calendar;
    ext->month_names = month_names == NULL ? month_names_def : month_names;

    lv_calendar_date_t * cur_date = lv_calendar_get_showed_date(calendar);

    lv_obj_add_style(header, LV_OBJ_PART_MAIN, &style_bg);
    lv_coord_t w = calendar ? lv_obj_get_width(calendar) : 2 * LV_DPI;
    lv_obj_set_size(header,  w, LV_SIZE_AUTO);
    lv_obj_set_flex_dir(header, LV_FLEX_DIR_ROW);
    lv_obj_set_flex_place(header, LV_FLEX_PLACE_START, LV_FLEX_PLACE_CENTER);

    lv_obj_t * mo_prev = lv_btn_create(header, NULL);
    lv_obj_set_style_local_value_str(mo_prev,  LV_BTN_PART_MAIN, LV_STATE_DEFAULT,  LV_SYMBOL_LEFT);
    lv_obj_set_flex_item_place(mo_prev, LV_FLEX_PLACE_START);
    lv_obj_set_size(mo_prev, btn_size, btn_size);
    lv_obj_set_event_cb(mo_prev, month_event_cb);

    lv_obj_t * label = lv_label_create(header, NULL);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
    lv_obj_set_flex_item_place(label, LV_FLEX_PLACE_CENTER);
    lv_obj_set_width(label, LV_FLEX_GROW(1));
    lv_label_set_text_fmt(label, "%d %s", cur_date->year, ext->month_names[cur_date->month - 1]);

    lv_obj_t * mo_next = lv_btn_create(header, NULL);
    lv_obj_set_style_local_value_str(mo_next,  LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_RIGHT);
    lv_obj_set_flex_item_place(mo_next, LV_FLEX_PLACE_START);
    lv_obj_set_size(mo_next, btn_size, btn_size);
    lv_obj_set_event_cb(mo_next, month_event_cb);

    return header;
}

/**********************
 *  STATIC FUNCTIONS
 **********************/
static void month_event_cb(lv_obj_t * btn, lv_event_t e)
{
    if(e != LV_EVENT_CLICKED) return;

    lv_obj_t * header = lv_obj_get_parent(btn);
    lv_calendar_header_arrow_ext_t * ext = lv_obj_get_ext_attr(header);

    if(ext->calendar == NULL) return;

    lv_calendar_date_t * d;
    d = lv_calendar_get_showed_date(ext->calendar);
    lv_calendar_date_t newd = *d;

    /*The last child is the right button*/
    if(lv_obj_get_child(header, NULL) == btn) {
        if(newd.month == 12) {
            newd.month = 1;
            newd.year ++;
        } else {
            newd.month ++;
        }
    } else {
        if(newd.month == 1) {
            newd.month = 12;
            newd.year --;
        } else {
            newd.month --;
        }
    }

    lv_calendar_set_showed_date(ext->calendar, &newd);

    lv_obj_t * label = lv_obj_get_child_by_id(header, 1);
    lv_label_set_text_fmt(label, "%d %s", newd.year, ext->month_names[newd.month - 1]);
}
