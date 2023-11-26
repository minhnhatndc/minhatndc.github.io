#include "ssadc_dev.h"


/*  Digital output
Single Ended: A single ended configuration uses 1 pin for reading analogue voltages.

A simple formula to calculate the input  voltage is given:
--------------------------------------------------------------------------------------------
  Vb = [v(p) - v(n)] * Gain / Reference * 2^(n-m)
  for single ended m =0
--------------------------------------------------------------------------------------------
  Vb = is voltage representation in binary

  v(p) = voltage read on positive pin of the adc channel

  v(n) = voltage on negative pin (In single ended mode this is connected with internal ground automatically). so its value is 0.

  Gain = 1/6 which is selected by default as GAIN_1_6 in config default

  Reference =  connected with internal 0.6V

  n = is the resolution of ADC
*/
/*  Differential

Differential : In Differential mode we use two input channels, so we measure the voltage difference between these two channels. 
Differential mode is good in terms of noise immunity 
and it is also good for measuring small differential changes for e.g a coin cell battery voltage drop is approx 0.6 volts from 100 percent to 0 percent 
so differential mode would be a good match for measuring this range.

Same formula can be used to calculate the input voltage for differential is:
for calculating the signed values:
---------------------------------------------------------------------------------
Vb = (V(p) / Input Range) * 2^(n -m)
here for differential mode m = 1
---------------------------------------------------------------------------------
Vb :        is voltage representation in binary
V(p):   is the input voltage read on positive pin
V(n): in this case we have connected it with internal reference
Input Range :     3.6V
n :          is the resolution of ADC
m = 1 for differential mode
*/
void saadc_timer_handler(nrf_timer_event_t event_type, void *p_contex)
{
  // Do something
}
void saadc_ppi_init()
{
  ret_code_t err_code;
  uint32_t timer_evt_addr;
  uint32_t saadc_task_addr;

  err_code = nrf_drv_ppi_init();
  APP_ERROR_CHECK(err_code);

  // Initialisation Timer
  nrf_drv_timer_config_t  timer_config  = NRF_DRV_TIMER_DEFAULT_CONFIG;
  timer_config.bit_width  = NRF_TIMER_BIT_WIDTH_32;

  err_code  = nrf_drv_timer_init(&timer_saadc,&timer_config,saadc_timer_handler);
  APP_ERROR_CHECK(err_code);

  uint32_t timer_ticks  = nrf_drv_timer_ms_to_ticks(&timer_saadc, SAMPLING_TIME_MS_TO_TICKS);
  nrf_drv_timer_extended_compare(&timer_saadc,NRF_TIMER_CC_CHANNEL0,timer_ticks,NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,true);
  //Enable Timer
  nrf_drv_timer_enable(&timer_saadc);

  // Init ppi channel

  timer_evt_addr  =   nrf_drv_timer_compare_event_address_get(&timer_saadc,NRF_TIMER_CC_CHANNEL0);
  saadc_task_addr =   nrf_drv_saadc_sample_task_get();

  err_code  = nrf_drv_ppi_channel_alloc(&saadc_ppi_channel);
  APP_ERROR_CHECK(err_code);
  err_code  = nrf_drv_ppi_channel_assign(saadc_ppi_channel,timer_evt_addr,saadc_task_addr);
  APP_ERROR_CHECK(err_code);

  // Enable PPI

  err_code =  nrf_drv_ppi_channel_enable(saadc_ppi_channel);
  APP_ERROR_CHECK(err_code);

}
void saadc_callback_handler(nrf_drv_saadc_evt_t const *p_event)
{
  ret_code_t err_code = NRF_SUCCESS;
  float value = 0;
  if(p_event->type ==  NRFX_SAADC_EVT_DONE)
  {
    err_code  = nrfx_saadc_buffer_convert(p_event->data.done.p_buffer, saadc_buffer_length);
    APP_ERROR_CHECK(err_code);
    int i;
    for(i = 0; i<saadc_buffer_length; i++)
    {
      value = p_event->data.done.p_buffer[i]* 3.6/4096;
      NRF_LOG_INFO("ADC read value ="NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT(value));
    }
  } 
}
void saadc_init()
{
    ret_code_t  err_code;
    nrf_saadc_channel_config_t  channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(SAADC_CHANNLE_CONFIG);
    err_code  = nrf_drv_saadc_init(NULL, saadc_callback_handler);
    APP_ERROR_CHECK(err_code);

    //channel config
    err_code  = nrfx_saadc_channel_init(saadc_channel,&channel_config);
    APP_ERROR_CHECK(err_code);
    //Buffer ADC config
    err_code  = nrfx_saadc_buffer_convert(saadc_buffer_pool[0], saadc_buffer_length);
    err_code  = nrfx_saadc_buffer_convert(saadc_buffer_pool[1], saadc_buffer_length);
}