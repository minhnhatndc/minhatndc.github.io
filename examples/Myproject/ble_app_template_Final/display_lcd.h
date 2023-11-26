#ifndef  DISPPLAY_LCD_H
#define  DISPPLAY_LCD_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nordic_common.h"
#include "nrf_delay.h"



#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "lcd_i2c.h"
#include "ds3231.h"
#include "dht11.h"
#include "gps_app.h"
#include "state_machine.h"



//==============================



void display_menu_time();
void display_menu_gps();
void display_menu_bluetooth();
void display_menu_idle();
void display_menu_sleep();

void display_time();
void display_time_test();
void display_time_setmode();

void display_date();
void display_temparature_dht11();
void display_temparature_ds3231();

void display_set_time();
void display_read_time();

void display_gps();
void display_bluetooth();
void display_bluetooth_config();
void display_time_adjust();

void display_sleep();


#endif