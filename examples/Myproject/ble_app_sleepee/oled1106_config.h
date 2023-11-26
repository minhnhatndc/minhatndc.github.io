#ifndef OLED1106_CONFIG_H
#define OLED1106_CONFIG_H

#include <stdio.h>

#include "nordic_common.h"
#include "nrf_drv_twi.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "boards.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define  TWI_INSTANCE_ID 0
#define  OLED_SDA_PIN 28
#define  OLED_SCL_PIN 27


void twi_oled_init(void);

#endif