#include "oled1106_config.h"
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void twi_oled_init(void)
{
    ret_code_t err_code;

  const nrf_drv_twi_config_t twi_config =
  {
    .scl  = OLED_SCL_PIN,
    .sda  = OLED_SDA_PIN,
    .frequency  =  NRF_DRV_TWI_FREQ_100K,
    .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
    .clear_bus_init = false
  
  };
  err_code = nrf_drv_twi_init(&m_twi,&twi_config,NULL,NULL);
  APP_ERROR_CHECK(err_code);

  nrf_drv_twi_enable(&m_twi);
} 