#ifndef APP_FILE_H
#define APP_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>



#include "ff.h"
#include "diskio_blkdev.h"
#include "nrf_block_dev_sdc.h"

#include "nrf_log.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"

#define BUFFER_FILE_MAX_SIZE 256U

#define FILE_NAME "TEST.TXT"


#define SDC_SCK_PIN 25
#define SDC_MOSI_PIN 23
#define SDC_MISO_PIN 24 
#define SDC_CS_PIN 22

typedef enum{
    data_write_OK = 0,
    data_write_notOK = 1,
    data_read_OK = 2,
    data_read_not_OK
}data_status_t;

typedef struct{
    volatile int8_t h;
    volatile int8_t t;
    uint32_t buffer[BUFFER_FILE_MAX_SIZE];
}file_def_t;

static FATFS fs; /* File system object structure (FATFS) */
static DIR direct; /* Directory object structure (DIR) */
static FILINFO fso; /* File information structure (FILINFO) : size, time, date*/
static FIL file; /* File object structure (FIL) */


void spi_init(void);
int app_file_data_check();
void app_file_data_mount(void);
int app_file_write_data(uint8_t data);
void app_file_init(void);
int app_file_read_data(void);


#endif