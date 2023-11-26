/* Define GPIOs before using */
#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

#define OLED_SCK_PIN	      NRF_GPIO_PIN_MAP(1, 15)
#define OLED_MOSI_PIN	      NRF_GPIO_PIN_MAP(1, 13)
#define OLED_SS_PIN	      	  NRF_GPIO_PIN_MAP(1, 12)
#define OLED_ENABLE_PIN       NRF_GPIO_PIN_MAP(1, 2)
#define OLED_DC_PIN           NRF_GPIO_PIN_MAP(1, 11)
#define OLED_RES_PIN          NRF_GPIO_PIN_MAP(1, 10)

/* Define macros for easier usage */
#define oled_enable()			nrf_gpio_pin_write(OLED_ENABLE_PIN, GPIO_PIN_SET)
#define oled_disable()			nrf_gpio_pin_write(OLED_ENABLE_PIN, GPIO_PIN_RESET)

#define oled_write_string(string, x, y) ssd1309_SetCursor(x, y);                              \
                                        ssd1309_WriteString(string, Font_7x10, White)

#define oled_write_mstring(string, x, y) ssd1309_SetCursor(x, y);			      \
                                         ssd1309_WriteString(string, Font_11x18, White)

#define oled_write_symbol(symbol, x, y) ssd1309_WriteSymbol(symbol, x, y)

#define oled_update_screen()		ssd1309_UpdateScreen()
#define oled_clear_screen()		ssd1309_Fill(Black)

typedef enum
{
    OLED_SPI_READY = 0,
    OLED_SPI_BUSY,
    OLED_SPI_NOT_AVAILABLE
} oled_spi_state_t;

//------------------------------------------------------------------------------
// Table generated by LCD Assistant
// http://en.radzio.dxp.pl/bitmap_converter/
//------------------------------------------------------------------------------
const unsigned char garfield_128x64 [] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xCF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFB, 0xE3, 0xFF, 0xF3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0xF3, 0xFF, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x1F, 0xD9, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x0F, 0x00, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0E, 0x1F, 0xF8, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x87, 0xF0, 0x07, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x3B, 0x80, 0x18, 0x00, 0x30, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x60, 0x00, 0x18, 0xC3, 0x01, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x01, 0x80, 0x00, 0x0F, 0xC3, 0x8F, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x03, 0x00, 0x00, 0x0C, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x0C, 0x00, 0x00, 0x0C, 0x07, 0xFF, 0xF8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x38, 0xC0, 0x18, 0x00, 0x00, 0x08, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x71, 0x80, 0x30, 0x00, 0x00, 0x08, 0x0F, 0xFC, 0xFC, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF7, 0x00, 0x60, 0x00, 0x00, 0x18, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x60, 0x00, 0x00, 0x18, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0xC0, 0x00, 0x00, 0x30, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x83, 0xE0, 0xC0, 0x00, 0x00, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x03, 0x1F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0E, 0x01, 0x00, 0xE7, 0xC0, 0x03, 0x80, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x01, 0x80, 0xE0, 0x00, 0x06, 0x00, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x83, 0x7F, 0xF0, 0x00, 0x38, 0x00, 0x26, 0xFF, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0xDC, 0x18, 0x1F, 0x87, 0xE0, 0x00, 0x26, 0xEF, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0xB8, 0x0E, 0x18, 0x00, 0x30, 0x00, 0x04, 0xCF, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x30, 0x0F, 0xC0, 0x00, 0x18, 0x00, 0x00, 0x8F, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x30, 0x38, 0x70, 0x00, 0x18, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x18, 0x00, 0x1F, 0x00, 0x18, 0x3B, 0x80, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x8E, 0x00, 0x03, 0x80, 0x70, 0x1F, 0xF8, 0x1C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x03, 0xE0, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x86, 0x00, 0x3F, 0x1F, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0xC3, 0x00, 0x00, 0x3F, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x3F, 0xC7, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0xE0, 0x07, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x07, 0xC0, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0xA4, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x16, 0x01, 0xC0, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x1E, 0x01, 0xC0, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x0C, 0x01, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x04, 0x01, 0xF3, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0C, 0x01, 0xEF, 0xF7, 0xE0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x18, 0x00, 0x07, 0xF0, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x18, 0x00, 0x07, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x30, 0x00, 0x06, 0x04, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x60, 0x00, 0x0C, 0x1C, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xFD, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xFD, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x07, 0x00, 0x00, 0x01, 0xC1, 0xE0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0x81, 0xE0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x39, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x01, 0xF0, 0x01, 0xE3, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x1F, 0x03, 0x8D, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x03, 0xFC, 0x3D, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x03, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xF1, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xE0, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xE0, 0xC0, 0x3F, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char github_logo_64x64[] =
{
    0x00, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00,
    0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
    0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
    0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x03, 0xFE, 0x3F, 0xFF, 0xFF, 0xFC, 0x7F, 0xC0,
    0x07, 0xFE, 0x07, 0xFF, 0xFF, 0xE0, 0x7F, 0xE0, 0x07, 0xFE, 0x01, 0xF8, 0x1F, 0xC0, 0x3F, 0xE0,
    0x0F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x0F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0,
    0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8,
    0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFC,
    0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE,
    0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFE,
    0x7F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFE, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
    0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
    0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
    0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
    0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
    0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE,
    0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFE,
    0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFE, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFC,
    0x3F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0x3F, 0xFF, 0xC0, 0x00, 0x00, 0x01, 0xFF, 0xFC,
    0x1F, 0x9F, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x1F, 0x87, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xF8,
    0x0F, 0xC3, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0xF0, 0x0F, 0xE1, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xF0,
    0x07, 0xF1, 0xFF, 0x80, 0x00, 0xFF, 0xFF, 0xE0, 0x07, 0xF0, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xE0,
    0x03, 0xF8, 0x3F, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x01, 0xF8, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80,
    0x00, 0xFC, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
    0x00, 0x7F, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x3F, 0xFF, 0x00, 0x00, 0xFF, 0xFC, 0x00,
    0x00, 0x0F, 0xFF, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x07, 0xFF, 0x00, 0x00, 0xFF, 0xE0, 0x00,
    0x00, 0x03, 0xFF, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x3F, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* SPI instances */
const nrf_drv_spi_t m_oled_spi   = NRF_DRV_SPI_INSTANCE(OLED_SPI_INSTANCE);

#if defined(SSD1309_USE_I2C)
void i2c_oled_comm_handle(uint8_t hdl_address, uint8_t *hdl_buffer, size_t hdl_buffer_size)
{
    nrf_drv_twi_tx(&m_oled_twi, hdl_address, hdl_buffer, hdl_buffer_size, false);
}
#elif defined(SSD1309_USE_SPI)
void spi_oled_comm_handle(uint8_t hdl_type, uint8_t *hdl_buffer, size_t hdl_buffer_size)
{
    switch (hdl_type)
    {
        case OLED_RESET:
        {
            /* CS = High (not selected) */
            nrf_gpio_pin_write(OLED_SS_PIN, GPIO_PIN_SET);

            /* Reset the OLED */
            nrf_gpio_pin_write(OLED_RES_PIN, GPIO_PIN_RESET);
            nrf_delay_ms(10);
            nrf_gpio_pin_write(OLED_RES_PIN, GPIO_PIN_SET);
            nrf_delay_ms(10);
            break;
        }

        case OLED_WRITE_COMMAND:
        {
            nrf_gpio_pin_write(OLED_DC_PIN, GPIO_PIN_RESET); 
            APP_ERROR_CHECK(nrf_drv_spi_transfer(&m_oled_spi, hdl_buffer, hdl_buffer_size, NULL, NULL));
            break;
        }

        case OLED_WRITE_DATA:
        {
            nrf_gpio_pin_write(OLED_DC_PIN, GPIO_PIN_SET); 
            APP_ERROR_CHECK(nrf_drv_spi_transfer(&m_oled_spi, hdl_buffer, hdl_buffer_size, NULL, NULL));
            break;
        }

        default: break;
    }
}
#endif

/**
 * @brief SPI initialization.
 */
void spi_init(void)
{
#if defined(SSD1309_USE_SPI)
    nrf_drv_spi_config_t oled_spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    oled_spi_config.ss_pin   = OLED_SS_PIN;
    oled_spi_config.mosi_pin = OLED_MOSI_PIN;
    oled_spi_config.sck_pin  = OLED_SCK_PIN;
#endif

#if SPI_USE_INTERRUPT
    APP_ERROR_CHECK(nrf_drv_spi_init(&m_oled_spi, &spi_config, oled_spi_callback, NULL));
#else
    APP_ERROR_CHECK(nrf_drv_spi_init(&m_oled_spi, &oled_spi_config, NULL, NULL));
#endif

#if defined(SSD1309_USE_SPI)
    nrf_gpio_cfg_output(OLED_ENABLE_PIN);
    nrf_gpio_cfg_output(OLED_RES_PIN);
    nrf_gpio_cfg_output(OLED_DC_PIN);
#endif
}

void oled_init()
{
    oled_enable();
    ssd1309_Init(spi_oled_comm_handle);
    ssd1309_Fill(Black);
}

int main(void)
{
    SSD1309_VERTEX loc_vertex[] =
    {
        {35, 40},
        {40, 20},
        {45, 28},
        {50, 10},
        {45, 16},
        {50, 10},
        {53, 16}
    };

	/* Initialize log. */
    log_init();   
	
	spi_init();
	
    /* Initialize oled. */
    oled_init();	
	
    while (1)
    {
        oled_clear_screen();
        oled_write_symbol(BLE, 32, 0);
        oled_write_string("Testing 123!!", 0, 32);
        oled_update_screen();
        nrf_delay_ms(3000);

        oled_clear_screen();
        ssd1309_Polyline(loc_vertex, sizeof(loc_vertex) / sizeof(loc_vertex[0]), White);
        ssd1309_DrawArc(30, 30, 25, 0, 360, White);
        oled_update_screen();
        nrf_delay_ms(3000);

        oled_clear_screen();
        ssd1309_Fill(White);
        ssd1309_DrawBitmap(0, 0, garfield_128x64, 128, 64, Black);
        oled_update_screen();
        nrf_delay_ms(3000);

        ssd1309_Fill(Black);
        ssd1309_DrawBitmap(32, 0, github_logo_64x64, 64, 64, White);
        oled_update_screen();
        nrf_delay_ms(3000);

        ssd1309_Fill(White);
        ssd1309_DrawBitmap(32, 0, github_logo_64x64, 64, 64, Black);
        oled_update_screen();
        nrf_delay_ms(3000);

        oled_clear_screen();
        for (uint32_t delta = 0; delta < 5; delta++)
        {
            ssd1309_DrawCircle(20 * delta + 30, 15, 10, White);
        }
        oled_update_screen();
        nrf_delay_ms(3000);

        oled_clear_screen();
        for (uint32_t delta = 0; delta < 5; delta++)
        {
            ssd1309_DrawRectangle(1 + (5 * delta), 1 + (5 * delta), SSD1309_WIDTH - 1 - (5 * delta), SSD1309_HEIGHT - 1 - (5 * delta), White);
        }
        oled_update_screen();
        nrf_delay_ms(3000);

		NRF_LOG_FLUSH();
	}
}
