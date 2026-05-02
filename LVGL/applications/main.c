/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-23     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <drv_common.h>
#include "agile_button.h"

#include "drv_JHD_LCD.h"

#include <lvgl.h>

#include "main_btn.h"

static agile_btn_t _sbtn;


lv_obj_t *scr1;
lv_obj_t *scr2;


static void auto_switch_timer(lv_timer_t * t)
{
    static uint8_t cur = 0;

    if(cur == 0)
    {
        lv_obj_add_flag(scr1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(scr2, LV_OBJ_FLAG_HIDDEN);
        cur = 1;
    }
    else
    {
        lv_obj_add_flag(scr2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(scr1, LV_OBJ_FLAG_HIDDEN);
        cur = 0;
    }
}
static lv_obj_t * time_label;
static lv_obj_t * date_label;

static void clock_timer_cb(lv_timer_t * t)
{
    static uint32_t sec = 0;

    sec++;

    uint32_t hour = (sec / 3600) % 24;
    uint32_t min  = (sec / 60) % 60;
    uint32_t s    = sec % 60;

    char buf[32];

    // 更新时间
    lv_snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hour, min, s);
    lv_label_set_text(time_label, buf);

    // 更新日期（这里简单写死，可以换RTC）
    lv_snprintf(buf, sizeof(buf), "2026-05-02");
    lv_label_set_text(date_label, buf);
}


void lv_user_gui_init(void)
{
    /* 获取默认显示器的活动屏幕 */
//    lv_obj_t *scr = lv_scr_act();
//    lv_obj_clean(scr); /* 清屏 */
//
//    /* 创建界面启动界面 */
//    lv_obj_t *page = lv_obj_create(scr);
//    lv_obj_set_size(page, LV_HOR_RES-2, LV_VER_RES-2);
//    lv_obj_set_style_bg_color(page, lv_color_white(), LV_PART_MAIN);            /* 设置背景颜色 */
//    lv_obj_set_style_radius(page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);          /* 设置导角为0 */
//    lv_obj_set_style_border_width(page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);    /* 设置边框为0 */
//
//    /* 添加标签 */
//    lv_obj_t *label = lv_label_create(page);
//    lv_label_set_text(label, "Hello LVGL, --QuinnW");
//    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

//    // 页面1
//    scr1 = lv_obj_create(lv_scr_act());
//    lv_obj_t *label1 = lv_label_create(scr1);
//    lv_label_set_text(label1, "Page 1");
//    lv_obj_center(label1);
//
//    // 页面2
//    scr2 = lv_obj_create(lv_scr_act());
//    lv_obj_t *label2 = lv_label_create(scr2);
//    lv_label_set_text(label2, "Page 2");
//    lv_obj_center(label2);
//
//    // 初始只显示A
//    lv_obj_clear_flag(scr1, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_add_flag(scr2, LV_OBJ_FLAG_HIDDEN);
//
//    lv_timer_create(auto_switch_timer, 1000, NULL);

    lv_obj_t * scr = lv_scr_act();

    lv_obj_t * card = lv_obj_create(scr);
    lv_obj_set_size(card, 160, 60);
//    lv_obj_center(card);
    lv_obj_align(card, LV_ALIGN_TOP_LEFT, 0, 0);


    lv_obj_set_style_border_width(card, 2, 0);
    lv_obj_set_style_border_color(card, lv_color_black(), 0);


    // ===== 时间 =====
    time_label = lv_label_create(card);
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_32, 0);
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, -10);

    // ===== 日期 =====
    date_label = lv_label_create(card);
    lv_obj_set_style_text_font(date_label, &lv_font_montserrat_20, 0);
    lv_obj_align(date_label, LV_ALIGN_CENTER, 0, 20);


    lv_obj_t * card2 = lv_obj_create(scr);
    lv_obj_set_size(card2, 160, 60);
//    lv_obj_center(card);
    lv_obj_align(card2, LV_ALIGN_TOP_LEFT, 0, 80);




    lv_obj_set_style_border_width(card2, 2, 0);
    lv_obj_set_style_border_color(card2, lv_color_black(), 0);


    // ===== 时间 =====
    time_label = lv_label_create(card2);
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_32, 0);
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, -10);

    // ===== 日期 =====
    date_label = lv_label_create(card2);
    lv_obj_set_style_text_font(date_label, &lv_font_montserrat_20, 0);
    lv_obj_align(date_label, LV_ALIGN_CENTER, 0, 20);

    // ===== 启动定时器 =====
    lv_timer_create(clock_timer_cb, 1000, NULL);

//    lv_obj_t * card = lv_obj_create(scr);
//    lv_obj_set_size(card, 200, 120);
//    lv_obj_center(card);


}



int main(void)
{


    return RT_EOK;
}
