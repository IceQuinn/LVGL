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

void lv_user_gui_init(void)
{
//    lv_init();
//    lv_port_disp_init();
    /* 获取默认显示器的活动屏幕 */
    lv_obj_t *scr = lv_scr_act();
    lv_obj_clean(scr); /* 清屏 */

    /* 创建界面启动界面 */
    lv_obj_t *page = lv_obj_create(scr);
    lv_obj_set_size(page, LV_HOR_RES-2, LV_VER_RES-2);
    lv_obj_set_style_bg_color(page, lv_color_white(), LV_PART_MAIN);            /* 设置背景颜色 */
    lv_obj_set_style_radius(page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);          /* 设置导角为0 */
    lv_obj_set_style_border_width(page, 1, LV_PART_MAIN | LV_STATE_DEFAULT);    /* 设置边框为0 */

    /* 添加标签 */
    lv_obj_t *label = lv_label_create(page);
    lv_label_set_text(label, "Hello LVGL");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}


int main(void)
{
//    agile_btn_env_init();

    Main_Btn_Init();

    JHD_LCD_Init();
//    lv_user_gui_init();
//    int count = 1;
//
//    while (count++)
//    {
//        LOG_D("Hello RT-Thread!");
//        rt_thread_mdelay(1000);
//    }

    return RT_EOK;
}
