/** @file
 * @defgroup pwm_example_main main.c
 * @{
 * @ingroup pwm_example
 *
 * @brief PWM Example Application main file.
 *
 * This file contains the source code for a sample application using PWM.
 */

#include <stdio.h>
#include <string.h>
#include "nrf_drv_pwm.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

//========================
#define m_top 100
#define m_step 100
#define led1 22
#define led2 23
#define led3 24


uint16_t step = m_top/m_step;

uint16_t value =0;
static nrfx_pwm_t m_pwm0 = NRFX_PWM_INSTANCE(0);

nrf_pwm_values_individual_t seq_values[] = {0, 0 , 0 ,0}; // for channel 0,1,2,3
nrf_pwm_sequence_t seq0 = {
  .values.p_individual = seq_values,
  .length = NRF_PWM_VALUES_LENGTH(seq_values),
  .repeats = 0,
  .end_delay = 0
  
};
static void pwm_update_duty_cycle(uint8_t duty_1, uint8_t duty_2, uint8_t duty_3)
{
  if( duty_1 >= 100)
    {
      seq_values->channel_0 = 100;

    }
    if( duty_2 >= 100)
    {
      seq_values->channel_1 = 100;

    }
    if( duty_3 >= 100)
    {
      seq_values->channel_2 = 100;

    }
    else 
    {
      seq_values->channel_3 = duty_3;
    }

    (void)nrfx_pwm_simple_playback(&m_pwm0,&seq0, 1 , NRFX_PWM_FLAG_LOOP);

}
static void pwm_individual_init()
{
  

    //configure
    nrfx_pwm_config_t const cfg0 = 
    {
      .output_pins = {
            led1,
            led2, 
            led3,
            NRFX_PWM_PIN_NOT_USED // for group 1
          },
       .irq_priority = APP_IRQ_PRIORITY_LOWEST,
       .base_clock = NRF_PWM_CLK_1MHz,
       .count_mode = NRF_PWM_MODE_UP,
       .top_value = m_top,
       .load_mode = NRF_PWM_LOAD_INDIVIDUAL, // change mode
       .step_mode = NRF_PWM_STEP_AUTO
    };

    APP_ERROR_CHECK(nrfx_pwm_init(&m_pwm0, &cfg0,NULL));


}



void log_init()
{
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

}

int main(void)
{
    log_init();
    bsp_board_init(BSP_INIT_LEDS);
    pwm_individual_init();
  
    NRF_LOG_INFO("PWM started...");

    while(true)
    {
       pwm_update_duty_cycle(100,100,100);
       nrf_delay_ms(1000);
              pwm_update_duty_cycle(0,0,0);
       nrf_delay_ms(1000);
      

    }
}


/** @} */
