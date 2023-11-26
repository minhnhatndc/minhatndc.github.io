#include "gps_app.h"

int       FlagGGA   = 0;
int       FlagRMC   = 0;
char      gga_data[128];
char      rmc_data[128];
int hr = 0, minute = 0, day=0, month =0, year =0;
int daychange       = 0;
int GMT             = +700;
GPSSTRUCT           gpsData;
//==================================================================
int gga_check(char *rmcbuff){
    if( (rmcbuff[3]== 'G') && (rmcbuff[4]== 'G')&& (rmcbuff[5]== 'A')){
       return 1;
    }else return 0;
}

// $GPGGA,150925.00,1021.77768,N,10623.03480,E,1,05,1.80,17.4,M,-2.7,M,,*72
 int decodeGGA (char *GGAbuffer, GGASTRUCT *gga){
    char buffer [12];
    int  inx = 0;
    int  i=0;

    while(GGAbuffer[inx]!= ',') inx++;
    inx++;
    while(GGAbuffer[inx]!= ',') inx++;
    inx++;
    while(GGAbuffer[inx]!= ',') inx++;
    inx++;
    while(GGAbuffer[inx]!= ',') inx++;
    inx++;
    while(GGAbuffer[inx]!= ',') inx++;
    inx++;
    while(GGAbuffer[inx]!= ',') inx++;
    inx++;
    if((GGAbuffer[inx]=='1')||(GGAbuffer[inx]=='2')|| GGAbuffer[inx]=='6'){
        gga->isfixValid = 1; // Fix is available
        inx = 0;
        } else {
          gga->isfixValid = 0; //Fix is not available
          return 1;           // return Error
          }
 //========Get Time========================================
 //// $GPGGA,150925.00,
 while(GGAbuffer[inx] != ',') inx++;  
 inx++;
 i=0;
 memset(buffer,'\0', 12);
 while(GGAbuffer[inx]!=','){
  buffer[i]= GGAbuffer[inx];
  i++;
  inx++;
    }
  hr      = (atoi(buffer)/10000)+GMT/100;
  minute  = ((atoi(buffer)/100)%100) + GMT%100;
  if(minute>59){
    minute=minute-60;
    hr++;
    }
   if(hr <0){
      hr=24 + hr;
      daychange --;
   
   }
  if(hr >= 24){
    hr = hr - 24;
    daychange= 1;
    }
   // Store time in gga structure
   gga->tim.hour  = hr;
   gga->tim.min   = minute;
   gga->tim.sec   = atoi(buffer)%100;
   //printf("\nHr:%2d min: %2d sec: %2d", gga->tim.hour,  gga->tim.min, gga->tim.sec);

  //============Get Latitude====================================
  inx++;
  i= 0;
  memset(buffer,'\0',12);
  while(GGAbuffer[inx]!= ','){       //00,1021.77768,N,
    buffer[i] = GGAbuffer[inx];
    i++;
    inx++;   
    }
  if (strlen(buffer)< 6) return 2;
  uint16_t num= atoi(buffer);
  int j=0;
  while (buffer[j]!='.') j++;
  j++;
  int declen    = strlen(buffer) -j;
  int dec       = atoi((char*)buffer +j);
  float lat     = (num/100.0) + (dec/(pow(10,(declen+2))));
  gga->lcation.latitude   = lat;
  inx++;
  gga->lcation.NS         = GGAbuffer[inx];

  //===============GET Longtitude==========================
  inx++;
  inx++;
  memset(buffer,'\0',12);
  i=0;
  while(GGAbuffer[inx]!=',')
    {
    buffer[i]= GGAbuffer[inx];
    i++;
    inx++;
    }
    num = atoi(buffer); // convert buffer to the number. It will only convert upto decimal
    j = 0;
    while(buffer[j] != '.') j++;
    j++;
    declen = strlen(buffer) - j;
    dec = atoi((char*) buffer+j);
    lat = num/100.0 + (dec/pow(10,declen+2));
    gga->lcation.longtitude = lat;
    inx++;
    gga->lcation.EW= GGAbuffer[inx];
//===============================================
// Skip position fix
inx++;//',' afer EW
inx++; // position
inx++; // ',' afer position fix
// number of sattelites
inx++;
memset(buffer,'\0',12);
i=0;
while (GGAbuffer[inx] != ',') 
  { 
  buffer[i]= GGAbuffer[inx];
  inx++;
  i++;
  }
  gga->momofsat = atoi(buffer);
//==================================================
//skip HDOP
inx++;
while(GGAbuffer[inx] != ',') inx++;
//==================================================
// Altitute calculation
inx++;
memset(buffer,'\0',12);
i = 0;
while(GGAbuffer[inx] != ',')
  {
    buffer[i] = GGAbuffer[inx];
    i++;
    inx++;
  }
  num = atoi(buffer);
  j = 0;
 while(buffer[j] != '.') j++;
 j++;
 declen   = strlen(buffer)-j;
 dec      = atoi((char*) buffer +j);
 lat      = num + (dec/pow(10,declen));
 gga->alt.altitude = lat;
 inx++;
 gga->alt.unit  = GGAbuffer[inx];
 return 0;
}

// ============ DecodeRMC
//$GPRMC,150925.00,A,1021.77768,N,10623.03480,E,0.314,,050223,,,A*78
// Here 'A' Indicates the data is valid, and 'V' indicates invalid data
int decodeRMC ( char *RMCbuffer, RMCSTRUCT *rmc)
{
  int inx = 0;
  int i   = 0;
  char buffer[12];
  while (RMCbuffer[inx] != ',') inx++;
  inx++;
  while( RMCbuffer[inx] != ',') inx++;
  inx++;
  if( RMCbuffer[inx] == 'A')
    {
      rmc->isValid = 1;
    }else{
      rmc->isValid = 0;
      return 1;
    }
  inx++;
  inx++;
  while( RMCbuffer[inx] != ',') inx++;
  inx++;
  while( RMCbuffer[inx] != ',') inx++;
  inx++;
  while( RMCbuffer[inx] != ',') inx++;
  inx++;
  while( RMCbuffer[inx] != ',') inx++;// E
  inx++; // ',' after E
  // Get Speed
  memset(buffer,'\0', 12);
  i     = 0;
  int j = 0;
  while(RMCbuffer[inx] != ',')
    {
      buffer[i] = RMCbuffer[inx];
      i++;
      inx++;
    }
   if(strlen(buffer)>0)
    {
    uint8_t num = atoi(buffer);
    j=0;
    while(buffer[j] != '.') j++;
    j++;
    int declen  = strlen(buffer) - j;
    int dec     = atoi((char*)buffer+j);
    float lat   = num + (dec/pow(10, declen)); //Ground speed; 0.356knot (1knot =1 nautical mile per hour， which is equivalent to 0.5m per second)
    rmc->speed  = lat*0.5; // m/s 
    } else{
    rmc->speed = 0;
    }

   // Get Course
   inx++;
   i=0;
   memset(buffer, '\0',12);
   while(RMCbuffer[inx] != ',')
    {
    buffer[i] = RMCbuffer[inx];
    i++;
    inx++;
    }
    if(strlen(buffer)>0)// if the course have some data
    {
      uint16_t num = atoi(buffer);
      j = 0;
      while(buffer[j] != '.') j++;
      j++;
      int declen  = strlen(buffer) - j;
      int dec     = atoi((char*)buffer +j);
      float c     = num + (dec/pow(10, declen));
      rmc->course = c;

    }else{
      rmc->course= 0;
    }
 // Get Date
 inx++;
 memset(buffer,'\0',12);
 i = 0;
 while(RMCbuffer[inx]!= ',')
  {
    buffer[i] = RMCbuffer[inx];
    i++;
    inx++;
  }
  day   = atoi(buffer)/10000;
  month = (atoi(buffer)/100)%100;
  year  = atoi(buffer)%100;
  day   = day + daychange;
  rmc->date.Day   = day;
  rmc->date.Mon   = month;
  rmc->date.Year  = year;
  return 0;

}

void uart_GPS_err_handle(app_uart_evt_t *p_event){

 switch(p_event->evt_type){ 
    case (APP_UART_COMMUNICATION_ERROR):
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    
    break;
    }
    case (APP_UART_FIFO_ERROR):
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    break;
    }
    case APP_UART_DATA_READY:
     {
      app_uart_get(&t);
      RingBufferPut(t);
      printf("%c", t);
     break;
     }
     default:
     {
      break;
     }
    }     
}

 void gps_init()
{
  ret_code_t err_code;
  app_uart_comm_params_t comm_params ={
  RX_PIN,
  TX_PIN,
  RTS_PIN,
  CTS_PIN,
  UART_HWFC,
  false,
  NRF_UART_BAUDRATE_9600
  };
APP_UART_FIFO_INIT(&comm_params,UART_RX_GPS_BUFF_SIZE,UART_TX_GPS_BUFF_SIZE,uart_GPS_err_handle,APP_IRQ_PRIORITY_LOWEST,err_code);
APP_ERROR_CHECK(err_code);
}

void gps_get()
{
    if(Wait_for("GGA") == 1)
          {
            Copy_upto("*",gga_data);
            if(decodeGGA(gga_data, &gpsData.ggastruct) == 0) FlagGGA = 2;
            else FlagGGA = 1;
          }
          nrf_delay_ms(5000);

    if(Wait_for("RMC")==1)
      {
            Copy_upto("*",rmc_data);
            if(decodeRMC(rmc_data,&gpsData.rmcstruct) == 0 ) FlagRMC = 2;
            else FlagRMC = 1;
      }
          nrf_delay_ms(5000);
}