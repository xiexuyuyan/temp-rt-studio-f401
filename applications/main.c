/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-03     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define LED_PIN GET_PIN(C, 13)

int main(void)
{
    int count = 1;

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

#if defined (USB_OTG_FS)
    rt_kprintf("defined otg fs!\r\n");
    rt_pin_write(LED_PIN, PIN_HIGH);
#endif

    MX_USB_DEVICE_Init();

    while (count++)
    {
        rt_kprintf("Hello RT-Thread!");
        rt_thread_mdelay(300);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(5000);
        rt_pin_write(LED_PIN, PIN_LOW);

        uint8_t str[] = {'c', 'd', 'c', 'o', 'k', '\0'};
        CDC_Transmit_FS(str, 5u);
    }

    return RT_EOK;
}
