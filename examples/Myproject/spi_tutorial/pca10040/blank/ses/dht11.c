#include "dht11.h"

uint8_t check()
{
  uint8_t time =0;
  NRF_LOG_INFO("dth11_check");
  nrf_gpio_cfg_input(DHT11_PIN_READ, NRF_GPIO_PIN_NOPULL);
  
  NRF_LOG_INFO("Check bit 1 = %d",data_getval());
  while(nrf_gpio_pin_read(DHT11_PIN_READ) == 1 && time <100)
  {
    time++;
    nrf_delay_us(1);}
    if(time >80) 
    {
    return 1;
    }else return 0;
    time = 0;
  NRF_LOG_INFO("Check bit 0 = %d",data_getval());
  while(nrf_gpio_pin_read(DHT11_PIN_READ) == 0 && time <100)
  {
    time++;
    nrf_delay_us(1);
  }
  if(time >80)
  {
    return 1;
  }else return 0;

}
void start_seq()
{
  nrf_gpio_cfg_output(DHT11_PIN_READ);
  nrf_gpio_pin_clear(DHT11_PIN_READ);
  nrf_delay_ms(20);
  nrf_gpio_pin_write(DHT11_PIN_READ,1);
  nrf_delay_us(40);
  NRF_LOG_INFO("get ACK %d", nrf_gpio_pin_read(DHT11_PIN_READ));
}