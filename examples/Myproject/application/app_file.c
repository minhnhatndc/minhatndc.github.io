#include "app_file.h"
//=========define==============


uint32_t bytes_written;
FRESULT file_result;
/* Disk Status Bits (DSTATUS) 

#define STA_NOINIT		0x01	/ Drive not initialized 
#define STA_NODISK		0x02	/ No medium in the drive 
#define STA_PROTECT		0x04	/ Write protected 
*/
DSTATUS disk_state = STA_NOINIT;

void spi_init(void)
{
    ret_code_t err_code;

}
//==========================
/*
*brief SDC block device definition
*/
NRF_BLOCK_DEV_SDC_DEFINE(m_block_dev_sdc,
                NRF_BLOCK_DEV_SDC_CONFIG(SDC_SECTOR_SIZE,APP_SDCARD_CONFIG(SDC_MOSI_PIN,SDC_MISO_PIN,SDC_SCK_PIN,SDC_CS_PIN)),
                NFR_BLOCK_DEV_INFO_CONFIG("Test","SDcard","1.00")
                );
//====================== Init file======================
void app_file_init(void)
{
  //Initialize FATFS disk I/0 interface by providing the block dev
    static diskio_blkdev_t drivers[]=
    {
        DISKIO_BLOCKDEV_CONFIG(NRF_BLOCKDEV_BASE_ADDR(m_block_dev_sdc,block_dev),NULL)
    } ;
    diskio_blockdev_register(drivers,ARRAY_SIZE(drivers)); // register block device
    NRF_LOG_INFO("Initializing disk 0 Sdcard...");
    for(uint32_t retries = 3; retries && disk_state; --retries)
        {
            disk_state = disk_initialize(0);
        }
    if(disk_state)
        {
            NRF_LOG_INFO("Disk initialization failed.");
        }
    

}
int main(){


}
