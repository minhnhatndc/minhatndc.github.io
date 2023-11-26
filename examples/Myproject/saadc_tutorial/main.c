/** @file
 * @defgroup nrf_adc_example main.c
 * @{
 * @ingroup nrf_adc_example
 * @brief ADC Example Application main file.
 *
 * This file contains the source code for a sample application using ADC.
 *
 * @image html example_board_setup_a.jpg "Use board setup A for this example."
 */

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

/*
8 bit = approx 0.01289 = 12.89 mV
10 bit = // 0.003226 = 3.226 mV
12 bit = // 0.00080565 = 0.80566 mV
14 bit = // 0.00020141 = 0.20141 mV
*/
static void saadc_handler(nrf_drv_saadc_evt_t const *p_event)
{ // nrfx_saadc_evt_t *p_event
  printf("Saadc handler");
}
static void saadc_init()
{
  ret_code_t err_code;
  // Configure Pin read ADC value and single ended
  nrf_saadc_channel_config_t channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL(NRF_SAADC_INPUT_VDD, NRF_SAADC_INPUT_AIN2);
  
  // intialize SAADC handler
  err_code = nrf_drv_saadc_init(NULL, saadc_handler);
  APP_ERROR_CHECK(err_code);

  // Config channel 0
  err_code = nrfx_saadc_channel_init(0,&channel_config);
  APP_ERROR_CHECK(err_code);
  
}
void log_init()
{
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

}
/*
 * @brief Function for main application entry.
 */
int main(void)
{   log_init();
    saadc_init();
    nrf_saadc_value_t saadc_val;
    NRF_LOG_INFO("Application Started");


    while (1)
    {
      nrfx_saadc_sample_convert(0, &saadc_val);
      NRF_LOG_INFO("Sample value read:%d", saadc_val);
      NRF_LOG_INFO("Volts: " NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT(saadc_val *5/512)); 
      nrf_delay_ms(500);   
    }
}


/** @} */
