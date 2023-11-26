/** @file
 * @defgroup nrf_dev_wdt_example_main main.c
 * @{
 * @ingroup nrf_dev_wdt_example
 * @brief WDT Example Application main file.
 *
 * This file contains the source code for a sample application using WDT.
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "bsp.h"
#include "app_timer.h"
#include "app_error.h"
#include "nrf_drv_wdt.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"
#include "app_util_platform.h"

//Event Handler
nrfx_wdt_channel_id m_channel_id;



/**
 * @brief WDT events handler.
 */
void wdt_event_handler(void)
{
    bsp_board_leds_off();

    //NOTE: The max amount of time we can spend in WDT interrupt is two cycles of 32768[Hz] clock - after that, reset occurs
}

void wdt_init()
{
  ret_code_t err_code = NRF_SUCCESS;
  // creat struct config
  nrfx_wdt_config_t wdt_config =  NRFX_WDT_DEAFULT_CONFIG;
  // Init WDT
  err_code = nrfx_wdt_init(&m_channel_id,wdt_event_handler);
  APP_ERROR_CHECK(err_code);
  // Allocate WDT handle
  err_code = nrfx_wdt_channel_alloc(&m_channel_id);
  APP_ERROR_CHECK(err_code);
  nrfx_wdt_enable();// careful use: call when needed
}

/**
 * @brief Assert callback.
 *
 * @param[in] id    Fault identifier. See @ref NRF_FAULT_IDS.
 * @param[in] pc    The program counter of the instruction that triggered the fault, or 0 if
 *                  unavailable.
 * @param[in] info  Optional additional information regarding the fault. Refer to each fault
 *                  identifier for details.
 */


/**
 * @brief Function for main application entry.
 */
int main(void)
{   //init LED
    bsp_board_init(BSP_INIT_LEDS);
    
    nrf_gpio_cfg_input(BUTTON_1,NRF_GPIO_PIN_PULLUP);
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    nrf_drv_clock_lfclk_request(NULL);
    for(int i = 0; i <10 ; i++)
      {
        bsp_board_led_invert(0);
        nrf_delay_ms(100);

      }
    //Check board is reseted or not
    bsp_board_leds_off();
    wdt_init();
    while (1)
    {
      if(nrf_gpio_pin_read(BUTTON_1) == 0)
        {
          bsp_board_leds_on();
          
          while(nrf_gpio_pin_read(BUTTON_1)==0);
            bsp_board_leds_off();

        }
        nrfx_wdt_channel_feed(m_channel_id);
        __SEV();
        __WFE();
        __WFE();
    }
}

/** @} */
