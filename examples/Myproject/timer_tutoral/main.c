#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"
#include "nrf_gpio.h"
// step 1: 
const nrfx_timer_t TIMER_LED = NRFX_TIMER_INSTANCE(0);
//Step 3:
void timer_handler(nrf_timer_event_t evt_type, void *p_context){
switch(evt_type){
  case NRF_TIMER_EVENT_COMPARE0: // define in nrf_timer.h 
      //nrf_gpio_pin_toggle(LED_2);
  break;
  default:
  // Nothing
  break;
}


}
// Step 2
void timer_init(void){
uint32_t err_code;
err_code = NRF_SUCCESS;
uint32_t timer_ms = 300;
uint32_t timer_ticks;

// configure timer
nrfx_timer_config_t timer_cfg =  NRFX_TIMER_DEFAULT_CONFIG;

err_code = nrfx_timer_init(&TIMER_LED, &timer_cfg, timer_handler); // define in nrfx_timer.c
APP_ERROR_CHECK(err_code);

timer_ticks = nrfx_timer_ms_to_ticks(&TIMER_LED, timer_ms);// convert ms to ticks 

nrfx_timer_extended_compare(&TIMER_LED, NRF_TIMER_CC_CHANNEL0,timer_ticks,NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,true);

       
}

int main(void)
{
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_cfg_output(LED_2);

     nrf_gpio_pin_set(LED_1);
     nrf_gpio_pin_set(LED_3);
     nrf_gpio_pin_set(LED_2);
      nrf_gpio_pin_set(LED_4);
    // init and enable timer
    timer_init();
    nrfx_timer_enable(&TIMER_LED);

    while (1)
    {
       __WFI();
    }
}

/** @} */
