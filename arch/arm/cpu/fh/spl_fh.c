/*
 * Copyright (C) 2013 Atmel Corporation
 *		      Bo Shen <voice.shen@atmel.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <spl.h>

void start_armboot (void)
{
    board_init_f(0);
}

u32 spl_boot_device(void)
{
#ifdef CONFIG_SPL_YMODEM_SUPPORT
    return BOOT_DEVICE_UART;
#endif
#ifdef CONFIG_SPL_SPI_SUPPORT
    return BOOT_DEVICE_SPI;
#endif
	return BOOT_DEVICE_NONE;
}
