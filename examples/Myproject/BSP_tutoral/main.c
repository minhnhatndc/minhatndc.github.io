
#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nordic_common.h"
#include "boards.h"
#include "bsp.h"


#include "app_timer.h"
#include "nrf_error.h"
#include "nrf_drv_clock.h"

#include "nrf_log.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"

static void log_config()
{
}
static void clock_config()
{
  ret_code_t err_code = nrf_drv_clock_init();
  APP_ERROR_CHECK(err_code);

  nrf_drv_clock_lfclk_request(NULL);



}
void bsp_evt_handler(bsp_event_t evt)
{ uint32_t err_code;
  switch(evt){
  case BSP_EVENT_KEY_0:
  bsp_board_led_on(1);
  NRF_LOG_INFO("Led0 turn on");
  break;
  case BSP_EVENT_KEY_1:
  bsp_board_led_off(1);
  NRF_LOG_INFO("Led0 turn off");
  break;
  case BSP_EVENT_KEY_2:
  err_code = bsp_indication_set(BSP_INDICATE_FATAL_ERROR);
  APP_ERROR_CHECK(err_code);
  break;
  case BSP_EVENT_KEY_3:
  err_code = bsp_indication_set(BSP_INDICATE_IDLE);
  APP_ERROR_CHECK(err_code);
  break;

  default:

  break;
  
  }
}
void bsp_config()
{
  uint32_t err_code = bsp_init(BSP_INIT_BUTTONS| BSP_INIT_LEDS, bsp_evt_handler);
  APP_ERROR_CHECK(err_code);

  }

/**
 * @brief Function for application main entry.
 */
int main(void)
{   clock_config();
    // init APP_TIMER
    uint32_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
    //Init NRF_LOG
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    
    bsp_config();
    NRF_LOG_INFO("Application bsp here");

    while (true)
    {
        // Do nothing.
 
        
    }
}
/** @} */
