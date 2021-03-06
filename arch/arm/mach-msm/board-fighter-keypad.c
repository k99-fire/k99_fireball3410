/* arch/arm/mach-msm/board-fighter-keypad.c
 * Copyright (C) 2010 HTC Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/

#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/gpio_event.h>
#include <linux/gpio.h>
#include <linux/keyreset.h>
#include <asm/mach-types.h>
#include <mach/board_htc.h>
#include <mach/gpio.h>
#if 0
#include "proc_comm.h"
#endif
#include <linux/mfd/pm8xxx/pm8921.h>
#include "board-fighter.h"

#if 0
static char *keycaps = "--qwerty";
#endif
#undef MODULE_PARAM_PREFIX
#define MODULE_PARAM_PREFIX "board_fighter."

#if 0
module_param_named(keycaps, keycaps, charp, 0);
#endif

static struct gpio_event_direct_entry fighter_keypad_map[] = {
	{
		.gpio = FIGHTER_GPIO_PWR_KEYz,
		.code = KEY_POWER,
	},
	{
		.gpio = FIGHTER_GPIO_VOL_UPz,
		.code = KEY_VOLUMEUP,
	},
	{
		.gpio = FIGHTER_GPIO_VOL_DOWNz,
		.code = KEY_VOLUMEDOWN,
	},
};

static uint32_t matirx_inputs_gpio_table[] = {
	GPIO_CFG(FIGHTER_GPIO_PWR_KEYz, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP,
		 GPIO_CFG_2MA),
	GPIO_CFG(FIGHTER_GPIO_VOL_UPz, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP,
		 GPIO_CFG_2MA),
	GPIO_CFG(FIGHTER_GPIO_VOL_DOWNz, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP,
		 GPIO_CFG_2MA),
};

static void fighter_direct_inputs_gpio(void)
{
	gpio_tlmm_config(matirx_inputs_gpio_table[0], GPIO_CFG_ENABLE);
	gpio_tlmm_config(matirx_inputs_gpio_table[1], GPIO_CFG_ENABLE);
	gpio_tlmm_config(matirx_inputs_gpio_table[2], GPIO_CFG_ENABLE);

	return;
}

static struct gpio_event_input_info fighter_keypad_power_info = {
	.info.func = gpio_event_input_func,
	.flags = GPIOEDF_PRINT_KEYS,
	.type = EV_KEY,
#if BITS_PER_LONG != 64 && !defined(CONFIG_KTIME_SCALAR)
	.debounce_time.tv.nsec = 20 * NSEC_PER_MSEC,
# else
	.debounce_time.tv64 = 20 * NSEC_PER_MSEC,
# endif
	.keymap = fighter_keypad_map,
	.keymap_size = ARRAY_SIZE(fighter_keypad_map),
	.setup_input_gpio = fighter_direct_inputs_gpio,
};

static struct gpio_event_info *fighter_keypad_info[] = {
	&fighter_keypad_power_info.info,
};

static struct gpio_event_platform_data fighter_keypad_data = {
	.name = "keypad_8960",
	.info = fighter_keypad_info,
	.info_count = ARRAY_SIZE(fighter_keypad_info),
};

static struct platform_device fighter_keypad_device = {
	.name = GPIO_EVENT_DEV_NAME,
	.id = 0,
	.dev		= {
		.platform_data	= &fighter_keypad_data,
	},
};

static struct keyreset_platform_data fighter_reset_keys_pdata = {
	/*.keys_up = fighter_reset_keys_up,*/
	.keys_down = {
		KEY_POWER,
		KEY_VOLUMEDOWN,
		KEY_VOLUMEUP,
		0
	},
};

static struct platform_device fighter_reset_keys_device = {
	.name = KEYRESET_NAME,
	.dev.platform_data = &fighter_reset_keys_pdata,
};

int __init fighter_init_keypad(void)
{
	if (platform_device_register(&fighter_reset_keys_device))
		printk(KERN_WARNING "%s: register reset key fail\n", __func__);

	return platform_device_register(&fighter_keypad_device);
}

