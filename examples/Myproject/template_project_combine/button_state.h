#ifndef BUTTON_STATE_H
#define  BUTTON_STATE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nordic_common.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "lcd_i2c.h"
#include "state_machine.h"

#define BUTTON1  13 // Suff/idle menu button
#define BUTTON2  14 // +/Read button
#define BUTTON3  16 // -/Set button
#define BUTTON4  15 // Enter button
#define RESET_BUTTON  21

void gpio_init();

#endif