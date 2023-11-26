#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"
#include "nrf_delay.h"


const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(0);

/**
 * @brief Handler for timer events.
 */
void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)
{
   
}


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    uint32_t time_ms = 500; //Time(in miliseconds) between consecutive compare events.
    uint32_t time_ticks;
    uint32_t err_code = NRF_SUCCESS;
    uint32_t count = 0;
    //Configure all leds on board.
    bsp_board_init(BSP_INIT_LEDS);

    //Configure TIMER_LED for generating simple light effect - leds on board will invert his state one after the other.
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;

    timer_cfg.mode = NRF_TIMER_MODE_COUNTER;
    err_code = nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_led_event_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_enable(&TIMER_LED);
    
    while (1)
    {
        nrfx_timer_increment(&TIMER_LED);
        count = nrfx_timer_capture(&TIMER_LED, NRF_TIMER_CC_CHANNEL0);
        printf("Counter value: %d\n", count);
        nrf_delay_ms(1000);

    }
}

/** @} */
