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


#include "main_btn.h"

int main(void)
{
//    agile_btn_env_init();

    Main_Btn_Init();
//    int count = 1;
//
//    while (count++)
//    {
//        LOG_D("Hello RT-Thread!");
//        rt_thread_mdelay(1000);
//    }

    return RT_EOK;
}
