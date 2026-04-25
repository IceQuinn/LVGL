/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-24     mutou       the first version
 */
#include "main_btn.h"

#include <drv_common.h>
#include "agile_button.h"


enum Btn_Key
{
    BTN_KEY_ESC = 0,    // 返回键
    BTN_KEY_UP,     // 上键
    BTN_KEY_DOWN,   // 下键
    BTN_KEY_ENTER,  // 确定键
    BTN_KEY_MAX,
};

static agile_btn_t _sbtn[BTN_KEY_MAX];

uint32_t Btn_Pin[BTN_KEY_MAX] = {
        GET_PIN(B, 1),
        GET_PIN(B, 0),
        GET_PIN(A, 1),
        GET_PIN(A, 0),
};


static void btn_click_event_cb(agile_btn_t *btn)
{
    rt_kprintf("[button click event] pin:%d   repeat:%d, hold_time:%d\r\n", btn->pin, btn->repeat_cnt, btn->hold_time);
}

void Main_Btn_Init(void)
{
    for (int i = 0; i < BTN_KEY_MAX; ++i) {
        agile_btn_stop(&_sbtn[i]);
        agile_btn_init(&_sbtn[i], Btn_Pin[i], PIN_LOW, PIN_MODE_INPUT_PULLUP);
        agile_btn_set_event_cb(&_sbtn[i], BTN_CLICK_EVENT, btn_click_event_cb);
        agile_btn_start(&_sbtn[i]);
    }
}


