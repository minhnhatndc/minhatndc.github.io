#include "app_dht11.h"


 void data_setinput()
{
  nrf_gpio_cfg_input(DHT11_PIN, NRF_GPIO_PIN_PULLUP);
}

 void data_setoutput()
{
  nrf_gpio_cfg_output(DHT11_PIN);
  nrf_gpio_pin_set(DHT11_PIN);
}


 void data_delayus(uint32_t sec)
{
  nrf_delay_us(sec);
}

 void data_delayms(uint32_t sec)
{
  nrf_delay_ms(sec);
}
 void data_writepin(uint32_t pin, uint32_t data)
{
  nrf_gpio_pin_write(pin, data);
}
 uint32_t data_getval()
{
  return nrf_gpio_pin_read(DHT11_PIN);
}
 void data_clearval()
{
  nrf_gpio_pin_clear(DHT11_PIN);  
}
//================================================================================================================
 void dht11_start()
{
    NRF_LOG_INFO("dth11_start");
  nrf_gpio_cfg_output(DHT11_PIN);
  nrf_gpio_pin_write(DHT11_PIN,1);
  nrf_gpio_pin_write(DHT11_PIN,0);
  nrf_delay_ms(25);
  //nrf_gpio_pin_write(DHT11_PIN,1);
  nrf_gpio_cfg_input(DHT11_PIN,NRF_GPIO_PIN_PULLUP);
  nrf_delay_us(40);
  //nrf_gpio_cfg_input(DHT11_PIN,NRF_GPIO_PIN_PULLUP);
  NRF_LOG_INFO("Get ack = %d",data_getval());
   //nrf_delay_us(40);
  
  //NRF_LOG_INFO("Get value input = %d",data_getval());
}

//======================================================================================================================
 uint8_t dht11_check()
{
  uint8_t time =0;
  NRF_LOG_INFO("dth11_check");
  nrf_gpio_cfg_input(DHT11_PIN, NRF_GPIO_PIN_PULLUP);
  
  NRF_LOG_INFO("Check bit 1 = %d",data_getval());
  while(nrf_gpio_pin_read(DHT11_PIN) == 1 && time <100)
  {
    time++;
    nrf_delay_us(1);}
    if(time >80) 
    {
    return 1;
    }else return 0;
    time = 0;
  NRF_LOG_INFO("Check bit 0 = %d",data_getval());
  while(nrf_gpio_pin_read(DHT11_PIN) == 0 && time <100)
  {
    time++;
    nrf_delay_us(1);
  }
  if(time >80)
  {
    return 1;
  }else return 0;

}
uint8_t read_bit()
{
     NRF_LOG_INFO("dth11_read_bit");
  uint8_t time =0;
    NRF_LOG_INFO("Check bit 1 = %d",data_getval());
   while(nrf_gpio_pin_read(DHT11_PIN) == 1 && time <100)
  {
    time++;
    nrf_delay_us(1);}
 
  time = 0;
  NRF_LOG_INFO("Check bit 0 = %d",data_getval());
  while(nrf_gpio_pin_read(DHT11_PIN) == 0 && time <100)
  {
    time++;
    nrf_delay_us(1);
  }
  nrf_delay_us(40);

}

uint8_t read_byte()
{
  NRF_LOG_INFO("dth11_read_byte");
  uint8_t i;
  uint8_t data = 0;
  for(i=0; i<8;i++)
  {
  data = data <<1;
  data |= read_bit();
  }
  return data;
}
uint8_t data_read[5]={0,0,0,0,0};

void read_data_dht11()
{
uint8_t i;
dht11_start();
if(dht11_check() == 0)
{
  for(i = 0;i<5;i++)
  {
    NRF_LOG_INFO("data_read[%d] = %d",i, read_byte());
    data_read[i] = read_byte();
  }
}
}

uint8_t dht11_init()
{
  nrf_gpio_cfg_output(DHT11_PIN);
  nrf_gpio_pin_write(DHT11_PIN,1);
  dht11_start();

  return dht11_check();
}
//=====================================================================================================
dht11_err_t dht11_read(uint16_t *temp, uint16_t *humid)
{
  ret_code_t err_code;
  int cntr;
  int loopBits;
  uint8_t buffer[5];
  int i;
  int data;
  uint8_t value= 0;
 
  // int buffer
 for(i = 0; i< sizeof(buffer);i++)
 {
  buffer[i] = 0;
 }
  // set to input to check if the signal gets pullled up
  data_setinput();
  data_delayus(45);
  
  if(data_getval() == 0)
  {
  return DHT11_NO_PULLUP;
  }
  ////send start signal
  //data_setoutput();
  //data_clearval();
  //data_delayms(25);//keep signal low for at least 18ms;
  //data_setinput();
  //data_delayus(40);//data_delayus(40);
  ////check for ACK
  //NRF_LOG_INFO("Get ack = %d",data_getval());
  //if(data_getval() != 0)
  //{
  //  return DHT11_NO_ACK_0;
  //}
  dht11_start();
  //nrf_gpio_cfg_input(DHT11_PIN,NRF_GPIO_PIN_PULLUP);

  cntr = 0;
  NRF_LOG_INFO("Get signal  = %d",data_getval());
  while(nrf_gpio_pin_read(DHT11_PIN) == 0)
  {
    nrf_delay_us(1);
    cntr++;
  }
  NRF_LOG_INFO("Count 0 out");
   cntr = 0;
  while(nrf_gpio_pin_read(DHT11_PIN) == 1)
  {
    nrf_delay_us(1);
    cntr++;
  }
  NRF_LOG_INFO("Pin set to 0");
  //// wait for max 100us for the ack signal for sensor;
  //NRF_LOG_INFO("Get ack signal = %d",data_getval());
  //cntr = 16;
  //while(data_getval() == 0)
  //{
  //  data_delayus(5);
  //  if(cntr == 0)
  //  {
  //    return DHT11_NO_ACK_1;/* signal should be up for the ACK here */
  //  }
  //  --cntr;
  //}
  
  //  /* wait until it goes down again, end of ack sequence */
  //  NRF_LOG_INFO("Get ack sequence = %d",data_getval());
  //  cntr = 16;
  //  while(data_getval() !=0)
  //  {
     
  //    data_delayus(5);
  //    if(--cntr == 0)
  //    {
  //      return DHT11_NO_ACK_0;/* signal should be down to zero again here */
  //    }
  //  }

   // read 40bits data
   i = 0;
   data = 0;
   loopBits =40;
   do{
    cntr = 11;// wait max 55us
    NRF_LOG_INFO("Get byte = %d",data_getval());
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
  //value-> Humidation  = ((float)buffer[0])*100 + buffer[1];
  //value-> Temparature = ((float)buffer[2])*100  + buffer[3];
   *temp = ((int)buffer[2])*100  + buffer[3];
   *humid= ((int)buffer[0])*100 + buffer[1];
   return  DHT11_OKAY;
 }


  