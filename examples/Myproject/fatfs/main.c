/** @file
 * @defgroup fatfs_example_main main.c
 * @{
 * @ingroup fatfs_example
 * @brief FATFS Example Application main file.
 *
 * This file contains the source code for a sample application using FAT filesystem and SD card library.
 *
 */


#include "nrf.h"
#include "bsp.h"
#include "ff.h"
#include "diskio_blkdev.h"
#include "nrf_block_dev_sdc.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define FILE_NAME   "NORDIC.TXT"
#define  FILE_NAME_1 "Nhat1.TXT"
#define TEST_STRING "SD card example."

#define SDC_SCK_PIN     ARDUINO_13_PIN  ///< SDC serial clock (SCK) pin. // 25
#define SDC_MOSI_PIN    ARDUINO_11_PIN  ///< SDC serial data in (DI) pin. // 23
#define SDC_MISO_PIN    ARDUINO_12_PIN  ///< SDC serial data out (DO) pin. // 24
#define SDC_CS_PIN      ARDUINO_10_PIN  ///< SDC chip select (CS) pin. //22

/**
 * @brief  SDC block device definition
 * */
NRF_BLOCK_DEV_SDC_DEFINE(
        m_block_dev_sdc,
        NRF_BLOCK_DEV_SDC_CONFIG(
                SDC_SECTOR_SIZE,
                APP_SDCARD_CONFIG(SDC_MOSI_PIN, SDC_MISO_PIN, SDC_SCK_PIN, SDC_CS_PIN)
         ),
         NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "SDC", "1.00")
);

/**
 * @brief Function for demonstrating FAFTS usage.
 */

static void file_write(char data[])
{
   static FATFS fs;
    static DIR dir;
    static FILINFO fno;
    static FIL file;

    uint32_t bytes_written;
    FRESULT ff_result;
    DSTATUS disk_state = STA_NOINIT;

    // Initialize FATFS disk I/O interface by providing the block device.
    static diskio_blkdev_t drives[] =
    {
            DISKIO_BLOCKDEV_CONFIG(NRF_BLOCKDEV_BASE_ADDR(m_block_dev_sdc, block_dev), NULL)
    };

    diskio_blockdev_register(drives, ARRAY_SIZE(drives));

    NRF_LOG_INFO("Initializing disk 0 (SDC)...");
    for (uint32_t retries = 3; retries && disk_state; --retries)
    {
        disk_state = disk_initialize(0);
    }
    if (disk_state)
    {
        NRF_LOG_INFO("Disk initialization failed.");
        return;
    }

    uint32_t blocks_per_mb = (1024uL * 1024uL) / m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_size;
    uint32_t capacity = m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_count / blocks_per_mb;
    NRF_LOG_INFO("Capacity: %d MB", capacity);

    NRF_LOG_INFO("Mounting volume...");
    ff_result = f_mount(&fs, "", 1);
    if (ff_result)
    {
        NRF_LOG_INFO("Mount failed.");
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

    NRF_LOG_INFO("Writing to file " FILE_NAME_1 "...");
    ff_result = f_open(&file, FILE_NAME_1, FA_READ | FA_WRITE | FA_OPEN_APPEND);
    if (ff_result != FR_OK)
    {
        NRF_LOG_INFO("Unable to open or create file: " FILE_NAME_1 ".");
        return;
    }
    uint8_t buf[256];
    sprintf(buf,"Day la test 1", sizeof(buf));
    ff_result = f_puts(data, &file);
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
/**
 * @brief Function for main application entry.
 */
int main(void)
{
    bsp_board_init(BSP_INIT_LEDS);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("FATFS example started.");

    //fatfs_example();
    file_write("Hello world");
    while (true)
    {
        __WFE();
    }
}

/** @} */
