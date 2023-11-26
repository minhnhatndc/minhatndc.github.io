#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "boards.h"

#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"

#define led1 17
#define button1 13

static nrf_ppi_channel_t ppi_channel;

void interrupt_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t section)
{

}
static void gpioe_pins_init()
{
uint32_t err_code = NRF_SUCCESS;
err_code = nrf_drv_gpiote_init(); // initialize gpiote module
APP_ERROR_CHECK(err_code);
// create the config for input pin interrupt

nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
in_config.pull = NRF_GPIO_PIN_PULLUP;

err_code = nrf_drv_gpiote_in_init(button1, &in_config ,interrupt_pin_handler);
APP_ERROR_CHECK(err_code);

nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);
err_code = nrf_drv_gpiote_out_init(led1, &out_config);
APP_ERROR_CHECK(err_code);

nrf_drv_gpiote_out_task_enable(led1);
nrf_drv_gpiote_in_event_enable(button1,true);




}
//=======================================================================================
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
#define DHT11_ONE_WIRE_INPUT_PIN 21
#define level_1 1
#define level_0 0

uint8_t BT_Buff[20],BT_Buff1[20], str[20] = "ADC 1234";
uint16_t bytes_to_send = 20;
int flag = 0;

unsigned char DHT11_READ_1_BYTES_DATA();
void DHT11_DIR_INPUT();
void DHT11_DIR_OUTPUT();
void DHT11_START_SEQUENCE();
char DHT11_READ_5_BYTES_DATA();
void Convert_Humidity_Temperature_Values(unsigned char byte1);

 void DHT11_START_SEQUENCE()
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


char DHT11_READ_5_BYTES_DATA()
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

unsigned char DHT11_READ_1_BYTES_DATA()
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

void DHT11_DIR_INPUT()
{
                nrf_gpio_cfg_input(DHT11_ONE_WIRE_INPUT_PIN, NRF_GPIO_PIN_PULLUP);
}

void DHT11_DIR_OUTPUT()
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

//=-=====================================================================================

static void ppi_init()
{
  uint32_t err_code = NRF_SUCCESS;
  uint32_t button_evt_addr;
  uint32_t led_task_addr;
   
  err_code = nrf_drv_ppi_init();
  APP_ERROR_CHECK(err_code);
  // allocate channel
  err_code = nrf_drv_ppi_channel_alloc(&ppi_channel);
  APP_ERROR_CHECK(err_code);

  button_evt_addr = nrf_drv_gpiote_in_event_addr_get(button1);
  led_task_addr   = nrf_drv_gpiote_out_task_addr_get(led1);

  err_code = nrf_drv_ppi_channel_assign(ppi_channel, button_evt_addr,led_task_addr);
  APP_ERROR_CHECK(err_code);


  err_code = nrf_drv_ppi_channel_enable(ppi_channel);
  APP_ERROR_CHECK(err_code);


}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
   gpioe_pins_init();
   ppi_init();

  ret_code_t err;
    while (true)
    {
        // Do Nothing - GPIO can be toggled without software intervention.
             DHT11_START_SEQUENCE();
                        err = DHT11_READ_5_BYTES_DATA();
                        if(err == 0)
                        {
                                Convert_Humidity_Temperature_Values(Humidity_Int);
                                //NRF_LOG_INFO("Humidity %d\n",(int)Humidity_Int);
                                decimal_value2 = ((decimal_value2&0x0f)|0x30);
                                decimal_value1 = ((decimal_value1&0x0f)|0x30);
                               // NRF_LOG_INFO("humidity = %c%c\n",decimal_value2,decimal_value1);
                                __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "humidity = %c%c\n",decimal_value2,decimal_value1);
                    
                                   // sprintf((char *)BT_Buff,"HUM-%d",Humidity_Int);
                                //while(ble_nus_string_send(&m_nus, BT_Buff, &bytes_to_send) != NRF_SUCCESS);
        
                                //nop();
                                Convert_Humidity_Temperature_Values(TEMPERATURE_Int);
                                //NRF_LOG_INFO("Temperature = %d\n", (int)TEMPERATURE_Int);
                                decimal_value2 = ((decimal_value2&0x0f)|0x30);
                                decimal_value1 = ((decimal_value1&0x0f)|0x30);
                               // NRF_LOG_INFO("temp = %c%c\n",decimal_value2,decimal_value1);
                                //printf("temp = %c%c\n",decimal_value2,decimal_value1);
                               __LOG(LOG_SRC_APP, LOG_LEVEL_INFO, "Temp = %d\n",TEMPERATURE_Int);
                                                                                                                    
                                //sprintf((char *)BT_Buff1,"Temp-%d",TEMPERATURE_Int);
                                //strcat(BT_Buff1, BT_Buff);
                                //while(ble_nus_string_send(&m_nus, BT_Buff1, &bytes_to_send) != NRF_SUCCESS);
                                // nop();
                                //ip++;
                                                                }


    }
}


/** @} */
