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

static agile_btn_t _sbtn;

//{GET_PIN(B, 1), KEY_EVENT_NONE, "返回键"},
//{GET_PIN(B, 0), KEY_EVENT_NONE, "上键"},
//{GET_PIN(A, 1), KEY_EVENT_NONE, "下键"},
//{GET_PIN(A, 0), KEY_EVENT_NONE, "确定键"},

static void btn_click_event_cb(agile_btn_t *btn)
{
    rt_kprintf("[button click event] pin:%d   repeat:%d, hold_time:%d\r\n", btn->pin, btn->repeat_cnt, btn->hold_time);
}
int main(void)
{
//    agile_btn_env_init();

    agile_btn_stop(&_sbtn);
    agile_btn_init(&_sbtn, GET_PIN(B, 1), PIN_LOW, PIN_MODE_INPUT_PULLUP);
    agile_btn_set_event_cb(&_sbtn, BTN_CLICK_EVENT, btn_click_event_cb);
    agile_btn_start(&_sbtn);
//    int count = 1;
//
//    while (count++)
//    {
//        LOG_D("Hello RT-Thread!");
//        rt_thread_mdelay(1000);
//    }

    return RT_EOK;
}
