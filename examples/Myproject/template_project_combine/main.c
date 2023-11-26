#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nordic_common.h"
#include "boards.h"
#include "lcd_i2c.h"
#include "dht11.h"
#include "ds3231.h"
#include "gps_app.h"

#include "button_state.h"
#include "display_lcd.h"
//=============Define message =====================



//========================================

/**
 * @brief Function for application main entry.
 */


int main(void)
{   
    uint8_t b[16];
   
    
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    //gpio_init();
    NRF_LOG_INFO("start");
 NRF_LOG_FLUSH();
    //lcd_i2c_init();

    //CLCD_I2C_Init(&LCD,LCD_I2C_ADDRESS,20,4);
    //CLCD_I2C_Clear(&LCD);
    //CLCD_I2C_SetCursor(&LCD,0,0);
   // CLCD_I2C_WriteString(&LCD,"Hello");
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
    NRF_LOG_INFO("end"); NRF_LOG_FLUSH();
    while (true)
    {
        // Do nothing.
       

    //display_time();
    //display_date();
    //display_temparature_ds3231();
   }
}
/** @} */
