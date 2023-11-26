#include "app_dht11.h"
unsigned char decimal_value3, decimal_value2,decimal_value1;
unsigned long int Count_micro_second = 0;
unsigned long int test_start_seq1;
unsigned long int test_start_seq2;
unsigned long int test_start_seq3;

unsigned char Humidity_Int;
unsigned char Humidity_DEC;
unsigned char TEMPERATURE_Int;
unsigned char TEMPERATURE_DEC;
unsigned char CHECKSUM;
unsigned char err;
unsigned int TEMPERATURE_VALUE;
unsigned int HUMIDITY_VALUE;

uint8_t BT_Buff[20],BT_Buff1[20], str[20] = "ADC 1234";
uint16_t bytes_to_send = 20;
int flag = 0;

static void data_setinput()
{
  nrf_gpio_cfg_input(DHT11_PIN, NRF_GPIO_PIN_PULLUP);
}

static void data_setoutput()
{
  nrf_gpio_cfg_output(DHT11_PIN);
  nrf_gpio_pin_set(DHT11_PIN);
}


static void data_delayus(uint32_t sec)
{
  nrf_delay_us(sec);
}

static void data_delayms(uint32_t sec)
{
  nrf_delay_ms(sec);
}
static void data_writepin(uint32_t pin, uint32_t data)
{
  nrf_gpio_pin_write(pin, data);
}
static uint32_t data_getval()
{
  return nrf_gpio_pin_read(DHT11_PIN);
}
static void data_clearval()
{
  nrf_gpio_pin_clear(DHT11_PIN);  
}

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
  data_delayus(50);
  if(data_getval() == 0)
  {
    return DHT11_NO_PULLUP;
  }

  //send start signal
  data_setoutput();
  data_clearval();
  data_delayms(18);//keep signal low for at least 18ms;
  data_setinput();
  data_delayus(40);

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
  //value-> Humidation  = ((float)buffer[0])*100 + buffer[1];
  //value-> Temparature = ((float)buffer[2])*100  + buffer[3];
   *temp = ((int)buffer[2])*100  + buffer[3];
   *humid= ((int)buffer[0])*100 + buffer[1];
  return  DHT11_OKAY;
   }


   void DHT11_START_SEQUENCE(void)
{
            DHT11_DIR_OUTPUT();

            nrf_gpio_pin_write(DHT11_ONE_WIRE_INPUT_PIN, level_1);
            //DHT11_ONE_WIRE_OUTPUT_PIN = 1;

            nrf_gpio_pin_write(DHT11_ONE_WIRE_INPUT_PIN, level_0);
            nrf_delay_ms(25);
            //ets_delay_us(22000);


            nrf_gpio_pin_write(DHT11_ONE_WIRE_INPUT_PIN, level_1);
            //  Delay_micro_second(30);
                nrf_delay_us(30);


            DHT11_DIR_INPUT();


            Count_micro_second = 0;
            //while(DHT11_ONE_WIRE_INPUT_PIN==0)
            while(nrf_gpio_pin_read(DHT11_ONE_WIRE_INPUT_PIN)==0)
            {

            //  printf("waiting for make line high by dht11\n");
                nrf_delay_us(1);
            }
            test_start_seq2 = Count_micro_second;

            Count_micro_second = 0;
            //  while(DHT11_ONE_WIRE_INPUT_PIN==1)
            while(nrf_gpio_pin_read(DHT11_ONE_WIRE_INPUT_PIN)==1)
            {
                    //printf("waiting for make line low by dht11\n");
                    nrf_delay_us(1);
            }
            test_start_seq3 = Count_micro_second;
}


char DHT11_READ_5_BYTES_DATA(void)
{
                //vTaskSuspendAll ();
                err = 0;
                Humidity_Int = DHT11_READ_1_BYTES_DATA();
                Humidity_DEC = DHT11_READ_1_BYTES_DATA();
                TEMPERATURE_Int = DHT11_READ_1_BYTES_DATA();
                TEMPERATURE_DEC = DHT11_READ_1_BYTES_DATA();
                CHECKSUM = DHT11_READ_1_BYTES_DATA();
//              printf("datas = %c %c\n",Humidity_Int,TEMPERATURE_Int);

                if (((Humidity_Int + Humidity_DEC + TEMPERATURE_Int + TEMPERATURE_DEC) & 0xff) != CHECKSUM) 
                {

                    NRF_LOG_INFO("got wrong values\n");
                   
                     //   __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "got wrong values\n");
                    return 1;
                }
                else
                {
                    NRF_LOG_INFO("got values\n");
                   // __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "got values\n");
                    return err;
                }
}

unsigned char DHT11_READ_1_BYTES_DATA(void)
{

            unsigned int i=0;
            unsigned char Return_Value=0;

            for(i=0;i<8;i++)
            {
                        Return_Value = Return_Value << 1;

                    //printf("inside low");
                    while((nrf_gpio_pin_read(DHT11_ONE_WIRE_INPUT_PIN)) == 0)
                    {
                                    //  printf("inside low");
                                    //NRF_LOG_INFO("inside low1");
                                        nrf_delay_us(5);
                    }
                    Count_micro_second = 0;

                    //printf("inside high");
                    //NRF_LOG_INFO("inside high");
                    while((nrf_gpio_pin_read(DHT11_ONE_WIRE_INPUT_PIN))==1)
                    {
                                Count_micro_second++;
                                nrf_delay_us(5);
                    }

                    if(Count_micro_second<7)
                    {   
                                    
                                    Return_Value = Return_Value | 0;
                    }
                    else
                    {
                                Return_Value = Return_Value | 1;
                    }       
            }
//      printf("return_value=%c\n",Return_Value);

    return Return_Value;

}

void DHT11_DIR_INPUT(void)
{
                nrf_gpio_cfg_input(DHT11_ONE_WIRE_INPUT_PIN, NRF_GPIO_PIN_PULLUP);
}

void DHT11_DIR_OUTPUT(void)
{
                nrf_gpio_cfg_output(DHT11_ONE_WIRE_INPUT_PIN);
                //DHT11_ONE_WIRE_DIR = 1;
}

void Convert_Humidity_Temperature_Values(unsigned char byte1)
{

            unsigned char intermediate_value1=0;                              //Varible required while converting the hex value to decimal value
                /*******************************************************************************
                Procedure to convert 8bit hex value to equivalent BCD value
                *******************************************************************************/
            decimal_value3=(byte1/100);
            intermediate_value1=byte1-(100*decimal_value3);
            decimal_value2=(intermediate_value1/10);
            decimal_value1=intermediate_value1-(10*decimal_value2);
}
