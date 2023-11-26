#include "display_lcd.h"



void display_menu_time()
{
  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD,"Time");
}
void display_menu_gps(){
  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD,"GPS");
}
void display_menu_bluetooth(){
  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD,"Bluetooth");

}
void display_menu_sleep(){
  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD,"Mearsure Sleep");
}

void display_menu_idle(){
  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD,"Idle.....");

}

void display_set_time(){
  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD,"Set Time");
}
void display_read_time(){
  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD,"Read Time");

}

void display_time()
{
  char buff[16];
  switch(Mode_time)
  {
    case(Mode24h):
      i2c_read_time(DS3231_ADDRESS_SEC,&DS3231);
      sprintf(buff,"%2d:%2d:%2d",DS3231.Hours,DS3231.Min,DS3231.Sec);
      CLCD_I2C_SetCursor(&LCD,0,1);
      CLCD_I2C_WriteString(&LCD,buff);
    break;
    case(Mode12h):
      i2c_read_time(DS3231_ADDRESS_SEC,&DS3231);
      if(DS3231.Hours < 12)
        {
        sprintf(buff,"%2d:%2d:%2dam",DS3231.Hours,DS3231.Min,DS3231.Sec);
        CLCD_I2C_SetCursor(&LCD,0,1);
        CLCD_I2C_WriteString(&LCD,buff);
        }else if(DS3231.Hours == 12)
                {
                  sprintf(buff,"%2d:%2d:%2dpm",DS3231.Hours,DS3231.Min,DS3231.Sec);
                  CLCD_I2C_SetCursor(&LCD,0,1);
                  CLCD_I2C_WriteString(&LCD,buff);
                }else if(DS3231.Hours > 12)
                  {
                  sprintf(buff,"%2d:%2d:%2dpm",DS3231.Hours -12,DS3231.Min,DS3231.Sec);
                  CLCD_I2C_SetCursor(&LCD,0,1);
                  CLCD_I2C_WriteString(&LCD,buff);
                  }else if(DS3231.Hours == 24)
                        {
                          sprintf(buff,"%2d:%2d:%2dpm",DS3231.Hours -24,DS3231.Min,DS3231.Sec);
                          CLCD_I2C_SetCursor(&LCD,0,1);
                          CLCD_I2C_WriteString(&LCD,buff);
                        }
    break;
  }
}
void display_time_test()
{
  char buff[16];
  switch(Mode_time)
  {
    case(Mode24h):
      
      sprintf(buff,"%2d:%2d:%2d",12,24,30);
      CLCD_I2C_SetCursor(&LCD,0,1);
      CLCD_I2C_WriteString(&LCD,buff);
    break;
    case(Mode12h):
      //i2c_read_time(DS3231_ADDRESS_SEC,&DS3231);
      if(DS3231.Hours < 12)
        {
        sprintf(buff,"%2d:%2d:%2dam|",2,30,54);
        CLCD_I2C_SetCursor(&LCD,0,1);
        CLCD_I2C_WriteString(&LCD,buff);
        }else if(DS3231.Hours == 12)
                {
                  sprintf(buff,"%2d:%2d:%2dpm|",12,2,3);
                  CLCD_I2C_SetCursor(&LCD,0,1);
                  CLCD_I2C_WriteString(&LCD,buff);
                }else if(DS3231.Hours > 12)
                  {
                  sprintf(buff,"%2d:%2d:%2dpm|",14 -12,2,23);
                  CLCD_I2C_SetCursor(&LCD,0,1);
                  CLCD_I2C_WriteString(&LCD,buff);
                  }else if(DS3231.Hours == 24)
                        {
                          sprintf(buff,"%2d:%2d:%2dpm|",24 -24,2,1);
                          CLCD_I2C_SetCursor(&LCD,0,1);
                          CLCD_I2C_WriteString(&LCD,buff);
                        }
    break;
  }
}
void display_time_setmode()
{
  char buffer[16];
  char bufferm[16];
  i2c_read_time(DS3231_ADDRESS_SEC,&DS3231);
  i2c_read_date(DS3231_ADDRESS_DAY,&DS3231);

  CLCD_I2C_Clear(&LCD);
  CLCD_I2C_SetCursor(&LCD,0,0);
  sprintf(buffer,"%2d:%2d:%2d",DS3231.Hours,DS3231.Min,DS3231.Sec);
  CLCD_I2C_WriteString(&LCD,buffer);
  
  CLCD_I2C_SetCursor(&LCD,0,1);
  sprintf(bufferm,"%2d,%2d-%2d-%2d",DS3231.Day,DS3231.Date,DS3231.Month,DS3231.Year);
  CLCD_I2C_WriteString(&LCD,bufferm);
}


void display_date()
{
  char buffer[16];
  char bufferm[4];
  char bufferd[4];
//  i2c_read_date(DS3231_ADDRESS_DAY,&DS3231);
  //state_month(DS3231.Month,bufferm);
  state_day(2,bufferd);
  sprintf(buffer,"%s,%2d-%2d |",bufferd,12,11);
  CLCD_I2C_SetCursor(&LCD,0,0);
  CLCD_I2C_WriteString(&LCD, buffer);
}
void display_temparature_ds3231()
{
  char buffer[16];
  i2c_read_temp(DS3231_ADDRESS_TEMP,&DS3231);
  int Temp_t = DS3231.Temp;
  sprintf(buffer,"%2dC", Temp_t);
  CLCD_I2C_SetCursor(&LCD,11,0);
  CLCD_I2C_WriteString(&LCD,buffer);
}

void display_temparature_dht11()
{
  char buffer[16];
  //read_data_dht11(&DHT11);
  int Temp_t = 32;//DHT11.Temparature;
  int Humd_t = 70;//DHT11.Humidation;
  sprintf(buffer,"%2doC", Temp_t);
  CLCD_I2C_SetCursor(&LCD,12,0);
  CLCD_I2C_WriteString(&LCD,buffer);
   for(int i = 0 ; i <16; i++)
  {
    buffer[i] = 0;
  }
  sprintf(buffer,"%2dPC",Humd_t);
  CLCD_I2C_SetCursor(&LCD,12,1);
  CLCD_I2C_WriteString(&LCD,buffer);
  for(int i = 0 ; i <16; i++)
  {
    buffer[i] = 0;
  }
}

int value_convert(float data)
{
  // dem bao nhieu so sau dau phay
    int res_tmp = 0;
    int res     = 0 ;
    int tmp     = data*100000;
    int i = 0;
    while(i < 5)
    {
        res_tmp = tmp%10;
        res = res+ res_tmp*pow(10,i);
        tmp = tmp/10;
        i++;
    }
    i = 0;
    return res;
}
 
void display_gps()
{
  char buffer[16];
  int num_int = 0;
  int num_dec = 0;
  char direction;
  gps_get();
  CLCD_I2C_Clear(&LCD);
  //dis play altitude
  CLCD_I2C_SetCursor(&LCD,0,0);
  //num_int= gpsData.ggastruct.lcation.latitude;
  //num_dec= value_convert(gpsData.ggastruct.lcation.latitude);
  //direction = gpsData.ggastruct.lcation.NS;
  num_int = 1234.45679;
  num_dec = value_convert(1234.45679);
  direction = 'N';
  sprintf(buffer,"%9d.%5d%c",num_int,num_dec,direction);
  CLCD_I2C_WriteString(&LCD,buffer);
  // display longtitude
  CLCD_I2C_SetCursor(&LCD,0,1);
  //num_int= gpsData.ggastruct.lcation.longtitude;
 // num_dec= value_convert(gpsData.ggastruct.lcation.longtitude);
  //direction = gpsData.ggastruct.lcation.EW;
  num_int = 2404.20011;
  num_dec = value_convert(2404.20011);
  direction = 'E';
  sprintf(buffer,"%9d.%5d%c",num_int,num_dec,direction);
  CLCD_I2C_WriteString(&LCD,buffer);
}

void display_bluetooth()
{
 
 char buffer[16];
 switch(Bluetooth_status)
 {
  case (Bluetooth_connect):
    CLCD_I2C_Clear(&LCD);
    CLCD_I2C_SetCursor(&LCD,0,0);
    CLCD_I2C_WriteString(&LCD,"Bluetooth:");
    CLCD_I2C_SetCursor(&LCD,0,1);
    CLCD_I2C_WriteString(&LCD,"Connected");
   break;
  case (Bluetooth_disconnect):
    CLCD_I2C_Clear(&LCD);
    CLCD_I2C_SetCursor(&LCD,0,0);
    CLCD_I2C_WriteString(&LCD,"Bluetooth:");
    CLCD_I2C_SetCursor(&LCD,0,1);
    CLCD_I2C_WriteString(&LCD,"Disconnected");
  break;
 }
}
void display_bluetooth_config()
{
    CLCD_I2C_Clear(&LCD);
    CLCD_I2C_SetCursor(&LCD,0,0);
    CLCD_I2C_WriteString(&LCD,"1.Connect");
    CLCD_I2C_SetCursor(&LCD,0,1);
    CLCD_I2C_WriteString(&LCD,"2.Disconnect");
}
void display_time_adjust()
{
  switch(Mode_cfg)
  {
    case(AdjustHour):
      CLCD_I2C_SetCursor(&LCD,1,0);
    break;
     case(AdjustMin):
      CLCD_I2C_SetCursor(&LCD,4,0);
    break;
     case(AdjustSec):
      CLCD_I2C_SetCursor(&LCD,7,0);
    break;
     case(AdjustDay):
      CLCD_I2C_SetCursor(&LCD,1,1);
    break;
     case(AdjustDate):
      CLCD_I2C_SetCursor(&LCD,3,1);
    break;
     case(AdjustMonth):
      CLCD_I2C_SetCursor(&LCD,6,1);
    break;
     case(AdjustYear):
      CLCD_I2C_SetCursor(&LCD,9,1);
    break;
  }

}
