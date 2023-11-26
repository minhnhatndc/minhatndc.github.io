#ifndef  DHT11_H
#define  DHT11_H

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


#define STARTTIME 18000
#define STOPTIME  12000


#define DHT11_PIN            NRF_GPIO_PIN_MAP(0,30)


#define pin_data_out         nrf_gpio_cfg_output(DHT11_PIN);
#define pin_data_in          nrf_gpio_cfg_input(DHT11_PIN, NRF_GPIO_PIN_PULLUP);

#define pin_set              nrf_gpio_pin_set(DHT11_PIN);
#define pin_clear            nrf_gpio_pin_clear(DHT11_PIN) ;

#define DATA_SUCCESS        NRF_SUCCESS
#define DATA_ERROR          0xFD
#define DATA_NOACK          0xFE


typedef struct{
    uint8_t   temp_int;
    uint8_t   temp_dec;
    uint8_t   humid_int;
    uint8_t   humid_dec;
    uint16_t  checksum;
    uint16_t  Temparature;
    uint16_t  Humidation;
}DHT11_t;




 

uint32_t read_data(DHT11_t *data);

#endif