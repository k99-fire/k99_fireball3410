/* arch/arm/mach-msm/board-fighter-gpio.c
 * Copyright (C) 2011 HTC Corporation.
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

#include <mach/gpiomux.h>
#include "board-fighter.h"

static struct gpiomux_setting gsbi2 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi3 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

#if 0	/* active in cam_settings */
static struct gpiomux_setting gsbi4 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

static struct gpiomux_setting gsbi8 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi12 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

#if 0
static struct gpiomux_setting gsbi10 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_4MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

static struct gpiomux_setting cdc_mclk = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting slimbus = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_KEEPER,
};

static struct msm_gpiomux_config fighter_gsbi_configs[] __initdata = {
	{
		.gpio      = FIGHTER_GPIO_NFC_I2C_DAT,	/* GSBI2 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi2,
			[GPIOMUX_ACTIVE] = &gsbi2,
		},
	},
	{
		.gpio      = FIGHTER_GPIO_NFC_I2C_CLK,	/* GSBI2 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi2,
			[GPIOMUX_ACTIVE] = &gsbi2,
		},
	},
	{
		.gpio      = FIGHTER_GPIO_TP_I2C_DAT,	/* GSBI3 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3,
			[GPIOMUX_ACTIVE] = &gsbi3,
		},
	},
	{
		.gpio      = FIGHTER_GPIO_TP_I2C_CLK,	/* GSBI3 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3,
			[GPIOMUX_ACTIVE] = &gsbi3,
		},
	},
#if 0	/* active in cam_settings */
	{
		.gpio      = FIGHTER_GPIO_CAM_I2C_DAT,	/* GSBI4 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi4,
		},
	},
	{
		.gpio      = FIGHTER_GPIO_CAM_I2C_CLK,	/* GSBI4 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi4,
		},
	},
#endif
	{
		.gpio	   = FIGHTER_GPIO_AC_I2C_DAT,	/* GSBI8 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi8,
		},
	},
	{
		.gpio	   = FIGHTER_GPIO_AC_I2C_CLK,	/* GSBI8 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi8,
		},
	},
	{
		.gpio      = FIGHTER_GPIO_SR_I2C_DAT,	/* GSBI12 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi12,
			[GPIOMUX_ACTIVE] = &gsbi12,
		},
	},
	{
		.gpio      = FIGHTER_GPIO_SR_I2C_CLK,	/* GSBI12 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi12,
			[GPIOMUX_ACTIVE] = &gsbi12,
		},
	},
};

static struct msm_gpiomux_config fighter_audio_codec_configs[] __initdata = {
	{
		.gpio = FIGHTER_GPIO_AUD_WCD_MCLK,
		.settings = {
			[GPIOMUX_SUSPENDED] = &cdc_mclk,
		},
	},
};

static struct msm_gpiomux_config fighter_slimbus_configs[] __initdata = {
	{
		.gpio	= FIGHTER_GPIO_AUD_WCD_SB_CLK,		/* slimbus data */
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
	{
		.gpio	= FIGHTER_GPIO_AUD_WCD_SB_DATA,		/* slimbus clk */
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
};

static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config wcnss_5wire_interface[] = {
	{
		.gpio = FIGHTER_GPIO_WCN_CMD_DATA2,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = FIGHTER_GPIO_WCN_CMD_DATA1,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = FIGHTER_GPIO_WCN_CMD_DATA0,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = FIGHTER_GPIO_WCN_CMD_SET,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = FIGHTER_GPIO_WCN_CMD_CLK,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
};

static struct gpiomux_setting cam_settings[5] = {
	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend*/
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},

	{
		.func = GPIOMUX_FUNC_1, /*active 1*/
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*active 2*/
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},

	{
		.func = GPIOMUX_FUNC_1, /*active 3*/
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_2, /*active 4*/
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
	},

};

static struct msm_gpiomux_config fighter_cam_configs[] = {
	{
		.gpio = FIGHTER_GPIO_CAM_MCLK1,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[4],
			[GPIOMUX_SUSPENDED] = &cam_settings[2],
		},
	},
	{
		.gpio = FIGHTER_GPIO_CAM_MCLK0,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[1],
			[GPIOMUX_SUSPENDED] = &cam_settings[2],
		},
	},
	{
		.gpio = FIGHTER_GPIO_CAM_I2C_DAT,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[0],
		},
	},
	{
		.gpio = FIGHTER_GPIO_CAM_I2C_CLK,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[0],
		},
	},
};

static struct gpiomux_setting mdp_vsync_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdp_vsync_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config fighter_mdp_vsync_configs[] __initdata = {
	{
		.gpio = FIGHTER_GPIO_LCD_TE,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdp_vsync_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdp_vsync_suspend_cfg,
		},
	}
};

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL

static struct gpiomux_setting mhl_i2c_suspend_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_8MA,
    .pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mhl_i2c_active_cfg = {
    .func = GPIOMUX_FUNC_1,
    .drv = GPIOMUX_DRV_8MA,
    .pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config fighter_mhl_i2c_configs[] __initdata = {
    {
        .gpio = 36,
        .settings = {
            [GPIOMUX_ACTIVE]    = &mhl_i2c_active_cfg,
            [GPIOMUX_SUSPENDED] = &mhl_i2c_suspend_cfg,
        },
    },
    {
        .gpio = 37,
        .settings = {
            [GPIOMUX_ACTIVE]    = &mhl_i2c_active_cfg,
            [GPIOMUX_SUSPENDED] = &mhl_i2c_suspend_cfg,
        },
    },
};
#endif

static struct gpiomux_setting usb_id_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting usb_audio_sw_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config cable_detect_usbid_config[] __initdata = {
	{
		.gpio = FIGHTER_GPIO_USB_ID1,
		.settings = {
			[GPIOMUX_ACTIVE] = &usb_id_cfg,
			[GPIOMUX_SUSPENDED] = &usb_id_cfg,
		},
	},
	{
		.gpio = FIGHTER_GPIO_USBz_AUDIO_SW,
		.settings = {
			[GPIOMUX_ACTIVE] = &usb_audio_sw_cfg,
			[GPIOMUX_SUSPENDED] = &usb_audio_sw_cfg,
		},
	},
};

int __init fighter_gpiomux_init(void)
{
	int rc;

	rc = msm_gpiomux_init(NR_GPIO_IRQS);
	if (rc) {
		pr_err(KERN_ERR "msm_gpiomux_init failed %d\n", rc);
		return rc;
	}

	msm_gpiomux_install(fighter_cam_configs,
			ARRAY_SIZE(fighter_cam_configs));

	msm_gpiomux_install(fighter_gsbi_configs,
			ARRAY_SIZE(fighter_gsbi_configs));

	msm_gpiomux_install(fighter_slimbus_configs,
			ARRAY_SIZE(fighter_slimbus_configs));

	msm_gpiomux_install(fighter_audio_codec_configs,
			ARRAY_SIZE(fighter_audio_codec_configs));

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
	msm_gpiomux_install(fighter_mhl_i2c_configs,
			ARRAY_SIZE(fighter_mhl_i2c_configs));
#endif
	msm_gpiomux_install(fighter_mdp_vsync_configs,
			ARRAY_SIZE(fighter_mdp_vsync_configs));

	msm_gpiomux_install(wcnss_5wire_interface,
			ARRAY_SIZE(wcnss_5wire_interface));

	msm_gpiomux_install(cable_detect_usbid_config,
			ARRAY_SIZE(cable_detect_usbid_config));

	return 0;
}
