/** @file
 * @defgroup rtc_example_main main.c
 * @{
 * @ingroup rtc_example
 * @brief Real Time Counter Example Application main file.
 *
 * This file contains the source code for a sample application using the Real Time Counter (RTC).
 *
 */

#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "boards.h"
#include "app_error.h"
#include <stdint.h>
#include <stdbool.h>


const nrfx_rtc_t rtc = NRFX_RTC_INSTANCE(2); // rtc 2 handle
#define led 17

//Init Clock frequence
static void lfclk_init()
{ 
  //Step1: init clock
  ret_code_t err_code = nrf_drv_clock_init();
  APP_ERROR_CHECK(err_code);
  /**
 * @brief Function for requesting the LFCLK.
 *
 * The low-frequency clock can be requested by different modules
 * or contexts. The driver ensures that the clock will be started only when it is requested
 * the first time. If the clock is not ready but it was already started, the handler item that is
 * provided as an input parameter is added to the list of handlers that will be notified
 * when the clock is started. If the clock is already enabled, user callback is called from the
 * current context.
 *
 * The first request will start the selected LFCLK source. If an event handler is
 * provided, it will be called once the LFCLK is started. If the LFCLK was already started at this
 * time, the event handler will be called from the context of this function. Additionally,
 * the @ref nrf_drv_clock_lfclk_is_running function can be polled to check if the clock has started.
 *
 * @note When a SoftDevice is enabled, the LFCLK is always running and the driver cannot control it.
 *
 * @note The handler item provided by the user cannot be an automatic variable.
 *
 * @param[in] p_handler_item A pointer to the event handler structure.
 */
  nrf_drv_clock_lfclk_request(NULL);
   
} 
//RTC handler
static void rtc_handler(nrfx_rtc_int_type_t int_type)
{
  if(int_type == NRFX_RTC_INT_TICK)
    {
      nrf_gpio_pin_toggle(led);
    }
}
// RTC init
static void rtc_init()
{
  ret_code_t err_code;
  //define struct config for RTC
  nrfx_rtc_config_t rtc_config = NRFX_RTC_DEFAULT_CONFIG;
  rtc_config.prescaler = 4095 ;// ticks = 32768/(4095+1) = 8hz = 12s

  //int rtc module
  err_code = nrfx_rtc_init(&rtc,&rtc_config,rtc_handler);
  APP_ERROR_CHECK(err_code);
  //Enable
  nrfx_rtc_tick_enable(&rtc,true);
  nrfx_rtc_enable(&rtc);

}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    bsp_board_init(BSP_INIT_LEDS);
    lfclk_init();
    rtc_init();
    
    while (true)
    {
        __SEV();
        __WFE();
        __WFE();
    }
}


/**  @} */
