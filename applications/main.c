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

    rt_device_t dev = RT_NULL;
    dev = rt_device_find("vcom");
    char buf[] = "usbd write to pc\r\n";
    char bufRec[512];
    if (dev) {
        rt_device_open(dev, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    } else {
        return -RT_ERROR;
    }

    while (count++)
    {
        rt_kprintf("Hello RT-Thread!\r\n");
        rt_thread_mdelay(300);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(5000);
        rt_pin_write(LED_PIN, PIN_LOW);

        rt_device_write(dev, 0, buf, rt_strlen(buf));

        int realRec = 0;
        realRec = rt_device_read(dev, 0, bufRec, sizeof(bufRec));
        bufRec[realRec] = '\0';
        rt_kprintf(bufRec);
    }

    return RT_EOK;
}
