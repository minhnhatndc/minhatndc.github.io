#ifndef OLED1106_H
#define OLED1106_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include <oled1106_fonts.h>
#include "nordic_common.h"
#include "nrf.h"
#include "boards.h"
#include "nrf_drv_twi.h"
#include "nrf_gpio.h"
#include "app_error.h"
#include "app_util_platform.h"

#define OLED1106_ADDRESS 0x78

#define MAX_TX_DATA      64
#define MAX_ADDRESS_SIZE 2
#define MAX_TX_SIZE      (MAX_TX_DATA + MAX_ADDRESS_SIZE)
#define OLED_WIDTH       128
#define OLED_HEIGTH      64

#ifndef OLED_OFFSET_X
#define OLED_OFFSET_X -2
#define OLED_X_OFFSET_LOWER (OLED_X_OFFSET & 0x0F)
#define OLED_X_OFFSET_UPPER ((OLED_X_OFFSET >> 4) & 0x07)
#else
#define OLED_X_OFFSET_LOWER 0
#define OLED_X_OFFSET_UPPER 0
#endif

#ifndef OLED_OFFSET_Y
#define OLED_OFFSET_Y  0
#endif

#define OLED_MAX_BUFFER_SIZE (OLED_WIDTH* OLED_HEIGTH)/8
#define RESET_OLED  0
#define OLED_WRITE_DATA 1
#define OLED_WRITE_COMMAND  2
#define OLED_DELAY          3
typedef enum{
    Black   =   0x00, /* Black color, no pixel		  */
    White   =   0x01, /* Pixel is set. Color depends on OLED  */
}Oled_Color_t;

typedef enum{
    OKAY   =   0x00,
    ERROR = 0x01
}Oled_Error_t;

typedef enum {
    ROTATION_0  =  0,
    ROTATION_90 = 1,
    ROTATION_180 = 2,
    ROTATION_270  =  3 
}Oled_Rotation_t;

typedef struct{
    uint16_t CurrentX;
    uint16_t CurrentY;
    Oled_Rotation_t Rotation;
    uint8_t Initialization;
    uint8_t DisplayOn;
}Oled_t;

typedef struct{
    uint8_t x;
    uint8_t y;
}Oled_Vertex_t;
/*Initialization Function I2C Oled*/
typedef void(*oled_i2c_handle)(uint8_t addr, uint8_t *data, uint16_t size);
void oled_init(oled_i2c_handle i2c_comm_handle);

void oled_fill(Oled_Color_t color);
void oled_UpdateScreen(void);
void oled_DrawPixel(uint8_t x, uint8_t y, Oled_Color_t color);
char oled_WriteChar(char data, FondDef_t font, Oled_Color_t color);
char oled_WriteString(char *String, FondDef_t font, Oled_Color_t color);
void oled_WriteSymbol(SymbolID_t symbol, uint8_t x, uint8_t y);
void oled_SetCursor(uint8_t x, uint8_t y);
void oled_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Oled_Color_t color);
void oled_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint8_t start_angle, uint16_t sweep, Oled_Color_t color);
void oled_DrawRadiusLine(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, Oled_Color_t color);
void oled_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, Oled_Color_t color);
void oled_FillCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, Oled_Color_t color);
void oled_PolyLine(const Oled_Vertex_t *par_vertex, uint16_t par_size, Oled_Color_t color);
void oled_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Oled_Color_t color);
void oled_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Oled_Color_t color);
void oled_DrawBitmap(uint8_t x, uint8_t y, const unsigned char *bitmap, uint8_t w, uint8_t h, Oled_Color_t color);
/**
 * @brief Sets the contrast of the display.
 * @param[in] value contrast to set.
 * @note Contrast increases as the value increases.
 * @note RESET = 7Fh.
 */
void oled_setContrast(const uint8_t value);

/* Low-level procedures	*/
void oled_Reset(void);
void oled_WriteCommand(uint8_t byte);
void oled_WriteData(uint8_t *data, size_t buffer_size);
Oled_Error_t oled_FillBuffer(uint8_t *buffer, uint32_t length);
static uint16_t oled_NomalizeTo0_360(uint16_t par_deg);
static float oled_DegtoRag(float par_deg);
#endif