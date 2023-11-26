#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "dht11.h"
//#include "app_dht11.h"
//#include "nrf_temp.h"

#define ADD_RED_WHO_AM_I 0x0F
#define UC_WHO_AM_I_DEFAULT_VALUE 0x3F

#define SPI_BUFFER_SIZE 8
#define SPI_INSTANCE 0

#define SET_READ_SIMPLE_CMD(x) (x|0x80)

uint8_t spi_tx_buffer[SPI_BUFFER_SIZE];
uint8_t spi_rx_buffer[SPI_BUFFER_SIZE];

static volatile bool spi_xfer_done;

static const nrf_drv_spi_t m_spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);




/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_handler(nrf_drv_spi_evt_t const *p_event, void *p_context)
{
spi_xfer_done = true; // show the communication finished
} 
void spi_init()
{
  nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;

  spi_config.ss_pin = 27;
  spi_config.miso_pin = 26;
  spi_config.mosi_pin = 25;
  spi_config.sck_pin = 24;
  spi_config.frequency = NRF_DRV_SPI_FREQ_4M;
  APP_ERROR_CHECK(nrf_drv_spi_init(&m_spi,&spi_config, spi_handler,NULL));


}
int LIS3DH_read_reg(int reg)
{
  spi_tx_buffer[0] = SET_READ_SIMPLE_CMD(reg);
  spi_xfer_done= false;
  APP_ERROR_CHECK(nrf_drv_spi_transfer(&m_spi,spi_tx_buffer,3,spi_rx_buffer,2));
  while(spi_xfer_done == false);
  return  spi_rx_buffer[1];


}\
//=================================================================================

 uint16_t temperature, humidity;
//dht11_err_t err_code;
DHT11_t data;

//=================================================================================
int main(void)
{ 
   int intRegvalue;
   ret_code_t err;
   APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
   NRF_LOG_DEFAULT_BACKENDS_INIT();
   //spi_init();
   NRF_LOG_INFO("Start");
   //intRegvalue = LIS3DH_read_reg( ADD_RED_WHO_AM_I);
   //if(intRegvalue == UC_WHO_AM_I_DEFAULT_VALUE)
   //{
   // NRF_LOG_INFO("the WHO_Am_I is correct for the lis3dsh...");
   //}

    ret_code_t err_code;
 
    while (1)
    {
       // Do Nothing - GPIO can be toggled without software intervention.
      
      err_code = read_data(&data); 
       
      //if(err_code =  DATA_SUCCESS)
      {
       //NRF_LOG_INFO("Temparature = %d  humidity = %d.\n\r",(float)data.Temparature/10.0, (float) data.Humidation/10.0);
      }

     
    }

}
