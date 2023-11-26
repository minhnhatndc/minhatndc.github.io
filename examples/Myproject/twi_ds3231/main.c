/**
 * Copyright (c) 2016 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 * @defgroup tw_scanner main.c
 * @{
 * @ingroup nrf_twi_example
 * @brief TWI Sensor Example main file.
 *
 * This file contains the source code for a sample application using TWI.
 *
 */

#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"

#include "ds3231.h"


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
 #define TWI_ADDRESSES      127

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);


/**
 * @brief TWI initialization.
 */



/**
 * @brief Function for main application entry.
 */

ds3231_def_t DS3231;

int main(void)
{
    ret_code_t err_code;
    uint8_t address;
    uint8_t sample_data;
    bool detected_device = false;
  
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("TWI scanner started.");
    NRF_LOG_FLUSH();
    
    DS3231_Init(&DS3231);
    DS3231.Hours = 3;
    DS3231.Min   = 23;
    DS3231.Sec   = 4;

    DS3231.Date  = 5;
    DS3231.Day   = 7;
    DS3231.Month = 11;
    DS3231.Year  = 23;
    i2c_write_time(DS3231_ADDRESS_SEC,&DS3231,DS3231.Hours,DS3231.Min,DS3231.Sec);
    i2c_write_date(DS3231_ADDRESS_DAY,&DS3231,DS3231.Day,DS3231.Date,DS3231.Month,DS3231.Year);
    
    i2c_read_time(DS3231_ADDRESS_SEC,&DS3231);
    NRF_LOG_INFO("%d %d", DS3231.Hours, DS3231.Min);
    NRF_LOG_FLUSH();
    //i2c_write_date(DS3231_ADDRESS_DAY,&ds3231data,ds3231data.Day,ds3231data.Date,ds3231data.Month,ds3231data.Year);
    //i2c_read_time(DS3231_ADDRESS_SEC,&ds3231data);
    //   if(ds3231data.Sec > 59)
    //   {
    //    ds3231data.Sec = 0;
    //    ds3231data.Min= ds3231data.Min + 1;
    //   }
    //   if(ds3231data.Min > 59)
    //   {
    //    ds3231data.Min = 0;
    //    ds3231data.Hours+=1;
    //   }
    //   if(ds3231data.Hours == 24)
    //   {
    //   ds3231data.Hours = 0;
    //   }
    //   NRF_LOG_INFO("Hours = %d, Min = %d, Sec = %d \r\n",ds3231data.Hours, ds3231data.Min, ds3231data.Sec);
    //   NRF_LOG_FLUSH();
    //   i2c_read_date(DS3231_ADDRESS_DAY,&ds3231data);
    //   NRF_LOG_INFO("Day = %d, Date = %d, Month = %d, Year = %d \r\n",ds3231data.Day, ds3231data.Date, ds3231data.Month,ds3231data.Year);
    //   NRF_LOG_FLUSH();
    while (true)
    {  
        
        /* Empty loop. */
    }
}

/** @} */
