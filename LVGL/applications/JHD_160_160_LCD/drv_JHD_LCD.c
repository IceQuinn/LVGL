/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-25     mutou       the first version
 */
#include "drv_JHD_LCD.h"

#include <drv_common.h>
#include "drv_spi.h"


/* 显示屏 */
#define UC1698u_SPI_NAME            "spi2"
#define SPI_UC1698u_DEVICE_NAME     "spi21"
#define UC1698u_NSS_GPIO_PORT       GPIOC
#define UC1698u_NSS_GPIO_PIN        GPIO_PIN_3
#define LCD_NSS_PIN                 GET_PIN(C, 3)

#define LCD_CD              GET_PIN(C, 2)   // 数据/指令
#define LCD_CS              GET_PIN(C, 3)   // 片选
#define LCD_RST             GET_PIN(C, 1)   // 复位信号

struct rt_spi_device *spi_dev_UC1698u;     /* SPI 设备句柄 */

int JHD_LCD_SPI_Init(void)
{
    rt_err_t res;

    /* 设置片选管脚模式为输出 */
    rt_pin_mode(LCD_NSS_PIN, PIN_MODE_OUTPUT);
    /* 把spi20挂到spi2上 */
    res = rt_hw_spi_device_attach(UC1698u_SPI_NAME, SPI_UC1698u_DEVICE_NAME, UC1698u_NSS_GPIO_PORT, UC1698u_NSS_GPIO_PIN);
    if (res == RT_EOK)
    {
        rt_kprintf("spi2 bus attach LCD device OK !\r\n");
    }
    spi_dev_UC1698u = (struct rt_spi_device *)rt_device_find(SPI_UC1698u_DEVICE_NAME);
    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
        cfg.max_hz = 20 * 1000 *1000; /* 20M,SPI max 42MHz,ssd1351 4-wire spi */

        rt_spi_configure(spi_dev_UC1698u, &cfg);
    }

    return RT_EOK;

}

void UC1698u_spi_Write(void* data, uint16_t len)
{
//    rt_pin_write(LCD_CS, PIN_LOW);
//    HAL_SPI_Transmit(&hspi2, data, len, 1000);
    rt_spi_send(spi_dev_UC1698u, data, len);
//    rt_pin_write(LCD_CS, PIN_HIGH);
}

uint16_t LCD_CD_Pin_Level = 0;
// 低电平命令
void LCD_RS_LOW(void)
{
    if(1 == LCD_CD_Pin_Level){
        LCD_CD_Pin_Level = 0;
        rt_pin_write(LCD_CD, PIN_LOW);
    }
}
// 高电平数据
void LCD_RS_HIGH(void)
{
    if(0 == LCD_CD_Pin_Level){
        LCD_CD_Pin_Level = 1;
        rt_pin_write(LCD_CD, PIN_HIGH);
    }
}


void LCD_Write_Data(void *Data, uint16_t len)
{
    LCD_RS_HIGH();         /* 数据高电平 */
    UC1698u_spi_Write(Data, len);
}

void LCD_Write_CMD(uint8_t Cmd)
{
    LCD_RS_LOW();    /* 命令低电平 */
    UC1698u_spi_Write(&Cmd, 1);
}




void UC1698u_GPIO_Init(void)
{
    rt_pin_mode(LCD_CD,   PIN_MODE_OUTPUT); // 数据/指令
    rt_pin_mode(LCD_CS,   PIN_MODE_OUTPUT); // 片选
    rt_pin_mode(LCD_RST,  PIN_MODE_OUTPUT); // 复位信号

    rt_pin_write(LCD_RST, PIN_LOW);
    rt_thread_mdelay(10);
    rt_pin_write(LCD_RST, PIN_HIGH);

    rt_pin_write(LCD_CD, PIN_LOW);
}


void Drv_JHD_LCD_Init(void)
{
    UC1698u_GPIO_Init();

    JHD_LCD_SPI_Init();
}
