#include "LCD.h"

void LCD_ENABLE()
{
	NRF_GPIO->OUTSET = (1UL<<LCD_E);
	nrf_delay_us (10);
	NRF_GPIO->OUTCLR = (1UL<<LCD_E);
	nrf_delay_us (50);
}
void LCD_SET_DATA (uint8_t DATA)
{
	DATA = (DATA&0x0F);
	if (DATA & 0x01)
	{
		NRF_GPIO->OUTSET = (1UL<<LCD_DB4);
	}
	else
	{
		NRF_GPIO->OUTCLR = (1UL<<LCD_DB4);
	}
	if ((DATA>>1) & 0x01)
	{
		NRF_GPIO->OUTSET = (1UL<<LCD_DB5);
	}
	else
	{
		NRF_GPIO->OUTCLR = (1UL<<LCD_DB5);
	}
	if ((DATA>>2) & 0x01)
	{
		NRF_GPIO->OUTSET = (1UL<<LCD_DB6);
	}
	else
	{
		NRF_GPIO->OUTCLR = (1UL<<LCD_DB6);
	}
	if ((DATA>>3) & 0x01)
	{
		NRF_GPIO->OUTSET = (1UL<<LCD_DB7);
	}
	else
	{
		NRF_GPIO->OUTCLR = (1UL<<LCD_DB7);
	}
}
void LCD_CM_WRITE (uint8_t CM)
{
	NRF_GPIO->OUTCLR = (1UL<<LCD_RS);
	LCD_SET_DATA(CM>>4);
	LCD_ENABLE();
	LCD_SET_DATA(CM & 0x0F);
	LCD_ENABLE();
	nrf_delay_ms(10);
}
void LCD_DATA_WRITE (uint8_t DATA)
{
	NRF_GPIO->OUTSET = (1UL<<LCD_RS);
	LCD_SET_DATA(DATA>>4);
	LCD_ENABLE();
	LCD_SET_DATA(DATA & 0x0F);
	LCD_ENABLE();
	nrf_delay_ms(10);
}
void LCD_int()
{
	NRF_GPIO->OUTCLR = (1UL<<LCD_DB4);
	NRF_GPIO->OUTCLR = (1UL<<LCD_DB5);
	NRF_GPIO->OUTCLR = (1UL<<LCD_DB6);
	NRF_GPIO->OUTCLR = (1UL<<LCD_DB7);
	
	NRF_GPIO->OUTCLR = (1UL<<LCD_E);
	NRF_GPIO->OUTCLR = (1UL<<LCD_RS);
	
	nrf_delay_ms(15);
	LCD_SET_DATA(0x03);
	nrf_delay_ms(5);
	LCD_SET_DATA(0x03);
	nrf_delay_us(160);
	LCD_SET_DATA(0x03);
	nrf_delay_us(160);
	LCD_SET_DATA(0x02);
    
	LCD_CM_WRITE(0x28);    /* function set */
	 //LCD_CM_WRITE(0x08);
	LCD_CM_WRITE(0x0C);    /* display on,cursor off,blink off */
	LCD_CM_WRITE(0x01);    /* clear display */
	LCD_CM_WRITE(0x06);    /* entry mode, set increment */
}
void LCDBuildChar(uint8_t loc, uint8_t *p)
{
     unsigned char i;
	 
     if(loc<8)                                 //If valid address
	 {

		 LCD_CM_WRITE(0x40+(loc*8));               //Write to CGRAM
         for(i=0;i<8;i++)
            LCD_DATA_WRITE(p[i]);                   //Write the character pattern to CGRAM
     }
	 LCD_CM_WRITE(0x80);                           //shift back to DDRAM location 0
}
void lcd_gotoxy(unsigned char x, unsigned char y)
{
	if(y!=0) LCD_CM_WRITE(0xC0+x);
	else LCD_CM_WRITE(0x80+x);
	nrf_delay_us(1000);
}
