#ifndef  LCD_I2C
#define  LCD_I2C

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nordic_common.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define LCD_I2C_ADDRESS   0x27
#define LCD_I2C_SDA_PIN   29
#define LCD_I2C_SCL_PIN   28

/* TWI instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID_LCD     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID_LCD     1
#endif

#define CLCD_COMMAND                    0x00
#define CLCD_DATA                       0x01

#define LCD_EN                          0x04  // Enable bit
#define LCD_RW                          0x02  // Read/Write bit
#define LCD_RS                          0x01  // Register select bit

#define CLCD_COMMAND 			0x00
#define CLCD_DATA 			0x01

// commands
#define LCD_CLEARDISPLAY 		0x01
#define LCD_RETURNHOME 			0x02

#define LCD_ENTRYMODESET 		0x04
#define LCD_DISPLAYCONTROL 		0x08
#define LCD_CURSORSHIFT 		0x10
#define LCD_FUNCTIONSET 		0x20
#define LCD_SETCGRAMADDR 		0x40
#define LCD_SETDDRAMADDR	 	0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 			0x00
#define LCD_ENTRYLEFT 			0x02
#define LCD_ENTRYSHIFTINCREMENT         0x01
#define LCD_ENTRYSHIFTDECREMENT         0x00

// flags for display on/off control
#define LCD_DISPLAYON 			0x04
#define LCD_DISPLAYOFF 			0x00
#define LCD_CURSORON 			0x02
#define LCD_CURSOROFF 			0x00
#define LCD_BLINKON 			0x01
#define LCD_BLINKOFF 			0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 		0x08
#define LCD_CURSORMOVE 			0x00
#define LCD_MOVERIGHT 			0x04
#define LCD_MOVELEFT 			0x00

// flags for function set
#define LCD_8BITMODE 			0x10
#define LCD_4BITMODE 			0x00
#define LCD_2LINE                       0x08
#define LCD_1LINE 			0x00
#define LCD_5x10DOTS 			0x04
#define LCD_5x8DOTS 			0x00

#define LCD_BACKLIGHT 			0x08
#define LCD_NOBACKLIGHT 		0x00

static const nrf_drv_twi_t m_twi_lcd = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID_LCD);
typedef struct
{
	//nrf_drv_twi_evt_handler_t* I2C;
	uint8_t ADDRESS;
	uint8_t COLUMS;
	uint8_t ROWS;
	uint8_t ENTRYMODE;
	uint8_t DISPLAYCTRL;
	uint8_t CURSORSHIFT;
	uint8_t FUNCTIONSET;
	uint8_t BACKLIGHT;
}CLCD_I2C_Name;
/**
 * @brief Function for initializing the TWI driver.                
 */
void lcd_i2c_init();
/**
 * @brief Function for initializing the LCD.
 *
 * @param[in] LCD           Pointer to the LCD structure.
 * @param[in] Address       Address LCD slave.
 * @param[in] Colums        Colums position.
 * @param[in] Rows          Row position.                           
 */
void CLCD_I2C_Init(CLCD_I2C_Name* LCD, uint8_t Address, uint8_t Colums, uint8_t Rows);
void CLCD_I2C_SetCursor(CLCD_I2C_Name* LCD, uint8_t Xpos, uint8_t YPos);
void CLCD_I2C_WriteChar(CLCD_I2C_Name* LCD, char character);
void CLCD_I2C_WriteString(CLCD_I2C_Name* LCD, char *String);
void CLCD_I2C_Clear(CLCD_I2C_Name* LCD);
void CLCD_I2C_ReturnHome(CLCD_I2C_Name* LCD);
void CLCD_I2C_CursorOn(CLCD_I2C_Name* LCD);
void CLCD_I2C_CursorOff(CLCD_I2C_Name* LCD);
void CLCD_I2C_BlinkOn(CLCD_I2C_Name* LCD);
void CLCD_I2C_BlinkOff(CLCD_I2C_Name* LCD);


//void I2C_LCD_setCursor(uint8_t col, uint8_t row);
//void I2C_LCD_SendString(char *str);
#endif

/******************************************************************************************************************
@File:  	CLCD I2C Chip PCF8574
@Author:  Khue Nguyen
@Website: khuenguyencreator.com
@Youtube: https://www.youtube.com/channel/UCt8cFnPOaHrQXWmVkk-lfvg
Huong dan su dung:
- Su dung thu vien HAL
- Khoi tao bien LCD: CLCD_I2C_Name LCD1;
- Khoi tao LCD do: CLCD_I2C_Init(&LCD1,&hi2c1,0x4e,20,4);
- Su dung cac ham phai truyen dia chi cua LCD do: 
CLCD_I2C_SetCursor(&LCD1, 0, 1);
CLCD_I2C_WriteString(&LCD1,"hello anh em ");
******************************************************************************************************************/
