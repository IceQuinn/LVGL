/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-23     RealThread   first version
 */

#include <rtthread.h>
#include <board.h>
#include <drv_common.h>

#ifndef RT_WEAK
#define RT_WEAK rt_weak
#endif

RT_WEAK void rt_hw_board_init()
{
    extern void hw_board_init(char *clock_src, int32_t clock_src_freq, int32_t clock_target_freq);

    /* Heap initialization */
#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *) HEAP_BEGIN, (void *) HEAP_END);
#endif

    hw_board_init(BSP_CLOCK_SOURCE, BSP_CLOCK_SOURCE_FREQ_MHZ, BSP_CLOCK_SYSTEM_FREQ_MHZ);

    /* Set the shell console output device */
#if defined(RT_USING_DEVICE) && defined(RT_USING_CONSOLE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}



DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hspi->Instance==SPI1)
    {

        /* USER CODE BEGIN SPI1_MspInit 0 */

        /* USER CODE END SPI1_MspInit 0 */
        /* SPI1 clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**SPI1 GPIO Configuration
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI
        */
        GPIO_InitStruct.Pin         = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull        = GPIO_NOPULL;
        GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate   = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* SPI1 DMA Init */
        /* SPI1_RX Init */
        hdma_spi1_rx.Instance               = DMA2_Stream0;
        hdma_spi1_rx.Init.Channel           = DMA_CHANNEL_3;
        hdma_spi1_rx.Init.Direction         = DMA_PERIPH_TO_MEMORY;
        hdma_spi1_rx.Init.PeriphInc         = DMA_PINC_DISABLE;
        hdma_spi1_rx.Init.MemInc            = DMA_MINC_ENABLE;
        hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_spi1_rx.Init.MemDataAlignment  = DMA_MDATAALIGN_BYTE;
        hdma_spi1_rx.Init.Mode              = DMA_NORMAL;
        hdma_spi1_rx.Init.Priority          = DMA_PRIORITY_LOW;
        hdma_spi1_rx.Init.FIFOMode          = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hspi, hdmarx, hdma_spi1_rx);

        /* SPI1_TX Init */
        hdma_spi1_tx.Instance               = DMA2_Stream2;
        hdma_spi1_tx.Init.Channel           = DMA_CHANNEL_2;
        hdma_spi1_tx.Init.Direction         = DMA_MEMORY_TO_PERIPH;
        hdma_spi1_tx.Init.PeriphInc         = DMA_PINC_DISABLE;
        hdma_spi1_tx.Init.MemInc            = DMA_MINC_ENABLE;
        hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_spi1_tx.Init.MemDataAlignment  = DMA_MDATAALIGN_BYTE;
        hdma_spi1_tx.Init.Mode              = DMA_NORMAL;
        hdma_spi1_tx.Init.Priority          = DMA_PRIORITY_LOW;
        hdma_spi1_tx.Init.FIFOMode          = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hspi, hdmatx, hdma_spi1_tx);

        /* USER CODE BEGIN SPI1_MspInit 1 */

        /* USER CODE END SPI1_MspInit 1 */

    }
    else if(hspi->Instance==SPI2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI2 GPIO Configuration
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else if(hspi->Instance==SPI3)
    {
        /* Peripheral clock enable */
        __HAL_RCC_SPI3_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_DISABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /**SPI2 GPIO Configuration
        PB3     ------> SPI3_SCK
        PB4     ------> SPI3_MISO
        PB5     ------> SPI3_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
}
