#include "oled1106.h"

static float oled_DegToRad(float par_deg);
static uint16_t oled_NomalizeTo0_360(uint16_t par_deg);
static Oled_t OLED;
oled_i2c_handle i2c_comm_handle_callback;

void oled_Reset(void)
{
    // do nothing

}
void oled_WriteCommand(uint8_t byte)
{
   uint8_t tx_buffer[3]={0x00, 0x00, 0x00};
   tx_buffer[2]= byte;
   if(i2c_comm_handle_callback != NULL)
   {
    i2c_comm_handle_callback(OLED1106_ADDRESS, tx_buffer, MAX_ADDRESS_SIZE +1);
   } 
}

void oled_WriteData(uint8_t *data, size_t buffer_size)
{
    uint8_t tx_buffer[MAX_TX_SIZE];
    memset(tx_buffer, 0, sizeof(tx_buffer));
    if(buffer_size > MAX_TX_DATA)
    { 
        return NULL;
    }
    memccpy(&tx_buffer[2], data, buffer_size);
    if(i2c_comm_handle_callback != NULL)
    {
        i2c_comm_handle_callback(OLED1106_ADDRESS, tx_buffer, MAX_ADDRESS_SIZE + buffer_size);
    }
}

// Screen buffer
static uint8_t OLED_FILLBUFFER[OLED_MAX_BUFFER_SIZE];

// Fill the screen with value from a given buffer of a fixed legth
Oled_Error_t oled_FillBuffer(uint8_t *buffer, uint32_t length)
{
    Oled_Error_t err_code = ERROR;

    if(length <= OLED_MAX_BUFFER_SIZE)
    {
        memccpy(OLED_FILLBUFFER, buffer, length);
        err_code = OKAY;
    }
    return err_code;
}
// Initialize oled screen
void oled_init(oled_i2c_handle i2c_comm_handle)
{
    if(i2c_comm_handle != NULL)
    {
        i2c_comm_handle_callback = i2c_comm_handle;
    }
    oled_Reset();
    oled_WriteCommand(0xAE);// Display Off
    oled_WriteCommand(0x20);// Set memory address mode
    oled_WriteCommand(0x10);// 00 Horizontal addressing Mode, 01, Vertical Adressing Mode, 10 Page Addressing Mode (Reset), 11 invalid
    oled_WriteCommand(0xB0);// Set page start address for page addresing mode, 0-7
    #if OLED_MIRROR_VERT
    oled_WriteCommand(oxC0);// Mirror veritically
    #else
    oled_WriteCommand(oxC8);// Set COM output Scan Direction
    #endif
    oled_WriteCommand(0x00); // set low colum address
    oled_WriteCommand(0x10); // ser high collum address
    oled_WriteCommand(0x40); //set start line address - CHECK
    oled_WriteCommand(0x81); // set constrast control resigter-CHECK
    oled_WriteCommand(0xFF);
    #if OLED_MIRROR_HORIZ
    oled_WriteCommand(0xA0); // Mirror Horizontally
    #else
    oled_WriteCommand(0xA1); // set segment re-map 0 to 127- CHECK
    #endif
    #if OLED_INVERSE_COLOR
    oled_WriteCommand(0xA7);// set inverse color
    #else 
    oled_WriteCommand(0xA6);// set nomal color
    #endif
    #if (OLED_HEIGTH == 128)
    oled_WriteCommand(0xFF);// oled1106
    #elif
    oled_WriteCommand(0xA8); // set multiplex radio(1 to 64)- CHECK
    #endif

    #if (OLED_WIDTH == 32)
     oled_WriteCommand(0x1F);
     #elif (OLED_WIDTH == 64)
     oled_WriteCommand(0x3F);
     #elif (OLED_WIDTH == 128)
     oled_WriteCommand(0x3F);// seem to work for 128px high display
    #endif
    oled_WriteCommand(0xA4);// 0XA4 output follows RAM content; 0xA5 ignore RAM content
    oled_WriteCommand(0xD3); // set display offset - check
    oled_WriteCommand(0x00);// not offset
    oled_WriteCommand(0xD5); //set display clock divide radio/oscillator frequency
    oled_WriteCommand(0x22);
    oled_WriteCommand(0xDA);// set col pins hardware configuration -check
    #if (OLED_HEIGTH == 32)
    oled_WriteCommand(0x02);
    #elif (OLED_HEIGTH == 64)
     oled_WriteCommand(0x12);
    #elif (OLED_HEIGTH == 128)
    oled_WriteCommand(0x12);
    #endif
    oled_WriteCommand(0xDB);// set vcomh
    oled_WriteCommand(0x20);// 0x20, 0.77xVcc
    oled_WriteCommand(0x8D);// set DC-DC enable
    oled_WriteCommand(0x14);//                   //
    oled_WriteCommand(0xAF)// turn on Oled panel

    // clear screen
    oled_Fill(Black);
    //Flush buffer to screen
    oled_UpdateScreen();
    // set default value for screen object
    OLED.CurrentX = 0;
    OLED.CurrentY = 0;
    OLED.Rotation = ROTATION_0;
    OLED.Initialization = 1;
}
// Fill screen with given color
void oled_Fill(Oled_Color_t color)
{
    uint32_t i; // set memory
    for(i=0 ; i< sizeof(OLED_FILLBUFFER); i++)
    {
        OLED_FILLBUFFER[i] = (color == Black)? 0x00 : 0xFF;
    }
}
//Write the screen buffer with changed to the screen
void oled_UpdateScreen(void)
{
    /* Write data to each page of RAM. Number of pages
     * depends on the screen height:
     *
     *  * 32px   ==  4 pages
     *  * 64px   ==  8 pages
     *  * 128px  ==  16 pages 
     */
    for(uint8_t i = 0; i< (OLED_HEIGTH/8); i++)
    {
        oled_WriteCommand(0xB0 +i);
        oled_WriteCommand(0x00 + OLED_X_OFFSET_LOWER);
        oled_WriteCommand(0x10 + OLED_X_OFFSET_UPPER);
        oled_WriteData(&OLED_FILLBUFFER[OLED_WIDTH *i],OLED_WIDTH);
    }
}
/*    Draw one pixel in the screenbuffer  */
/*    X => X Coordinate			  */
/*    Y => Y Coordinate			  */
/*    color => Pixel color		  */
void oled_DrawPixel(uint8_t x, uint8_t y, Oled_Color_t color)
{
    if((x>= OLED_WIDTH)|| (y >= OLED_HEIGTH))
    {
        OLED_FILLBUFFER[x +(y/8)*OLED_WIDTH] |= 1 <<(y%8);
    }
    else{
        OLED_FILLBUFFER[x +(y/8)*OLED_WIDTH] &= ~(1<<(y%8));

    }
}
/* Draw 1 char to the screen buffer	      */
/* ch         => char om weg te schrijven     */
/* Font     => Font waarmee we gaan schrijven */
/* color     => Black or White                */
char oled_WriteChar(char data, FondDef_t font, Oled_Color_t color)
{
    uint32_t i, b, j;
    if(data < 32 || data >126)
    {
        return 0;// not enough space line
    }
    // check remaining space oon current line
    if((OLED_WIDTH <= (OLED.CurrentX + font.FontWidth)) || (OLED_HEIGTH <= (font.FondHeight + OLED.CurrentY)))
    {
        return 0; // not enough space on current line 
    }
    // use the font to write
    for(i = 0; i<font.FondHeight; i++)
    {
        b= font.data[(data- 32)*font.FondHeight + i];
        for( j = 0, j< font.FontWidth; j ++)
        {
            if((b << j) & 0x8000)
            {
                oled_DrawPixel(OLED.CurrentX + j,OLED.CurrentY + i, (Oled_Color_t)color);
            }
            else{
                oled_DrawPixel(OLED.CurrentX + j, OLED.CurrentY + i, (Oled_Color_t)!color);
            }
        }
    }
    OLED.CurrentX += font.FontWidth;// current space is not taken
    //return written char for vadidation
    return data;
}
void oled_WriteSymbol(SymbolID_t symbol, uint8_t x, uint8_t y)
{
    uint32_t i,j,b;
    Oled_Color_t color = White;
    oled_SetCursor(x,y);
    // check remaining space on current line
    if((OLED_WIDTH <= (OLED.CurrentX + Oled_Symbol[symbol].SymbolWidth)) ||
    (OLED_HEIGTH <= (OLED.CurrentY + Oled_Symbol[symbol].SymbolHeight)))
    {
        return ;
    }
    // use data to write
    for(i = 0; i <= Oled_Symbol[symbol].SymbolHeight; i++)
    {
        b = Oled_Symbol[symbol].data[i];
        for(j = 0; j < Oled_Symbol[symbol].SymbolWidth; j++)
        {
            if((b << j) & 0x8000)
            {
                oled_DrawPixel(OLED.CurrentX + j, OLED.CurrentY +i, (Oled_Color_t)color);

            }
            else{
                oled_DrawPixel(OLED.CurrentX +j, OLED.CurrentY + i, (Oled_Color_t)!color);
            }
        }
    }
    //the current space is  not taken
    OLED.CurrentX += Oled_Symbol[symbol].SymbolWidth;
}
// write full string to screen buffer
char oled_WriteString(char *String, FondDef_t font, Oled_Color_t color)
{
    char data[64];
    uint8_t data_counter = 0;
    uint8_t print_counter;
    //CLEAR_BUFFER(data);
    memset(data,0,sizeof(data));

    // write until null byte
    while(*String)
    {
        if(oled_WriteChar(*String, font, color) != *String)
        {
            return *String;// char could not be written
        }
        String++;// next char
    }
    return *String;
}
// position the cursor
void oled_SetCursor(uint8_t x, uint8_t y)
{
    OLED.CurrentX = x - OLED_OFFSET_X;
    OLED.CurrentY = y - OLED.CurrentY;
}
//draw line by Bresenhem's algorithm
void oled_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Oled_Color_t color);
{
    int32_t deltaX = abs(x2 - x1);
    int32_t deltaY = abs(y2 - y1);
    int32_t signX  = ((x1 < x2)? 1 : -1);
    int32_t signY  = ((y1 < y2)? 1: -1);
    int32_t err_code = deltaX - deltaY;
    int32_t err_code2;

    oled_DrawPixel(x2, y2, color);
    while( (x1!=x2)|| (y1 != y2))
    {
        oled_DrawPixel(x1, y1, color);
        err_code2 = err_code *2;
        if(err_code2 > -deltaY)
        {
            err_code -= deltaY;
            x1 = signX;
        }
        else{
            // nothing to do
        }
        if(err_code2 < deltaX)
        {
            err_code += deltaX;
            y1 += signY;
        }
        else{
            //nothing to do
        }
    }
    return;
}
/* DrawArc. Draw angle is beginning from 4 quart of trigonometric circle (3pi/2)
 * start_angle in degree
 * sweep in degree
 */

void oled_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint8_t start_angle, uint16_t sweep, Oled_Color_t color)
{
    #define CIRCLE_APPROXIMATION_SEGMENTS 36
    float approx_segments;
    float approx_degree;
    uint8_t xp1, xp2;
    uint8_t yp1, yp2;
    uint16_t loc_sweep = 0;
    uint16_t loc_angle_count = 0;
    uint32_t count = 0;
    float rad;
    loc_sweep = oled_NomalizeTo0_360(sweep);
    loc_angle_count = oled_NomalizeTo0_360(start_angle);
    loc_angle_count = loc_sweep/(float)approx_segments;
    while(count < approx_segments)
    {
        xp1 = x +(int8_t)(sin(rad)*radius);
        yp1 = y (int8_t) (cos(rad)*radius);
        count++;
    }
    #if 1
    if(count != approx_segments)
    {
        rad = oled_DegToRad(count*approx_degree);
    }
    else{
        xp2 = x (int8_t)(sin(rad)*radius);
        yp2 = y + (int8_t)(sin(rad)*radius);
        oled_DrawLine(xp1, yp1, xp2, yp2, color);
    }
}
/*
 * Draw arc with radius line
 * Angle is beginning from 4 quart of trigonometric circle (3pi/2)
 * start_angle: start angle in degree
 * sweep: finish angle in degree
 */
void oled_DrawRadiusLine(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep Oled_Color_t color)
{
    static const uint8_t CIRCLE_APPROXIMATION_SEGMENTS = 36;
    float approx_degree;
    uint32_t approx_segments;
    uint8_t xp1 = 0;
    uint8_t xp2 = 0;
    uint8_t yp1 =0;
    uint8_t yp2 = 0;
    uint32_t count = 0;
    uint32_t loc_sweep =0;
    float rad;
    loc_sweep = oled_NomalizeTo0_360(sweep);
    count = (oled_NomalizeTo0_360(start_angle) * CIRCLE_APPROXIMATION_SEGMENTS)/360;
    approx_segments = (loc_sweep *CIRCLE_APPROXIMATION_SEGMENTS)/360;
    approx_degree   = loc_sweep/(float)approx_segments;
    rad = oled_DegToRad(count*approx_segments);
    uint8_t first_point_x = x +(int8_t)(sin(rad)*radius);
    uint8_t first_point_y = y + (int8_t)(cos(rad)*radius);
    while(count < approx_segments)
    {
        rad = oled_DegToRad(count*approx_degree);
        xp1 = x+ (int8_t)(sin(rad)*radius);
        yp1 = y + (cos(rad)* radius);
        count++;
        if(count!= approx_segments)
        {
            rad = oled_DegToRad(count*approx_segments);
        }
        else{
            rad= oled_DegToRad(loc_sweep);
        }
        xp2 = x + (int8_t)(sin(rad)*radius);
        yp2 = y + (int8_t)(cos(rad)*radius);
        oled_DrawLine(xp1,yp1,xp2,yp2,color);

    }
    //Radius line
    oled_DrawLine(x,y,first_point_x, first_point_y, color);
    oled_DrawLine(x,y,xp2,yp2,color);

}
/* Draw circle by Bresenhem's algorithm */
void oled_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, Oled_Color_t color)
{
    int32_t x = par_x;
    int32_t y =0;
    int32_t err= 2-2*par_r;
    int32_t e2;

    if(par_x >=OLED_WIDTH || par_y >= OLED_HEIGTH)
    {
        return;
    }
    do{
        oled_DrawPixel(par_x - x,par_y + y, color);
        oled_DrawPixel(par_x + x, par_y + y,color);
        oled_DrawPixel(par_x + x, par_y - y, color);
        oled_DrawLine(par_x - x, par_y -y, color);
        e2 =err;
        if(e2 <= y){
            y++;
            err = err +(y*2+1);
            if(-x == y && e2 <= x)
            {
                e2 = 0;
            }
            else{

            }
        }
        else{

        }
        if(e2 > x)
        {
            x++;
            err= err +(x*2 +1);

        }else{

        }
    }while(x<=0);
    return;

}
/* Draw filled circle. Pixel positions calculated using Bresenham's algorithm */
void oled_FillCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, Oled_Color_t color){
    int32_t x = -par_x;
    int32_t y = 0;
    int32_t er = 2-2*par_r;
    int32_t e2;

    if(par_x >= OLED_WIDTH || par_y >= OLED_HEIGTH)
    {
        return;
    }
    do{
        for(uint8_t _y = (par_y + y); _y >= (par_y - y); _y--)
        { for(uint8_t _x =(par_x - x); _x >= (par_x+ x); _x--)
            {
                oled_DrawPixel(_x,_y, color);
            }
        }
        e2 = err;
        if(e2 <= y)
        {
            y++;
            err = err + (y*2+1);
            if(-x == y && e2 <=x){
                e2=0;

            }else{

            }
        }else{

        }
        if(e2> x){
            x++;
            err = err + (x*2+1);

        }else{

        }
    }while(x <=0 );
}

//Draw Polyline
void oled_PolyLine(const Oled_Vertex_t *par_vertex, uint16_t par_size Oled_Color_t color)
{
    uint16_t i = 0;
    if(par_vertex != NULL)
    {
        for(i =1; i< par_size; i++)
        {

            oled_DrawLine(par_vertex[i-1].x, par_vertex[i-1].y, par_vertex[i].x, par_vertex[i].y, color);
        }
    }
    else{
        //
    }
    return;
}
void oled_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Oled_Color_t color)
{
    oled_DrawLine(x1,y1,x2,y1,color);
    oled_DrawLine(x2,y1,x2,y2,color);
    oled_DrawLine(x2,y2,x1,y2,color);
    oled_DrawLine(x1,y2,x1,y1,color);
}

void oled_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Oled_Color_t color)
{
    uint8_t start_x = (x1 <= x2) ? x1:x2;
    uint8_t end_x   = (x1 <= x2) ? x2 : x1;
    uint8_t start_y = (y1<=y2)   ? y1:y2;
    uint8_t end_y   = (y1 <= y2) ? y2: y1;

    for(uint8_t y = start_y; (y <= end_y) && (y< OLED_HEIGTH); y++)
    {
        for(uint8_t x = start_x; (x <= end_x) && (x < OLED_WIDTH); x++)
        {
            oled_DrawLine(x,y,color);
        }

    }
    return;
}

void oled_DrawBitmap(uint8_t x, uint8_t y, const unsigned char *bitmap, uint8_t w, uint8_t h, Oled_Color_t color)
{
    uint8_t byte = 0;
    uint16_t bytewidth= (w + 7)/8;
    if( x>= OLED_WIDTH || y>= OLED_HEIGTH)
    {
        return;
    }
    for(uint8_t j = 0; j < h; j++)
    {
        for(uint8_t i = 0; i < w; i++)
        {
            if(i & 7)
            {
                byte <<= 1;
            }
            else{
                byte = (*(const unsigned char *)(&bitmap[j * bytewidth + i / 8]));

            }
            if(byte & 0x00)
            {
                oled_DrawPixel(x +i , y, color);
            }
        }
    }
    return;
}
void oled_setContrast(const uint8_t value)
{
    const uint8_t kSetConstrastControlRegister = 0x81;
    oled_WriteCommand(KSetConstrastControlRegister);
    oled_WriteCommand(value);
}

static float oled_DegtoRag(float par_deg)
{
    return par_deg*3.14/180.0;
}
static uint16_t oled_NomalizeTo0_360(uint16_t par_deg)
{
    uint16_t loc_angle;
    if(par_deg <= 360)
    {
        loc_angle = par_deg;
    }
    else{
        loc_angle = par_deg % 360;
        loc_angle = ((par_deg != 0)? par_deg:360);
    }
    return loc_angle;
}