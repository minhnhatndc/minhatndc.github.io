
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define saadc_buffer_length 5
//save the samples in the buffer
static nrf_saadc_value_t saadc_buffer_pool[2][saadc_buffer_length];

static const nrf_drv_timer_t timer1 = NRF_DRV_TIMER_INSTANCE(1);
static nrf_ppi_channel_t ppi_channel;

void timer_handler(nrf_timer_event_t event_type, void *p_context)
{
  // Nothing
}

void ppi_init(void)
{ uint32_t timer_evt_addr;
  uint32_t saadc_task_addr;
  ret_code_t err_code = NRF_SUCCESS;

  err_code = nrf_drv_ppi_init();
  APP_ERROR_CHECK(err_code);

  //init Timer
  nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
  timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;

  err_code = nrf_drv_timer_init(&timer1,&timer_cfg, timer_handler);

  uint32_t timer_ticks = nrf_drv_timer_ms_to_ticks(&timer1, 250);
  nrf_drv_timer_extended_compare(&timer1,NRF_TIMER_CC_CHANNEL0,timer_ticks,NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,true);
  //Enable Timer
  nrf_drv_timer_enable(&timer1);

  //init PPI channel
  timer_evt_addr = nrf_drv_timer_compare_event_address_get(&timer1, NRF_TIMER_CC_CHANNEL0);
  saadc_task_addr = nrf_drv_saadc_sample_task_get();
  
  err_code = nrf_drv_ppi_channel_alloc(&ppi_channel);
  APP_ERROR_CHECK(err_code);
  err_code = nrf_drv_ppi_channel_assign(ppi_channel,timer_evt_addr,saadc_task_addr);
  APP_ERROR_CHECK(err_code);
  
  

  
}
// handle the events once the samples are recieved in the buffer
void saadc_callback_handler(nrf_drv_saadc_evt_t const *p_event)
{ float val;
  if(p_event ->type == NRFX_SAADC_EVT_DONE){
  ret_code_t err_code;
  err_code = nrfx_saadc_buffer_convert(p_event->data.done.p_buffer, saadc_buffer_length);
  APP_ERROR_CHECK(err_code);
  int i;
  NRF_LOG_INFO("ADC event occured!!");
  for(i=0; i< saadc_buffer_length; i++){
  NRF_LOG_INFO("Sample value read: %d", p_event->data.done.p_buffer[i]);
  val = p_event->data.done.p_buffer[i] * 3.6/4096;
  NRF_LOG_INFO("Vol read:" NRF_LOG_FLOAT_MARKER " \r\n", NRF_LOG_FLOAT(val));
  }
  }
}


void saadc_init(void)
{ ret_code_t err_code;
  nrf_saadc_channel_config_t channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);
  err_code = nrf_drv_saadc_init(NULL, saadc_callback_handler);
  APP_ERROR_CHECK(err_code);

  //channel config
  err_code = nrfx_saadc_channel_init(0, &channel_config);
  APP_ERROR_CHECK(err_code);
  // Buffer config
  err_code = nrfx_saadc_buffer_convert(saadc_buffer_pool[0], saadc_buffer_length);
  APP_ERROR_CHECK(err_code);
  err_code = nrfx_saadc_buffer_convert(saadc_buffer_pool[1], saadc_buffer_length);

}

/**
 * @brief Function for main application entry.
 */
int main(void)
{   
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    ppi_init();
    saadc_init();

    NRF_LOG_INFO("SAADC PPI start");
    ret_code_t err_code = nrf_drv_ppi_channel_enable(ppi_channel);
    APP_ERROR_CHECK(err_code);
    
    NRF_LOG_INFO("Application started");      

    while (1)
    { 
      

    }
}



//=================================================================================================================
//#define SAMPLES_IN_BUFFER 5
//volatile uint8_t state = 1;

//static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(0);
//static nrf_saadc_value_t     m_buffer_pool[2][SAMPLES_IN_BUFFER];
//static nrf_ppi_channel_t     m_ppi_channel;
//static uint32_t              m_adc_evt_counter;


//void timer_handler(nrf_timer_event_t event_type, void * p_context)
//{

//}


//void saadc_sampling_event_init(void)
//{
//    ret_code_t err_code;

//    err_code = nrf_drv_ppi_init();
//    APP_ERROR_CHECK(err_code);

//    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
//    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
//    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
//    APP_ERROR_CHECK(err_code);

//    /* setup m_timer for compare event every 400ms */
//    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 400);
//    nrf_drv_timer_extended_compare(&m_timer,
//                                   NRF_TIMER_CC_CHANNEL0,
//                                   ticks,
//                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
//                                   false);
//    nrf_drv_timer_enable(&m_timer);

//    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
//                                                                                NRF_TIMER_CC_CHANNEL0);
//    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

//    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
//    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
//    APP_ERROR_CHECK(err_code);

//    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
//                                          timer_compare_event_addr,
//                                          saadc_sample_task_addr);
//    APP_ERROR_CHECK(err_code);
//}


//void saadc_sampling_event_enable(void)
//{
//    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);

//    APP_ERROR_CHECK(err_code);
//}


//void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
//{
//    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
//    {
//        ret_code_t err_code;

//        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
//        APP_ERROR_CHECK(err_code);

//        int i;
//        NRF_LOG_INFO("ADC event number: %d", (int)m_adc_evt_counter);

//        for (i = 0; i < SAMPLES_IN_BUFFER; i++)
//        {
//            NRF_LOG_INFO("%d", p_event->data.done.p_buffer[i]);
//        }
//        m_adc_evt_counter++;
//    }
//}


//void saadc_init(void)
//{
//    ret_code_t err_code;
//    nrf_saadc_channel_config_t channel_config =
//        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);

//    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
//    APP_ERROR_CHECK(err_code);

//    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
//    APP_ERROR_CHECK(err_code);

//    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
//    APP_ERROR_CHECK(err_code);

//    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
//    APP_ERROR_CHECK(err_code);

//}


///**
// * @brief Function for main application entry.
// */
//int main(void)
//{
//    uint32_t err_code = NRF_LOG_INIT(NULL);
//    APP_ERROR_CHECK(err_code);

//    NRF_LOG_DEFAULT_BACKENDS_INIT();

//    ret_code_t ret_code = nrf_pwr_mgmt_init();
//    APP_ERROR_CHECK(ret_code);

//    saadc_init();
//    saadc_sampling_event_init();
//    saadc_sampling_event_enable();
//    NRF_LOG_INFO("SAADC HAL simple example started.");

//    while (1)
//    {
//        nrf_pwr_mgmt_run();
//        NRF_LOG_FLUSH();
//    }
//}


/** @} */
