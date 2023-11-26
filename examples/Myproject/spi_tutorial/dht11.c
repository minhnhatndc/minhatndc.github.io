#include "dht11.h"
uint8_t       buffer[5];
uint16_t      temp,humid;

static uint32_t wait_for(bool pin)
{

  uint8_t delay_us = 100;
  do{
    if(nrf_gpio_pin_read(DHT11_PIN) == pin)
    {
      return DATA_SUCCESS;
    }
    nrf_delay_us(1);
    delay_us--;
  }while(delay_us);
  return DATA_NOACK;
}


 uint32_t data_read_bit()
{
  return nrf_gpio_pin_read(DHT11_PIN);
}

//https://www.twblogs.net/a/5ca72298bd9eee59d33309c1
static uint8_t read_byte_dht11(void)
{
    uint8_t  temp =0;
    for(int i=0; i< 8; i++)
    {
      if(wait_for(1) != DATA_SUCCESS)
      {
        NRF_LOG_INFO("Error 1");
        return DATA_NOACK; 
      }
      nrf_delay_us(28);
      if(nrf_gpio_pin_read(DHT11_PIN) == 1)
      {
        if(wait_for(0) != DATA_SUCCESS) 
        {
         NRF_LOG_INFO("error 2");
         return DATA_NOACK;
        }

        temp |= (uint8_t)(0x01 <<(7-i));
      }
      else{
          temp&=(uint8_t) ~(0x01<<(7-i));
      }
    
    }
    return temp;
}
//Khue Nguyen
static uint8_t dht11_read_byte()
{
  uint8_t data = 0;

  for(int i = 0 ; i <8 ; i++)
  {
    while(nrf_gpio_pin_read(DHT11_PIN)== 0);
    nrf_delay_us(40);
    if(nrf_gpio_pin_read(DHT11_PIN)== 0)
    {
      data &= ~(1<<(7-i));
    }else data |= 1<<(7-i);
    //while(wait_for(0) != DATA_SUCCESS);
  }
  return data;
}

/**
 void read_bit()
{
  int cntr;
  int loopBits;
  
  int i;
  int DataToBuffer;
 
  /* init buffer *
  for(i=0;i<sizeof(buffer); i++) {
    buffer[i] = 0;
  }
  /* now read the 40 bit data *
  i = 0;
  DataToBuffer = 0;
  loopBits = 40;
  do {
    cntr = 11; /* wait max 55 us *
    while(nrf_gpio_pin_read(DHT11_PIN)==0) {
     nrf_delay_us(5);
      if (--cntr==0) {
        NRF_LOG_INFO("get no data 0");
      }
    }
    cntr = 17; /* wait max 75 us *
    while(nrf_gpio_pin_read(DHT11_PIN)!=0) {
      nrf_delay_us(5);
      if (--cntr==0) {
        NRF_LOG_INFO("get no data 1");
      }
    }
    DataToBuffer <<= 1; /* next data bit *
    if (cntr<10) { /* data signal high > 30 us ==> data bit 1 *
      DataToBuffer |= 1;
    }
    if ((loopBits&0x7)==1) { /* next byte *
      buffer[i] = DataToBuffer;
      i++;
      DataToBuffer = 0;
    }
  } while(--loopBits!=0);

    /* now we have the 40 bit (5 bytes) data:
   * byte 1: humidity integer data
   * byte 2: humidity decimal data (not used for DTH11, always zero)
   * byte 3: temperature integer data
   * byte 4: temperature fractional data (not used for DTH11, always zero)
   * byte 5: checksum, the sum of byte 1 + 2 + 3 + 4
   */
  /* test CRC *
  if ((uint16_t)(buffer[0]+buffer[1]+buffer[2]+buffer[3])!=(uint16_t)buffer[4]) {
    NRF_LOG_INFO("get checksum bad");
  }

    /* store data values for caller *
  humid = (buffer[0]<<8)|buffer[1];
  temp = (buffer[2]<<8) |buffer[3];
  NRF_LOG_INFO("Humid = %d",humid/10);
  NRF_LOG_INFO("Temp = %d",temp/10);
}
**/

uint32_t read_data(DHT11_t *data)
{
  int cntr;
  int loopBits;
  int i;
  int DataToBuffer;
   /* init buffer */
  for(i = 0;i <sizeof(buffer); i++) 
  {
    buffer[i] = 0;
  }
  //Start communicate DHT11
  pin_data_out;
  pin_clear;
  nrf_delay_ms(20); //20
  pin_set;
  pin_data_in;
  nrf_delay_us(40); //40

  //Check ACK from DHT11
  if(nrf_gpio_pin_read(DHT11_PIN) == 0)
  { 
    nrf_delay_us(60);
    if(nrf_gpio_pin_read(DHT11_PIN))
    {
      NRF_LOG_INFO("DHT11 pull up 1");
    }else NRF_LOG_INFO("DHT11 no pull up 1");
    while(nrf_gpio_pin_read(DHT11_PIN));
  
    /* now read the 40 bit data */
    i = 0;
    DataToBuffer = 0;
    loopBits = 40;
    do {
      cntr = 11; /* wait max 55 us */
      while(nrf_gpio_pin_read(DHT11_PIN)==0) 
      {
        nrf_delay_us(5);
        if (--cntr==0) 
        {
          NRF_LOG_INFO("get no data 0");
        }
      }
    cntr = 17; /* wait max 75 us */
    while(nrf_gpio_pin_read(DHT11_PIN) !=0) 
    {
      nrf_delay_us(5);
      if (--cntr == 0) 
      {
        NRF_LOG_INFO("get no data 1");
      }
    }
    DataToBuffer <<= 1; /* next data bit */
    if (cntr<10) { /* data signal high > 30 us ==> data bit 1 */
      DataToBuffer |= 1;
    }
    if ((loopBits & 0x7) ==1) { /* next byte */
      buffer[i] = DataToBuffer;
      i++;
      DataToBuffer = 0;
    }
  } while(--loopBits!=0);

    /* now we have the 40 bit (5 bytes) data:
   * byte 1: humidity integer data
   * byte 2: humidity decimal data (not used for DTH11, always zero)
   * byte 3: temperature integer data
   * byte 4: temperature fractional data (not used for DTH11, always zero)
   * byte 5: checksum, the sum of byte 1 + 2 + 3 + 4
   */
  /* test CRC */
  if ((uint16_t)(buffer[0]+buffer[1]+buffer[2]+buffer[3])!=(uint16_t)buffer[4]) {
    NRF_LOG_INFO("get checksum bad");
  }
  
  data->humid_int = buffer[0];
  data->humid_dec = buffer[1];
  data->temp_int  = buffer[2];
  data->temp_dec  = buffer[3];
  data->checksum  = (uint16_t)buffer[4];

    /* store data values for caller */
  data->Humidation  = ( data->humid_int<<8) | (data->humid_dec);
  data->Temparature = (data->temp_int <<8)  | (data->temp_dec);
  NRF_LOG_INFO("Humid = %d",  data->Humidation/10);
  NRF_LOG_INFO("Temp = %d",   data->Temparature /10);

  }

}





















/*

uint32_t read_data(DHT11_t *data)
{

  pin_data_out;
  pin_clear;
  nrf_delay_ms(20); //20
  pin_set;
  pin_data_in;
  nrf_delay_us(40); //40

/*
  if(nrf_gpio_pin_read(DHT11_PIN_READ) == 0)
  { 
    NRF_LOG_INFO("get ack 0 success");
  }else NRF_LOG_INFO("get ack 0 error");
  */
/*
  if(nrf_gpio_pin_read(DHT11_PIN_READ) == 0)
  { 
   nrf_delay_us(80);
   if(nrf_gpio_pin_read(DHT11_PIN_READ) ==1) 
   {
        NRF_LOG_INFO("DHT11 pull up 1");
   } else  NRF_LOG_INFO("DHT11 no pull up 1");
   while(nrf_gpio_pin_read(DHT11_PIN_READ) == 1);
  }

   data->humid_int = read_byte_dht11();
   data->humid_dec = read_byte_dht11();
   data-> temp_dec = read_byte_dht11();
   data-> temp_int = read_byte_dht11();
   data->checksum  = read_byte_dht11();
   pin_data_out;
   pin_set;

   if(data->checksum = data->humid_dec+ data->humid_int + data->temp_dec + data->temp_int)
  { 
    NRF_LOG_INFO("get checksum success");
  }
  else NRF_LOG_INFO("get checksum error");
  data->Temparature = ((data->temp_int) << 8) | data->temp_dec;
  data->Humidation = ((data->humid_int) << 8) | data->humid_dec;
  NRF_LOG_INFO("get data success");
  return  DATA_SUCCESS;

*/

/**
    if(nrf_gpio_pin_read(DHT11_PIN_READ) == 0)
  { 
   
   nrf_delay_us(40);
   if(nrf_gpio_pin_read(DHT11_PIN_READ))
   {
      NRF_LOG_INFO("DHT11 pull up 1");
   }else NRF_LOG_INFO("DHT11 no pull up 1");
   while(nrf_gpio_pin_read(DHT11_PIN_READ));
/* 
   data-> humid_int = read_byte_dht11();
   data-> humid_dec = read_byte_dht11();
   data-> temp_dec = read_byte_dht11();
   data-> temp_int = read_byte_dht11();
   data-> checksum  = read_byte_dht11();
*
   NRF_LOG_INFO("read humd int");
   data-> humid_int =   dht11_read_byte();
   NRF_LOG_INFO("read humd dec");
   data-> humid_dec =   dht11_read_byte();
   NRF_LOG_INFO("read temp int");
   data-> temp_dec  =   dht11_read_byte();
   NRF_LOG_INFO("read temp dec");
   data-> temp_int  =   dht11_read_byte();
   NRF_LOG_INFO("read checksum");
   data-> checksum  =   dht11_read_byte();
  
   NRF_LOG_INFO("read success");

   if((data->checksum = data->humid_dec + data->humid_int + data->temp_dec + data->temp_int))
  { 
    NRF_LOG_INFO("get checksum success");
  }
  else NRF_LOG_INFO("get checksum error");

  data->Temparature = ((data->temp_int) << 8) | data->temp_dec;
  data->Humidation = ((data->humid_int) << 8) | data->humid_dec;
  NRF_LOG_INFO("get data success");
  return  DATA_SUCCESS;
  }  
**/
/*
if(nrf_gpio_pin_read(DHT11_PIN) == 0)
  { 
   nrf_delay_us(60);
   if(nrf_gpio_pin_read(DHT11_PIN))
   {
      NRF_LOG_INFO("DHT11 pull up 1");
   }else NRF_LOG_INFO("DHT11 no pull up 1");
   while(nrf_gpio_pin_read(DHT11_PIN));
   read_bit();
 }
}
*/