#ifndef APP_GPS_H
#define APP_GPS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "string.h"
#include "math.h"

#define GPS_BUFFER 256U 

typedef enum{
    Data_Not_Avalable = 0,
    Data_Avalable = 1,
} data_t;

typedef struct{
    int Day;
    int Month;
    int Year;
} Date_t;

typedef struct{
    int Hour;
    int Minute;
    int Second;
} Time_t;

typedef struct{
    float latitude;
    char NS;
    float longtitude;
    char EW;
}Location_t;

typedef struct{
    float altitude;
    char unit;
}Altitude_t;

typedef struct{
    Location_t lcation;
    Time_t time;
    int isfixValid;
    Altitude_t alt;
    int mumofsat;
} GGA_t;

typedef struct {
    Date_t Date;
    float speed;
    float course;
    int isValid;
} RMC_t;

typedef struct {
    GGA_t ggastruct;
    RMC_t rmcstruct;
}GPS_t;

//$GPGGA,164011.00,1021.77720,N,10623.02866,E,1,04,4.41,21.5,M,-2.7,M,,*7F
int decodeGGA(char *GGAbuffer, GGA_t *gga);
//$GPRMC,164012.00,A,1021.77822,N,10623.02861,E,1.585,,110223,,,A*7B
int decodeRMC(char *RMCbuffer, RMC_t *rmc );

    /* data */




#endif