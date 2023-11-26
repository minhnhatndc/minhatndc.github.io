#include "app_dht11.h"
static void data_setinput()
{
  nrf_gpio_cfg_input(DHT11_PIN, NRF_GPIO_PIN_PULLUP);
}
static uint32_t data_getval()
{
  return nrf_gpio_pin_read(DHT11_PIN);
}

static void data_setoutput()
{
  nrf_gpio_cfg_output(DHT11_PIN);
  nrf_gpio_pin_set(DHT11_PIN);
}

static void data_clearval()
{
  nrf_gpio_pin_clear(DHT11_PIN);  
}
static void data_delayus(uint32_t sec)
{
  nrf_delay_us(sec);
}

static void data_delayms(uint32_t sec)
{
  nrf_delay_ms(sec);
}

dht11_err_t dht11_read(dht11_t *value)
{
  ret_code_t err_code;
  int cntr;
  int loopBits;
  uint8_t buffer[5];
  int i;
  int data;
  // init log
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  // int buffer
  memset(buffer, 0, sizeof(buffer));
  // set to input to check if the signal gets pullled up
  data_setinput();
  data_delayus(50);
  if(data_getval() == 0)
  {
    return DHT11_NO_PULLUP;
  }

  //send start signal
  data_setoutput();
  data_clearval();
  data_delayms(20);//keep signal low for at least 18ms;
  data_setinput();
  data_delayus(50);

  //check for ACK
  if(data_getval() != 0)
  {
    return DHT11_NO_ACK_0;
  }
  // wait for max 100us for the ack signal for sensor;
  cntr = 18;
  while(data_getval() == 0)
  {
    data_delayus(5);
    if(--cntr == 0)
    {
      return DHT11_NO_ACK_1;/* signal should be up for the ACK here */
    }
  }
  
    /* wait until it goes down again, end of ack sequence */
    cntr = 18;
    while(data_getval() !=0)
    {
      data_delayus(5);
      if(--cntr == 0)
      {
        return DHT11_NO_ACK_0;/* signal should be down to zero again here */
      }
    }

   // read 40bits data
   i = 0;
   data = 0;
   loopBits =40;
   do{
    cntr = 11;// wait max 55us
    while(data_getval()== 0)
    {
      data_delayus(5);
      if(--cntr == 0)
      {
        return DHT11_NO_DATA_0;
      }
    }
    cntr= 15;/* wait max 75 us */
    while(data_getval() != 0)
      {
        data_delayus(5);
        if(--cntr == 0)
        {
          return DHT11_NO_DATA_1;

        }  
      }
    data <<= 1; /* next data bit */
    if(cntr < 10)
      {
        data |=1;
      }
    if(loopBits & 0x7 == 1)
      {
        buffer[i] = data;
        i++;
        data = 0;
      }
    
    }while(--loopBits != 0);
 /* now we have the 40 bit (5 bytes) data:
   * byte 1: humidity integer data
   * byte 2: humidity decimal data (not used for DTH11, always zero)
   * byte 3: temperature integer data
   * byte 4: temperature fractional data (not used for DTH11, always zero)
   * byte 5: checksum, the sum of byte 1 + 2 + 3 + 4
   */
  /* test CRC */
  if((uint8_t)(buffer[0] + buffer[1] + buffer[2] + buffer[3]) != buffer[4])
  {
    return DHT11_BAD_CRC;
  }
  //store data values for caller
  value-> Humidation  = ((float)buffer[0])*100 + buffer[1];
  value-> Temparature = ((float)buffer[2])*100  + buffer[3];
  return  DHT11_OKAY;
  NRF_LOG_INFO("Humid = %f\r\n", value->Humidation);
  NRF_LOG_INFO("Temp = %f\n\r", value->Temparature);
   
   
   }
