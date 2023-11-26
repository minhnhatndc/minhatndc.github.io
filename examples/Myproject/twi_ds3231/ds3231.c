#include "ds3231.h"
// A flag to indicate the transfer state
static volatile bool m_xfer_done = false;

void ds3231_twi_handler(nrf_drv_twi_evt_t const *p_event, void *p_context)
{
  switch(p_event->type)
  {
    case NRF_DRV_TWI_EVT_DONE:
      m_xfer_done = true;
      break;
    default:
    break;
  }
}
void DS3231_Init(ds3231_def_t *DS3231)
{
    ret_code_t err_code;
    const nrf_drv_twi_config_t twi_config_ds3231 = {
       .scl                = DS3231_SCL_PIN,
       .sda                = DS3231_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi_ds3231, &twi_config_ds3231, ds3231_twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi_ds3231);
}

static uint8_t BCD2DEC(uint8_t data)
{
  return (data >> 4)*10 + (data & 0x0F);
}

static uint8_t DEC2BCD(uint8_t data)
{
  return (data/10) << 4|(data%10);
}

//================================================================================================
bool i2c_write_byte(uint8_t address, uint8_t data)
{
  ret_code_t err_code;
  uint8_t   tx_buff[2];
  
  //write register address and data into transmiss buffer
  tx_buff[0]= address;
  tx_buff[1]= data;
  // set flag
  m_xfer_done = false;
  //transmit data over I2c bus
  err_code = nrf_drv_twi_tx(&m_twi_ds3231,DS3231_ADDRESS,tx_buff,2,false);
  //Wait for transmit finish
  while(m_xfer_done == false);
  //If there is no error the return true else return false
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("Tx write time error");
    return false;
  }
    return true;
}

bool i2c_read_byte(uint8_t address, uint8_t *readBuffer, uint8_t number_of_byte)
{
  ret_code_t err_code;
  //set flag to false to show the receiving is not yet completed
  m_xfer_done = false;

  //Send register address where we want to write data
  err_code = nrf_drv_twi_tx(&m_twi_ds3231,DS3231_ADDRESS,&address,1,true);
  while(m_xfer_done == false);
  if(err_code != NRF_SUCCESS)
  {
    return false;
  }

  // set the flag agian so that we can read data from Device's internal register
  
  m_xfer_done = false;
  //Recieve data from slave device
  err_code = nrf_drv_twi_rx(&m_twi_ds3231,DS3231_ADDRESS,readBuffer,number_of_byte);
  
  //wait until transmission complete;
  while(m_xfer_done == false);
  if(err_code != NRF_SUCCESS)
  {
    return false;
  }

  return true;
}
void i2c_write_time(uint8_t address, ds3231_def_t *DS3231, uint8_t Hour, uint8_t Min, uint8_t Sec)
{
  bool check = false;
  uint8_t tx_data[3];
  DS3231->TxTimeBuff[0] = DEC2BCD(Sec);
  DS3231->TxTimeBuff[1] = DEC2BCD(Min);
  DS3231->TxTimeBuff[2] = DEC2BCD(Hour);

  for(uint8_t i = 0; i <3; i++)
  {
     check = i2c_write_byte(address + i, DS3231->TxTimeBuff[i]);
  }
  if( check == false)
  {
    NRF_LOG_INFO("Set time error");
  }
  NRF_LOG_INFO("Set time completed")
}
void i2c_read_time(uint8_t address, ds3231_def_t *DS3231)
{
  bool check = false;
  uint8_t read_buff[3];

  for(int i = 0; i< 3; i++)
  {
    DS3231->RxTimeBuff[i] = 0;
  }
  check = i2c_read_byte(address,DS3231->RxTimeBuff,3);
  if(check == false)
  {
    NRF_LOG_INFO("Read time error");
  }
  DS3231->Sec   = BCD2DEC(DS3231->RxTimeBuff[0]);
  DS3231->Min   = BCD2DEC(DS3231->RxTimeBuff[1]);
  DS3231->Hours = BCD2DEC(DS3231->RxTimeBuff[2]);
  NRF_LOG_INFO("Read time completed");
}
void i2c_write_date(uint8_t address,ds3231_def_t *DS3231, uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year)
{
  bool check = false;
  DS3231->TxDateBuff[0] = DEC2BCD(Day);
  DS3231->TxDateBuff[1] = DEC2BCD(Date);
  DS3231->TxDateBuff[2] = DEC2BCD(Month);
  DS3231->TxDateBuff[3] = DEC2BCD(Year);

  for(uint8_t i = 0; i< 4; i++)
  {
    check = i2c_write_byte(address + i, DS3231->TxDateBuff[i]);
  }
  if( check == false)
  {
    NRF_LOG_INFO("Set Date error");
  }
  NRF_LOG_INFO("Set Date completed");
}

void i2c_read_date(uint8_t address, ds3231_def_t *DS3231)
{
  bool check;
  for (int i = 0; i < 4 ; i++)
  {
    DS3231->RxDateBuff[i] = 0;
  }
  check = i2c_read_byte(address,DS3231->RxDateBuff,4);
  if(check == false)
  {
    NRF_LOG_INFO("Read Date error");
  }
  DS3231->Day   = BCD2DEC(DS3231->RxDateBuff[0]);
  DS3231->Date  = BCD2DEC(DS3231->RxDateBuff[1]);
  DS3231->Month = BCD2DEC(DS3231->RxDateBuff[2]);
  DS3231->Year  = BCD2DEC(DS3231->RxDateBuff[3]);
  NRF_LOG_INFO("Read Date completed");
}
//================================================================================================


static void i2c_WriteTime(ds3231_def_t *DS3231)
{
  ret_code_t err_code;
  err_code = nrf_drv_twi_tx(&m_twi_ds3231,DS3231_ADDRESS,DS3231->TxTimeBuff,3,false);
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("Tx write time error");
  }
}

static void i2c_ReadTime(ds3231_def_t *DS3231)
{
  ret_code_t err_code;
  err_code = nrf_drv_twi_rx(&m_twi_ds3231,DS3231_ADDRESS,DS3231->RxTimeBuff,3);
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("Rx read time error");
  }
}

static void i2c_WriteDate(ds3231_def_t *DS3231)
{
  ret_code_t err_code;
  err_code = nrf_drv_twi_tx(&m_twi_ds3231,DS3231_ADDRESS,DS3231->TxDateBuff,4,false);
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("Tx write Date error");
  }
}

static void i2c_ReadDate(ds3231_def_t *DS3231)
{
  ret_code_t err_code;
  err_code = nrf_drv_twi_rx(&m_twi_ds3231,DS3231_ADDRESS,DS3231->RxDateBuff,4);
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("Rx read Date error");
  }
}



void DS3231_SetTime(ds3231_def_t* DS3231, uint8_t Hour, uint8_t Min, uint8_t Sec)
{
 
  DS3231->TxTimeBuff[0] = DEC2BCD(Hour);
  DS3231->TxTimeBuff[1] = DEC2BCD(Min);
  DS3231->TxTimeBuff[2] = DEC2BCD(Sec);
  i2c_WriteTime(DS3231);
}

void DS3231_GetTime(ds3231_def_t* DS3231)
{
  i2c_ReadTime(DS3231);
  DS3231->Sec   = BCD2DEC(DS3231->RxTimeBuff[0]);
  DS3231->Min   = BCD2DEC(DS3231->RxTimeBuff[1]);
  DS3231->Hours = BCD2DEC(DS3231->RxTimeBuff[2]);
}
void DS3231_SetDate(ds3231_def_t* DS3231, uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year)
{
  DS3231->TxDateBuff[0] = DEC2BCD(Day);
  DS3231->TxDateBuff[1] = DEC2BCD(Date);
  DS3231->TxDateBuff[2] = DEC2BCD(Month);
  DS3231->TxDateBuff[3] = DEC2BCD(Year);
  i2c_WriteDate(DS3231);
}
void DS3231_GetDate(ds3231_def_t* DS3231)
{
  i2c_ReadDate(DS3231);
  DS3231->Day   = BCD2DEC(DS3231->RxDateBuff[0]);
  DS3231->Date  = BCD2DEC(DS3231->RxDateBuff[1]);
  DS3231->Month = BCD2DEC(DS3231->RxDateBuff[2]);
  DS3231->Year  = BCD2DEC(DS3231->RxDateBuff[3]);
}