#ifndef OLED1106_FONTS_H
#define OLED1106_FONTS_H

#include "stdint.h"
#include "stdio.h"

#define FONT_7x10_ID   0x00
#define FONT_11x18_ID  0x01
#define FONT_16x26_ID  0x02
#define SYMBOL_7x10_ID  0x03
#define SYMBOL_11x18_ID 0x04
typedef enum{
    POWER,
    ENTER,
    ANTENNA,
    BATTERY_0,
    BATTERY_33,
    BATTERY_66,
    BATTERY_100,
    BLE,
    DOWN,
    UP,
    ALL_SYMBOL
} SymbolID_t;

typedef struct {
    const uint8_t SymbolID;
    const uint8_t SymbolWidth;
    uint8_t       SymbolHeight;
    const uint16_t *data;

}SymbolDef_t;

typedef struct{
    const uint8_t FontID;
    const uint8_t FontWidth;
    uint8_t       FondHeight;
    const uint16_t *data;
}FontDef_t;

extern FontDef_t Fond_7x10;
extern FontDef_t Font_11x18;
extern FontDef_t Font_16_26;

extern SymbolDef_t  Oled_Symbol[];
#endif
