#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nordic_common.h"
#include "boards.h"
#include "app_error.h"

#include "app_uart.h"
#include "nrf_uart.h"
#include "nrf_drv_uart.h"
#include "app_uart_ringbuff.h"

#include "ff.h"
#include "diskio_blkdev.h"
#include "nrf_block_dev_sdc.h"


#include "nrf_log.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"

//============define================
#define TX_BUFF_SIZE 256
#define RX_BUFF_SIZE 256

#define SCK_PIN 25
#define MISO_PIN 24
#define MOSI_PIN 23
#define CS_PIN 22
uint8_t cr;
#define FILE_NAME "Test1.txt"
char data[256];
//==================================


//======Fsdcard=====================
NRF_BLOCK_DEV_SDC_DEFINE(
        m_block_dev_sdc,
        NRF_BLOCK_DEV_SDC_CONFIG(
                SDC_SECTOR_SIZE,
                APP_SDCARD_CONFIG(MOSI_PIN,MISO_PIN, SCK_PIN, CS_PIN)
         ),
         NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "SDC", "1.00")
);
static FATFS fs;
static DIR dir;
static FILINFO fno;
static FIL file;
uint32_t bytes_written;
FRESULT ff_result;
DSTATUS disk_state = STA_NOINIT;
void sdcard_init()
{
  static diskio_blkdev_t drives[] = 
    {
      DISKIO_BLOCKDEV_CONFIG(NRF_BLOCKDEV_BASE_ADDR(m_block_dev_sdc,block_dev),NULL)
    };
  diskio_blockdev_register(drives, ARRAY_SIZE(drives));
  NRF_LOG_INFO("Initializing disk 0....");
  for(uint32_t retries= 3; retries && disk_state; --retries)
    {
      disk_state = disk_initialize(0);

    }
    if(disk_state)
      {
        NRF_LOG_INFO("Disk initialization failed.");
        return;
      }
     uint32_t blocks_per_mb = (1024uL * 1024uL) / m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_size;
     uint32_t capacity = m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_count / blocks_per_mb;
     NRF_LOG_INFO("Capacity: %d MB", capacity);
     
     NRF_LOG_INFO("Mounting volume...");
     ff_result = f_mount(&fs,"",1);
     if(ff_result)
      {
        NRF_LOG_INFO("Mount failed");
        return;

      }
      NRF_LOG_INFO("\r\n Listing directory: /");
    ff_result = f_opendir(&dir, "/");
    if (ff_result)
    {
        NRF_LOG_INFO("Directory listing failed!");
        return;
    }

    do
    {
        ff_result = f_readdir(&dir, &fno);
        if (ff_result != FR_OK)
        {
            NRF_LOG_INFO("Directory read failed.");
            return;
        }

        if (fno.fname[0])
        {
            if (fno.fattrib & AM_DIR)
            {
                NRF_LOG_RAW_INFO("   <DIR>   %s",(uint32_t)fno.fname);
            }
            else
            {
                NRF_LOG_RAW_INFO("%9lu  %s", fno.fsize, (uint32_t)fno.fname);
            }
        }
    }
    while (fno.fname[0]);
    NRF_LOG_RAW_INFO("");

}


//====== End Fsdcard================
//======Uart initialization=========
void log_init(void)
{
  ret_code_t err_code;
  err_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(err_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();

}
static void uart_handler(app_uart_evt_t *p_event)
{
  switch (p_event->evt_type)
    {
      case (APP_UART_COMMUNICATION_ERROR):
        NRF_LOG_INFO("Communication error");
        APP_ERROR_HANDLER(p_event->data.error_communication);
      break;
      case (APP_UART_FIFO_ERROR):
        NRF_LOG_INFO("APP UART FIFO ERROR");
        APP_ERROR_HANDLER(p_event->data.error_code);
      break;
      case (APP_UART_DATA_READY):
        app_uart_get(&cr);
        app_uart_ringbuffer_put(cr);
        printf("%c",cr);
        

      break;
    }
}
void uart_init(void)
{
  ret_code_t err_code;
  app_uart_comm_params_t p_params=
    {
      RX_PIN_NUMBER,
      TX_PIN_NUMBER,
      RTS_PIN_NUMBER,
      CTS_PIN_NUMBER,
      APP_UART_FLOW_CONTROL_DISABLED,
      false,
      NRF_UART_BAUDRATE_115200
    };
    APP_UART_FIFO_INIT(&p_params,RX_BUFF_SIZE, TX_BUFF_SIZE,uart_handler, APP_IRQ_PRIORITY_LOWEST, err_code);
    APP_ERROR_CHECK(err_code);


  
}
static void file_write()
{   app_uart_ringbuffer_copy_upto("\n", data);
   NRF_LOG_INFO("Writing to file " FILE_NAME "...");
   ff_result = f_open(&file, FILE_NAME, FA_READ|FA_WRITE|FA_OPEN_APPEND);
   if (ff_result != FR_OK)
    {
     NRF_LOG_INFO("Unable to open or create file: " FILE_NAME ".");
        return;
    }
 
    ff_result = f_puts(data,&file);
    if (ff_result != FR_OK)
    {
        NRF_LOG_INFO("Write failed\r\n.");
    }
    else
    {
        NRF_LOG_INFO("%d bytes written.", bytes_written);
    }

    (void) f_close(&file);
    return;
    }
//=======End Uart initializaton========
/**
 * @brief Function for application main entry.
 */
int main(void)
{   
    app_uart_ringbuffer_init();
    log_init();
    uart_init();
    sdcard_init();
    file_write(cr);
    while (true)
    {
        // Do nothing.
    }
}
/** @} */
