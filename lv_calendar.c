/**
 * @file lv_calendar.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_calendar.h"

/*********************
 *      DEFINES
 *********************/
#define LV_OBJX_NAME "lv_calendar"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static uint8_t get_day_of_week(uint32_t year, uint32_t month, uint32_t day);
static uint8_t get_month_length(int32_t year, int32_t month);
static uint8_t is_leap_year(uint32_t year);
static void highlight_update(lv_obj_t * calendar);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a calendar object
 * @param par pointer to an object, it will be the parent of the new calendar
 * @param copy pointer to a calendar object, if not NULL then the new object will be copied from it
 * @return pointer to the created calendar
 */
lv_obj_t * lv_calendar_create(lv_obj_t * parent)
{
    /*Create the ancestor of calendar*/
    lv_obj_t * calendar = lv_btnmatrix_create(parent, NULL);
    LV_ASSERT_MEM(calendar);
    if(calendar == NULL) return NULL;

    /*Allocate the calendar type specific extended data*/
    lv_calendar_ext_t * ext = lv_obj_allocate_ext_attr(calendar, sizeof(lv_calendar_ext_t));
    LV_ASSERT_MEM(ext);
    if(ext == NULL) {
        lv_obj_del(calendar);
        return NULL;
    }

    /*Initialize the allocated 'ext' */
    ext->today.year  = 2020;
    ext->today.month = 1;
    ext->today.day   = 1;

    ext->showed_date.year  = 2020;
    ext->showed_date.month = 1;
    ext->showed_date.day   = 1;

    ext->highlighted_dates      = NULL;
    ext->highlighted_dates_num  = 0;

    lv_obj_set_size(calendar, 5 * LV_DPI / 2, 5 * LV_DPI / 2);

    _lv_memset_00(ext->nums, sizeof(ext->nums));
    uint8_t i;
    uint8_t j = 0;
    for(i = 0; i < 8 * 7; i++) {
        /*Every 8th string is "\n"*/
        if(i != 0 && (i + 1) % 8 == 0) {
            ext->map[i] = "\n";
        } else if(i < 8){
            ext->map[i] = "a";
        } else {
            ext->nums[j][0] = 'x';
            ext->map[i] = ext->nums[j];
            j++;
        }
    }
    ext->map[8 * 7 - 1] = "";

    lv_btnmatrix_set_map(calendar, ext->map);

    for(i = 0; i < 7; i++) {
        lv_btnmatrix_set_btn_ctrl(calendar, i, LV_BTNMATRIX_CTRL_TYPE_2);
    }

    lv_calendar_set_today_date(calendar, &ext->today);

    return calendar;
}

/*======================
 * Add/remove functions
 *=====================*/

/*
 * New object specific "add" or "remove" functions come here
 */

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the today's date
 * @param calendar pointer to a calendar object
 * @param today pointer to an `lv_calendar_date_t` variable containing the date of today. The value
 * will be saved it can be local variable too.
 */
void lv_calendar_set_today_date(lv_obj_t * calendar, lv_calendar_date_t * today)
{
    LV_ASSERT_OBJ(calendar, LV_OBJX_NAME);
    LV_ASSERT_NULL(today);

    lv_calendar_ext_t * ext = lv_obj_get_ext_attr(calendar);
    ext->today.year         = today->year;
    ext->today.month        = today->month;
    ext->today.day          = today->day;

    lv_calendar_date_t d;
    d.year = today->year;
    d.month = today->month;
    d.day = 0;

    uint8_t mo_len = get_month_length(d.year, d.month);
    uint8_t day_first = get_day_of_week(d.year, d.month, d.day);
    uint8_t i;
    uint8_t c;
    for(i = day_first, c = 1; i < mo_len + day_first; i++, c++) {
        lv_snprintf(ext->nums[i], sizeof(ext->nums[0]), "%d", c);
    }

    mo_len = get_month_length(today->year, today->month - 1);
    for(i = 0, c = mo_len - day_first + 1; i < day_first; i++, c++) {
        lv_snprintf(ext->nums[i], sizeof(ext->nums[0]), "%d", c);
        lv_btnmatrix_set_btn_ctrl(calendar, i + 7, LV_BTNMATRIX_CTRL_DISABLED);
    }

    mo_len = get_month_length(today->year, today->month + 1);
    for(i = day_first + mo_len, c = 1; i < 6 * 7; i++, c++) {
        lv_snprintf(ext->nums[i], sizeof(ext->nums[0]), "%d", c);
        lv_btnmatrix_set_btn_ctrl(calendar, i + 7, LV_BTNMATRIX_CTRL_DISABLED);
    }

    lv_btnmatrix_set_map(calendar, ext->map);

    highlight_update(calendar);
}

/**
 * Set the currently showed
 * @param calendar pointer to a calendar object
 * @param showed pointer to an `lv_calendar_date_t` variable containing the date to show. The value
 * will be saved it can be local variable too.
 */
void lv_calendar_set_showed_date(lv_obj_t * calendar, lv_calendar_date_t * showed)
{
    LV_ASSERT_OBJ(calendar, LV_OBJX_NAME);
    LV_ASSERT_NULL(showed);

    lv_calendar_ext_t * ext = lv_obj_get_ext_attr(calendar);
    ext->showed_date.year   = showed->year;
    ext->showed_date.month  = showed->month;
    ext->showed_date.day    = showed->day;

    lv_obj_invalidate(calendar);
}

/**
 * Set the the highlighted dates
 * @param calendar pointer to a calendar object
 * @param highlighted pointer to an `lv_calendar_date_t` array containing the dates. ONLY A POINTER
 * WILL BE SAVED! CAN'T BE LOCAL ARRAY.
 * @param date_num number of dates in the array
 */
void lv_calendar_set_highlighted_dates(lv_obj_t * calendar, lv_calendar_date_t highlighted[], uint16_t date_num)
{
    LV_ASSERT_OBJ(calendar, LV_OBJX_NAME);
    LV_ASSERT_NULL(highlighted);

    lv_calendar_ext_t * ext    = lv_obj_get_ext_attr(calendar);
    ext->highlighted_dates     = highlighted;
    ext->highlighted_dates_num = date_num;

    highlight_update(calendar);

}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the today's date
 * @param calendar pointer to a calendar object
 * @return return pointer to an `lv_calendar_date_t` variable containing the date of today.
 */
lv_calendar_date_t * lv_calendar_get_today_date(const lv_obj_t * calendar)
{
    LV_ASSERT_OBJ(calendar, LV_OBJX_NAME);

    lv_calendar_ext_t * ext = lv_obj_get_ext_attr(calendar);
    return &ext->today;
}

/**
 * Get the currently showed
 * @param calendar pointer to a calendar object
 * @return pointer to an `lv_calendar_date_t` variable containing the date is being shown.
 */
lv_calendar_date_t * lv_calendar_get_showed_date(const lv_obj_t * calendar)
{
    LV_ASSERT_OBJ(calendar, LV_OBJX_NAME);

    lv_calendar_ext_t * ext = lv_obj_get_ext_attr(calendar);
    return &ext->showed_date;
}

/**
 * Get the the highlighted dates
 * @param calendar pointer to a calendar object
 * @return pointer to an `lv_calendar_date_t` array containing the dates.
 */
lv_calendar_date_t * lv_calendar_get_highlighted_dates(const lv_obj_t * calendar)
{
    LV_ASSERT_OBJ(calendar, LV_OBJX_NAME);

    lv_calendar_ext_t * ext = lv_obj_get_ext_attr(calendar);
    return ext->highlighted_dates;
}

/**
 * Get the number of the highlighted dates
 * @param calendar pointer to a calendar object
 * @return number of highlighted days
 */
uint16_t lv_calendar_get_highlighted_dates_num(const lv_obj_t * calendar)
{
    LV_ASSERT_OBJ(calendar, LV_OBJX_NAME);

    lv_calendar_ext_t * ext = lv_obj_get_ext_attr(calendar);
    return ext->highlighted_dates_num;
}


/**********************
 *  STATIC FUNCTIONS
 **********************/

/**
 * Get the number of days in a month
 * @param year a year
 * @param month a month. The range is basically [0..11] but [-11..0] or [12..23] is also
 *              supported to handle next/prev. year
 * @return [28..31]
 */
static uint8_t get_month_length(int32_t year, int32_t month)
{
    if(month < 0) {
        year--;             /*Already in the previous year (won't be less then -12 to skip a whole year)*/
        month = 12 + month; /*`month` is negative, the result will be < 12*/
    }
    if(month >= 12) {
        year++;
        month -= 12;
    }

    /*month == 1 is february*/
    return (month == 1) ? (28 + is_leap_year(year)) : 31 - month % 7 % 2;
}

/**
 * Tells whether a year is leap year or not
 * @param year a year
 * @return 0: not leap year; 1: leap year
 */
static uint8_t is_leap_year(uint32_t year)
{
    return (year % 4) || ((year % 100 == 0) && (year % 400)) ? 0 : 1;
}

/**
 * Get the day of the week
 * @param year a year
 * @param month a  month
 * @param day a day
 * @return [0..6] which means [Sun..Sat] or [Mon..Sun] depending on LV_CALENDAR_WEEK_STARTS_MONDAY
 */
static uint8_t get_day_of_week(uint32_t year, uint32_t month, uint32_t day)
{
    uint32_t a = month < 3 ? 1 : 0;
    uint32_t b = year - a;

#if LV_CALENDAR_WEEK_STARTS_MONDAY
    uint32_t day_of_week = (day + (31 * (month - 2 + 12 * a) / 12) + b + (b / 4) - (b / 100) + (b / 400) - 1) % 7;
#else
    uint32_t day_of_week = (day + (31 * (month - 2 + 12 * a) / 12) + b + (b / 4) - (b / 100) + (b / 400)) % 7;
#endif

    return day_of_week;
}

static void highlight_update(lv_obj_t * calendar)
{
    lv_calendar_ext_t * ext = lv_obj_get_ext_attr(calendar);

    lv_btnmatrix_clear_btn_ctrl_all(calendar, LV_BTNMATRIX_CTRL_CHECKED);
    uint16_t i;
    if(ext->highlighted_dates) {
        for(i = 0; i < ext->highlighted_dates_num; i++) {
            if(ext->highlighted_dates[i].year == ext->today.year && ext->highlighted_dates[i].month == ext->showed_date.month) {
                lv_btnmatrix_set_btn_ctrl(calendar, ext->highlighted_dates[i].day + 7, LV_BTNMATRIX_CTRL_CHECKED);
            }
        }
    }

    if(ext->showed_date.year == ext->today.year && ext->showed_date.month == ext->today.month) {
        uint8_t day_first = get_day_of_week(ext->today.year, ext->today.month, ext->today.day - 1);
        lv_btnmatrix_set_btn_ctrl(calendar, ext->today.day - 1 + day_first + 7, LV_BTNMATRIX_CTRL_TYPE_2 | LV_BTNMATRIX_CTRL_CHECKED);
    }
}
