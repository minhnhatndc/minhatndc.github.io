#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"



#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

/* TWI instance ID. */
#define TWI_INSTANCE_ID     0
/* Number of possible TWI addresses. */
 

/**
 * @brief TWI initialization.
 */
//step 1
 static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
//step 2
void twi_event_handler()
{

}
void twi_init()
{

  ret_code_t err_code;
  const nrf_drv_twi_config_t twi_config =
  {
    .scl = 22,
    .sda = 23,
    .frequency = NRF_DRV_TWI_FREQ_100K,
    .clear_bus_init = false,
    .interrupt_priority = APP_IRQ_PRIORITY_HIGH
  };
  err_code = nrf_drv_twi_init(&m_twi,&twi_config,twi_event_handler,NULL);
  APP_ERROR_CHECK(err_code);
  nrf_drv_twi_enable(&m_twi);

}




/**
 * @brief Function for main application entry.
 */
int main(void)
{ ret_code_t err_code;
uint8_t address = 0x68;
uint8_t sample_data = 0x00;
APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
NRF_LOG_DEFAULT_BACKENDS_INIT();

NRF_LOG_INFO("Start");
NRF_LOG_FLUSH();
err_code = nrf_drv_twi_rx(&m_twi,address,&sample_data,sizeof(sample_data));
if(err_code == NRF_SUCCESS)
  {
    NRF_LOG_INFO("Success.......");  }
    
    while (true)
    {
        /* Empty loop. */
    }
}

/** @} */
