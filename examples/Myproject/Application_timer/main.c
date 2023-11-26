#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nordic_common.h"
#include "boards.h"

#include "app_timer.h"
#include "nrf_gpio.h"
#include "nrf_drv_clock.h"
/**
 * @brief Function for application main entry.
 */
 #define led1 17
 APP_TIMER_DEF(m_timer);
 #define led_interval APP_TIMER_TICKS(300) // 300ms
static void nrf_clock_configure(){
ret_code_t err_code = nrf_drv_clock_init();
APP_ERROR_CHECK(err_code);

nrf_drv_clock_lfclk_request(NULL);
}
void app_timer_handler(void *p_context)
{
  nrf_gpio_pin_toggle(led1);

}
void timer_init()
{
  ret_code_t err_code;
// initialize app timer
 err_code = app_timer_init();
 APP_ERROR_CHECK(err_code);

 err_code = app_timer_create(&m_timer, APP_TIMER_MODE_REPEATED,app_timer_handler);
 APP_ERROR_CHECK(err_code);




}
int main(void)
{ 
  nrf_gpio_cfg_output(led1);
  nrf_clock_configure();
  timer_init();

  uint32_t err_code = app_timer_start(m_timer, led_interval, NULL);
  APP_ERROR_CHECK(err_code);

    while (true)
    {
        // Do nothing.
    }
}
/** @} */
