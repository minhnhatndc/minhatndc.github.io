#ifndef  STATE_MACHINE_H
#define  STATE_MACHINE_H
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

#include "dht11.h"
#include "ds3231.h"
#include "gps_app.h"
#include "lcd_i2c.h"
#include "button_state.h"
#include "display_lcd.h"



typedef  enum{
  Idle = 0,
  ModemenuTime,
  ModemenuGPS,
  ModemenuBluetooth,

  ModeChangeDisplay,
  ModeReadTime,
  ModeConfigTime,

  ModeReadGPS,

  ModeReadBluetooth,
  ModeConfigBluetooth,

  ModeSetTimeSleep,
  ModeReadTimeSleep
} Mode_t;

typedef  enum
{
  AdjustHour = 0,
  AdjustMin,
  AdjustSec,
  AdjustDate,
  AdjustDay,
  AdjustMonth,
  AdjustYear,
  AdjustBlueTooth,
  AdjustTimeSleep,

} Mode_config_t;

typedef  enum{
  Mode24h = 0,
  Mode12h
} Mode_time_t;

typedef  enum{
  ModeConnect = 0,
  ModeDisconnect
} Mode_bluetooth_t;
typedef enum{
  Bluetooth_connect =0,
  Bluetooth_disconnect
} Bluetooth_status_t;
typedef enum{
  Menupin = 0,
  Enterpin,
  Incrpin,
  Decrpin
} Type_pin_t;

typedef  struct{
  Type_pin_t type;
} Type_pin;

extern Type_pin              Pin;
extern Bluetooth_status_t    Bluetooth_status;
extern Mode_t                Mode;
extern Mode_config_t         Mode_cfg; 
extern Mode_time_t           Mode_time;
extern Mode_bluetooth_t      Mode_bluetooth;

extern uint8_t               flag;
extern uint8_t               flagFinishCfg;
extern uint8_t               flagDisplay;

void state_config(Mode_config_t *mode);
void state_month(int Month, char buffer[]);
void state_day(int Day, char buffer[]);
void state_button();
#endif