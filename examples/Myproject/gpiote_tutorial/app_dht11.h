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
//#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"


#define DHT11_STARTTIME 18000
#define DHT11_STOPTIME  12000
#define DHT11           0x01
#define DHT11_PIN       20
#define DHT11_ONE_WIRE_INPUT_PIN 21
#define level_1 1
#define level_0 0






typedef struct
{
  uint16_t Temparature;
  uint16_t Humidation;
}dht11_t;
typedef struct{
    uint16_t type;
    nrfx_timer_event_handler_t *p_timer_hander;
    uint16_t pin;
    float temp;
    float humid;
}DHT_t;
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

unsigned char DHT11_READ_1_BYTES_DATA(void);
void DHT11_DIR_INPUT(void);
void DHT11_DIR_OUTPUT(void);
void DHT11_START_SEQUENCE(void);
char DHT11_READ_5_BYTES_DATA(void);
void Convert_Humidity_Temperature_Values(unsigned char byte1);
//void DHT_task_callback(void);
#endif