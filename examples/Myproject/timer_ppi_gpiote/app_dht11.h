#ifndef  APP_DHT11_H
#define  APP_DHT11_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#include "nordic_common.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_drv_timer.h"
#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"


#define DHT11_STARTTIME 18000
#define DHT11_STOPTIME  12000
#define DHT11           0x01
#define DHT11_PIN       20

typedef struct
{
  uint16_t Temparature;
  uint16_t Humidation;
}dht11_t;

typedef enum{
  DHT11_OKAY,
  DHT11_NO_PULLUP,
  DHT11_NO_ACK_0,
  DHT11_NO_ACK_1,
  DHT11_NO_DATA_0,
  DHT11_NO_DATA_1,
  DHT11_BAD_CRC
}dht11_err_t;

dht11_err_t dht11_read(uint16_t *temp, uint16_t *humid);



#endif