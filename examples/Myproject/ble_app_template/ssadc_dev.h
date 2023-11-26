//ADC development

/*     */
#ifndef  SSADC_DEV_H
#define  SSADC_DEV_H

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "app_error.h"
#include "app_util.h"
#include "nrf_pwr_mgmt.h"

// include   log library
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "ble_hrs.h"

#define saadc_buffer_length               5           // uint16
#define TIMER_SAADC                       1
#define SAMPLING_TIME_MS_TO_TICKS         25          //ms

#define SAADC_CHANNLE_CONFIG              NRF_SAADC_INPUT_AIN0  // define using ADC channel 0
#define saadc_channel                     0                     // define using ADC channel 0

static nrf_saadc_value_t  saadc_buffer_pool[2][saadc_buffer_length];  // the buffer for saving sampling value

static const nrf_drv_timer_t    timer_saadc = NRF_DRV_TIMER_INSTANCE(TIMER_SAADC);  // timer for sampling each value
static nrf_ppi_channel_t        saadc_ppi_channel;


//void saadc_timer_handler(nrf_timer_event_t event_type, void *p_contex);
//void saadc_ppi_init();
//void saadc_callback_handler(nrf_drv_saadc_evt_t const *p_event);
//void saadc_init();

#endif