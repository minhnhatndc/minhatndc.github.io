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

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

//========================
#define m_top 10000
#define m_step 100
#define led 22


uint16_t step = m_top/m_step;

static nrf_pwm_values_grouped_t sequence_values[m_step * 2];

uint16_t value =0;
static nrfx_pwm_t m_pwm0 = NRFX_PWM_INSTANCE(0);
static void pwm0_event_handler(nrfx_pwm_evt_type_t evt_type)
{
  if(evt_type == NRFX_PWM_EVT_FINISHED)
    {
      NRF_LOG_INFO("Finish sequence event once");
    
    }

}
static void pwm_init()
{
  for(int i =0; i< m_step; i++)
    {
      value += step;
      sequence_values[i].group_0 = value;
      sequence_values[i].group_1 = value;

      sequence_values[m_step+i].group_0 = m_step - value;
      sequence_values[m_step + i].group_1 = m_step - value;
    }

    //configure
    nrfx_pwm_config_t const cfg0 = 
    {
      .output_pins = {
            BSP_LED_0| NRFX_PWM_PIN_INVERTED,// for group 0
            NRFX_PWM_PIN_NOT_USED, // for group 0
            led,// for group 1
            NRFX_PWM_PIN_NOT_USED // for group 1
          },
       .irq_priority = APP_IRQ_PRIORITY_LOWEST,
       .base_clock = NRF_PWM_CLK_1MHz,
       .count_mode = NRF_PWM_MODE_UP,
       .top_value = m_top,
       .load_mode = NRF_PWM_LOAD_GROUPED, // change mode
       .step_mode = NRF_PWM_STEP_AUTO
    };

    APP_ERROR_CHECK(nrfx_pwm_init(&m_pwm0, &cfg0,pwm0_event_handler));


}


void pwm_play()
{
  nrf_pwm_sequence_t const seq0 = 
  {
    .values.p_grouped = sequence_values,
    .length = NRF_PWM_VALUES_LENGTH(sequence_values),
    .repeats = 0,
    .end_delay = 0
  
  
  };

(void)nrfx_pwm_simple_playback(&m_pwm0, &seq0,1, NRFX_PWM_FLAG_LOOP);

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
    pwm_init();
    pwm_play();
    NRF_LOG_INFO("PWM started...");

    while(true)
    {
       
    }
}


/** @} */
