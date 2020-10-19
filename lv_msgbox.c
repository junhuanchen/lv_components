/**
 * @file lv_msgbox.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_msgbox.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

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
 * Create a message box objects
 * @param par pointer to an object, it will be the parent of the new message box
 * @param copy pointer to a message box object, if not NULL then the new object will be copied from
 * it
 * @return pointer to the created message box
 */
lv_obj_t * lv_msgbox_create(lv_obj_t * parent, const char * title, const char * txt, const char * btn_txts[])
{
    /*Create the ancestor message box*/
    lv_obj_t * mbox = lv_obj_create(parent, NULL);
    LV_ASSERT_MEM(mbox);
    if(mbox == NULL) return NULL;

    lv_coord_t w = lv_obj_get_width_fit(parent);
    if(w > 2 * LV_DPI) w = 2 * LV_DPI;

    lv_obj_set_size(mbox, w, LV_SIZE_AUTO);
    lv_obj_set_flex_cont(mbox, LV_FLEX_DIR_COLUMN);

    lv_obj_t * label;
    label = lv_label_create(mbox, NULL);
    lv_label_set_text(label, title);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_width(label, LV_COORD_PCT(100));
    lv_obj_set_flex_item(label, LV_FLEX_START);

    label = lv_label_create(mbox, NULL);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_width(label, LV_COORD_PCT(100));
    lv_obj_set_flex_item(label, LV_FLEX_START);

    lv_obj_t * btns = lv_btnmatrix_create(mbox, NULL);
    lv_btnmatrix_set_map(btns, btn_txts);
    lv_obj_set_flex_item(btns, LV_FLEX_END);

    uint32_t btn_cnt = 0;
    while(btn_txts[btn_cnt][0] != '\0') {
        btn_cnt++;
    }

    const lv_font_t * font = lv_obj_get_style_text_font(btns, LV_BTNMATRIX_PART_BTN);
    lv_coord_t btn_h = lv_font_get_line_height(font) + LV_DPI / 3;
    lv_obj_set_size(btns, btn_cnt * (2 * LV_DPI / 3), btn_h);
    lv_obj_add_flag(btns, LV_OBJ_FLAG_EVENT_BUBBLE);    /*To see the event directly on the message box*/
    return mbox;
}


lv_obj_t * lv_msgboxget_title(lv_obj_t * mbox)
{
    return lv_obj_get_child_by_id(mbox, 0);
}

lv_obj_t * lv_msgboxget_text(lv_obj_t * mbox)
{
    return lv_obj_get_child_by_id(mbox, 1);
}

lv_obj_t * lv_msgboxget_btns(lv_obj_t * mbox)
{
    return lv_obj_get_child_by_id(mbox, 2);
}
