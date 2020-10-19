/**
 * @file lv_tileview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_tileview.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct
{
    lv_dir_t dir;
}lv_tile_ext_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void tileview_event_cb(lv_obj_t * tv, lv_event_t e);

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
 * Create a tileview object
 * @param par pointer to an object, it will be the parent of the new tileview
 * @param copy pointer to a tileview object, if not NULL then the new object will be copied from it
 * @return pointer to the created tileview
 */
lv_obj_t * lv_tileview_create(lv_obj_t * parent)
{
    LV_LOG_TRACE("tileview create started");

    /*Create the ancestor of tileview*/
    lv_obj_t * tileview = lv_obj_create(parent, NULL);
    LV_ASSERT_MEM(tileview);
    if(tileview == NULL) return NULL;

    lv_coord_t w;
    lv_coord_t h;
    if(parent) {
        w = lv_obj_get_width_fit(lv_obj_get_parent(tileview));
        h = lv_obj_get_height_fit(lv_obj_get_parent(tileview));
    }
    else {
        w = lv_disp_get_hor_res(NULL);
        h = lv_disp_get_ver_res(NULL);
    }

    lv_obj_set_size(tileview, w, h);
    lv_obj_set_event_cb(tileview, tileview_event_cb);
    lv_obj_add_flag(tileview, LV_OBJ_FLAG_SCROLL_STOP);
    tileview->snap_align_x = LV_SCROLL_SNAP_ALIGN_CENTER;
    tileview->snap_align_y = LV_SCROLL_SNAP_ALIGN_CENTER;
    return tileview;
}

/*======================
 * Add/remove functions
 *=====================*/

lv_obj_t * lv_tileview_add_tile(lv_obj_t * tv, uint8_t col_id, uint8_t row_id, lv_dir_t dir)
{
    lv_obj_t * tile = lv_obj_create(tv, NULL);
    lv_obj_set_size(tile, LV_COORD_PCT(100), LV_COORD_PCT(100));
    lv_obj_set_pos(tile, col_id * lv_obj_get_width_fit(tv),  row_id * lv_obj_get_height_fit(tv));

    lv_tile_ext_t * ext = lv_obj_allocate_ext_attr(tile, sizeof(lv_tile_ext_t));

    ext->dir = dir;

    if(col_id == 0 && row_id == 0) {
        tv->scroll_dir = dir;
    }

    return tile;
}

void lv_obj_set_tile(lv_obj_t * tv, lv_obj_t * tile, lv_anim_enable_t anim_en)
{
    lv_coord_t tx = lv_obj_get_x(tile);
    lv_coord_t ty = lv_obj_get_y(tile);

    lv_tile_ext_t * ext = lv_obj_get_ext_attr(tile);
    tv->scroll_dir = ext->dir;

    lv_obj_scroll_to(tv, tx, ty, anim_en);
}

void lv_obj_set_tile_id(lv_obj_t * tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en)
{
    lv_coord_t w = lv_obj_get_width_fit(tv);
    lv_coord_t h = lv_obj_get_height_fit(tv);

    lv_coord_t tx = col_id * w;
    lv_coord_t ty = row_id * h;

    tv->scroll_dir = LV_DIR_ALL;
    lv_obj_t * tile = lv_obj_get_child(tv, NULL);
    while(tile) {
        lv_coord_t x = lv_obj_get_x(tile);
        lv_coord_t y = lv_obj_get_y(tile);
        if(x == tx && y == ty) {
            lv_tile_ext_t * ext = lv_obj_get_ext_attr(tile);
            tv->scroll_dir = ext->dir;
            break;
        }
        tile = lv_obj_get_child(tv, tile);
    }

    lv_obj_scroll_to(tv, tx, ty, anim_en);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void tileview_event_cb(lv_obj_t * tv, lv_event_t e)
{
    if(e == LV_EVENT_SCROLL_END) {
        lv_coord_t w = lv_obj_get_width_fit(tv);
        lv_coord_t h = lv_obj_get_height_fit(tv);

        lv_point_t scroll_end;
        lv_obj_get_scroll_end(tv, &scroll_end);
        lv_coord_t left = scroll_end.x;
        lv_coord_t top = scroll_end.y;

        lv_coord_t tx = ((left + (w / 2)) / w) * w;
        lv_coord_t ty = ((top + (h / 2)) / h) * h;

        tv->scroll_dir = LV_DIR_ALL;
        lv_obj_t * tile = lv_obj_get_child(tv, NULL);
        while(tile) {
            lv_coord_t x = lv_obj_get_x(tile);
            lv_coord_t y = lv_obj_get_y(tile);
            if(x == tx && y == ty) {
                lv_tile_ext_t * ext = lv_obj_get_ext_attr(tile);
                tv->scroll_dir = ext->dir;
                break;
            }
            tile = lv_obj_get_child(tv, tile);
        }
    }
}
