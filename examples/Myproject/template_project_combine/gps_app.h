#ifndef  GPS_APP_H
#define  GPS_APP_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "nrf_delay.h"
#include "nrf_ringbuf.h"
#include "ringuart.h"


#define GPS_BUFFER                      256
#define UART_TX_GPS_BUFF_SIZE           128
#define UART_RX_GPS_BUFF_SIZE           128
#define RX_PIN  8
#define TX_PIN  6
#define CTS_PIN 7
#define RTS_PIN 5
#define UART_HWFC                       APP_UART_FLOW_CONTROL_DISABLED

#define  sizebuff                       256

typedef struct{
  int hour;
  int min;
  int sec;
  } TIME;

typedef struct{
  float latitude;
  char  NS;
  float longtitude;
  char  EW;
  } LOCATION;

typedef struct{
  float altitude;
  char  unit;
  } ALTITUDE;

typedef struct {
  int Day;
  int Mon;
  int Year;
  } DATE;

typedef  struct{
  LOCATION lcation;
  TIME     tim;
  int      isfixValid;
  ALTITUDE alt;
  int      momofsat;
  } GGASTRUCT;
  
 typedef struct {
  DATE  date;
  float speed;
  float course;
  int   isValid;
  } RMCSTRUCT;
  
  typedef struct {
  GGASTRUCT ggastruct;
  RMCSTRUCT rmcstruct ;
  } GPSSTRUCT;

extern char      gga_data[128];
extern char      rmc_data[128];
extern GPSSTRUCT gpsData;

extern uint8_t   buffer_gps[GPS_BUFFER];
extern uint8_t   t;
extern int       FlagGGA;
extern int       FlagRMC;


int decodeGGA (char *GGAbuffer, GGASTRUCT *gga);
int decodeRMC ( char *RMCbuffer, RMCSTRUCT *rmc);
 
void  gps_init();
extern void  gps_get();
#endif

/*
  uart_init();
  RingBufferInit();
  // Do task
  while (true)
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

*/