/*
    APP_GPS.C
    minh nhat
    Usage:
    add: GPS_t gga_data;
         GPS_t rmc_data;
         decodeRMC(..........., &rmc_data.rmcstruct);
         decodeGGA(..........., &gga_data.ggastruct);
*/
#include "app_gps.h"

int hr = 0, min = 0, sec = 0, mon = 0, day = 0, yr = 0; 
int GMT = +700;// fix time
int daychange = 0;


//$GPGGA,164011.00,1021.77720,N,10623.02866,E,1,04,4.41,21.5,M,-2.7,M,,*7F
int decodeGGA(char *GGAbuffer, GGA_t *gga)
{   char buffer[20];
    int i=0;
    int idx = 0;
    // Check data
    while(GGAbuffer[idx] != ',') idx++;
    idx++; // the position is /$GPGGA,
    while(GGAbuffer[idx] != ',') idx++;
    idx++;
    while(GGAbuffer[idx] != ',') idx++;
    idx++;
    while(GGAbuffer[idx] != ',') idx++;
    idx++;
    while(GGAbuffer[idx] != ',') idx++;
    idx++;
    while(GGAbuffer[idx] != ',') idx++;
    idx++; // Position is 'E,'

    if((GGAbuffer[idx] == '1') || (GGAbuffer[idx] == '2') || (GGAbuffer[idx] == '6'))
        {
            gga->isfixValid == 1;
            idx = 0;
        }else{
            gga->isfixValid = 0;
            return 1; // Data cant not be receive, Error
        }
    //=== Get Time========
    while(GGAbuffer[idx] != ',') idx++;
    idx++; // the position is /$GPGGA, 

    memset(buffer,'\0',20);
    i = 0;
    while(GGAbuffer[idx] != ','){
        buffer[i] = GGAbuffer[idx];
        idx++;
        i++;
    }   
    hr = atoi(buffer)/10000 + GMT/100;
    min = (atoi(buffer)/100)%100 + GMT%100;
    sec = (atoi(buffer))%100;
    if(min > 59)
        {
            min = min - 60;
            hr++;
        }
    if( hr < 0 )
        {
            hr= 24+hr;
            daychange = -1;;
        }
    if(hr >= 24 )
        {
            hr = hr -24;
            daychange = +1;
        }
        
    gga->time.Hour= hr;
    gga->time.Minute = min;
    gga->time.Second = sec;
    //=====Get Latitude=============
    idx++;
    memset(buffer,'\0',20);
    i=0;
    while(GGAbuffer[idx] != ','){
        buffer[i] = GGAbuffer[idx];
        idx++;
        i++;
    }
    if(strlen(buffer) < 6) return 2;
    int j=0;
    while(buffer[j] != '.') j++;
    j++;
    uint16_t num = atoi(buffer);// convert buffer to the number. It will only convert upto decimal
    int declen = atoi(buffer) - j; // Decnumber length
    int dec = atoi((char*)buffer+j);
    float lat = (num/100.0) +  (dec/pow(10, declen+ 2 ));
    
    gga->lcation.latitude = lat;
    idx++;
    gga->lcation.NS = GGAbuffer[idx]; // GET NS

    //============== Get Longtitude=====================
    idx++;
    idx++;
    memset(buffer,'\0', 20);
    i = 0;
    while(GGAbuffer[idx] != ',')
        {
            buffer[i] = GGAbuffer[idx];
            idx++;
            i++;
        }
    num = atoi(buffer); // convert buffer to the number. It will only convert upto decimal
    j = 0;
    while(buffer[j] != '.') j++;
    j++;

    declen = strlen(buffer) - j;
    dec = atoi((char*)buffer+j);
    float lon = (num/100.0) + (dec/pow(10, declen + 2));
    
    gga->lcation.longtitude = lon;
    idx++;
    gga->lcation.EW= GGAbuffer[idx];
    // Skip position fix
    idx++;//',' afer EW
    idx++; // position
    idx++; // ',' afer position fix
    // number of sattelites
    idx++;
    memset(buffer,'\0',20);
    i=0;
    while (GGAbuffer[idx] != ',') 
        { 
            buffer[i]= GGAbuffer[idx];
            idx++;
            i++;
        }
    gga->mumofsat = atoi(buffer);
//==================================================
    //skip HDOP
    idx++;
    while(GGAbuffer[idx] != ',') idx++;
//==================================================
// Altitute calculation
    idx++;
    memset(buffer,'\0',20);
    i = 0;
    while(GGAbuffer[idx] != ',')
        {
            buffer[i] = GGAbuffer[idx];
            idx++;
            i++;
        }
    num = atoi(buffer);
    j = 0 ;
    while (buffer[j] != '.') j++;
    j++;
    declen = strlen(buffer) - j;
    dec = atoi((char*) buffer + j );
    float al = num + (dec/pow(10,declen));
    gga->alt.altitude = al;
    idx++;
    gga->alt.unit = GGAbuffer[idx];
    return 0;
}

//$GPRMC,164012.00, A ,1021.77822,N,10623.02861,E, 1.585 , ,110223,,,A*7B
int decodeRMC(char *RMCbuffer, RMC_t *rmc )
{   
    int idx = 0;
    int i = 0;
    char buffer[20];
    int j = 0;
    while(RMCbuffer[idx] != ',') idx++;
    idx++;
    while(RMCbuffer[idx] != ',') idx++;
    idx++;

    if( RMCbuffer[idx] == 'A')
        {
            rmc->isValid = 1;
        }   else{
            rmc->isValid = 0;
            return 1; // Data is not fix, dont connect to gps
        }
        idx++;
        idx++;
    //========= Get Speed==================
    while (RMCbuffer[idx] != ',') idx++;
    idx++; // 1021.77822,
    while (RMCbuffer[idx] != ',') idx++;
    idx++; //N,
    while (RMCbuffer[idx] != ',') idx++;
    idx++; //10623.02861,
    while (RMCbuffer[idx] != ',') idx++;
    idx++; // E,
    memset(buffer,'\0', 20);
    i=0;
    while(RMCbuffer[idx] != ',')
        {
            buffer[i]= RMCbuffer[idx];
            i++;
            idx++;            
        }
    if( strlen(buffer)>0)
        {
            uint8_t num = atoi(buffer);
            j = 0;
            while(buffer[j]!= '.') j++;
            j++;
            int declen = strlen(buffer) - j;
            int dec    = atoi((char*)buffer + j);
            float spd = num + dec/pow(10,declen);
            //Ground speed; 0.356knot (1knot =1 nautical mile per hour，
            //which is equivalent to 0.5m per second)
            rmc->speed = spd*0.5;// m/s

        }else{
            rmc->speed = 0;
        }
    //========Get Course
    idx++;
    memset(buffer,'\0',20);
    i=0;
    while (RMCbuffer[idx] != ',')
        {
            buffer[i] = RMCbuffer[idx];
            idx++;
            i++;
        }
    
    if(strlen(buffer)>0)
        {   uint16_t num = atoi(buffer);
            j = 0;
            while(buffer[j] != '.') j++;
            j++;
            int declen = strlen(buffer) - j;
            int dec = atoi((char*)buffer + j);
            float cr = num + dec/pow(10,declen);
            rmc->course= cr;
        }else{
            rmc->course = 0;
        }
    //=====Get Date===========
    //110223
    idx++;
    memset(buffer,'\0', 20);
    i = 0;
    while(RMCbuffer[idx] != ',')
        {
            buffer[i]= RMCbuffer[idx];
            idx++;
            i++;
        }
    day = atoi(buffer)/10000;
    mon = (atoi(buffer)/100)%100;
    yr = atoi(buffer)%100;
    rmc->Date.Day = day + daychange;
    rmc->Date.Month = mon;
    rmc->Date.Year = yr;
    return 0;
}

/*
GPS_t gga_data;
GPS_t rmc_data;
uint8_t buff_uart[]= "$GPGGA,173930.00,1021.77371,N,10623.02977,E,1,05,3.21,5.7,M,-2.7,M,,*46";
uinr8_t bufferRMC[]="$GPRMC,151040.00,A,1021.77715,N,10623.03305,E,0.125,,050223,,,A*73";
int main(){
    decodeGGA(buff_uart, &gga_data.ggastruct);
    printf("Hour: %2d, Min: %2d, Sec: %2d", gga_data.ggastruct.time.Hour, gga_data.ggastruct.time.Minute, gga_data.ggastruct.time.Second);
    printf("\nLatitude: %f %c", gga_data.ggastruct.lcation.latitude,gga_data.ggastruct.lcation.EW);
    printf("\nLongtitude: %f %c", gga_data.ggastruct.lcation.longtitude, gga_data.ggastruct.lcation.NS);
    printf("\nFix: %d", gga_data.ggastruct.isfixValid);
    printf("\nAltitude: %f, %c", gga_data.ggastruct.alt.altitude, gga_data.ggastruct.alt.unit);

    printf("\n=================================");
    decodeRMC(bufferRMC, &rmc_data.rmcstruct);
    printf("\n Speed: %f",rmc_data.rmcstruct.speed);
    printf("\n IsValid: %d", rmc_data.rmcstruct.isValid);
    printf("\n Coure: %f", rmc_data.rmcstruct.course);
    printf("\nDay: %2d, Mon: %2d, Year: %2d", rmc_data.rmcstruct.Date.Day, rmc_data.rmcstruct.Date.Month, rmc_data.rmcstruct.Date.Year);
}
*/