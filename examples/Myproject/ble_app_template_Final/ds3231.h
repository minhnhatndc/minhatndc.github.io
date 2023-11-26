#ifndef DS3231_H
#define DS3231_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nordic_common.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

/* TWI instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif

/* Number of possible TWI addresses. */
#define DS3231_ADDRESS             0x68
 
#define DS3231_ADDRESS_SEC         0X00 
#define DS3231_ADDRESS_MIN         0x01
#define DS3231_ADDRESS_HOUR        0x02
#define DS3231_ADDRESS_DAY         0X03
#define DS3231_ADDRESS_DATE        0X04
#define DS3231_ADDRESS_MONTH       0X05
#define DS3231_ADDRESS_YEAR        0X06
#define DS3231_ADDRESS_TEMP        0X11

#define DS3231_SCL_PIN             27    // SCL signal pin
#define DS3231_SDA_PIN             26    // SDA signal pin
/* TWI instance. */
static const nrf_drv_twi_t m_twi_ds3231 = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

typedef struct{
        //nrf_drv_twi_evt_handler_t ds3231_handler;
        uint8_t TxTimeBuff[3];
	uint8_t RxTimeBuff[3];
	uint8_t TxDateBuff[4];
	uint8_t RxDateBuff[4];
        uint8_t RxTempBuff[2];

	uint8_t Hours;
	uint8_t Min;
	uint8_t Sec;
	uint8_t Date;
	uint8_t Day;
	uint8_t Month;
	uint8_t Year;
        uint8_t Temp;
}ds3231_def_t;

extern ds3231_def_t DS3231;

// function base not run

void DS3231_SetTime(ds3231_def_t* DS3231, uint8_t Hour, uint8_t Min, uint8_t Sec);
void DS3231_GetTime(ds3231_def_t* DS3231);
void DS3231_SetDate(ds3231_def_t* DS3231, uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year);
void DS3231_GetDate(ds3231_def_t* DS3231);

// Function run well and tested
void DS3231_Init(ds3231_def_t *DS3231);
void i2c_write_time(uint8_t address, ds3231_def_t *DS3231, uint8_t Hour, uint8_t Min, uint8_t Sec);
void i2c_read_time(uint8_t address, ds3231_def_t *DS3231);
void i2c_write_date(uint8_t address,ds3231_def_t *DS3231, uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year);
void i2c_read_date(uint8_t address, ds3231_def_t *DS3231);
void i2c_read_temp(uint8_t address, ds3231_def_t *DS3231);
/*
Note cach dung ham i2c_read/write:

Khi dung write_time phai truyen dia chi cua DS3231_ADDRESS_SEC
Khi dung read_time phai truyen dia chi DS3231_ADDRESS_SEC
Khi dung write_date phai truyen dia chi cua DS3231_ADDRESS_DAY
Khi dung read_date phai truyen dia chi DS3231_ADDRESS_DAY 

*/

#endif