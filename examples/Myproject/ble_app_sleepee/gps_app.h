#ifndef  GPS_APP
#define  GPS_APP

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "ringuart.h"

#define GPS_BUFFER 256



typedef struct{
  int hour;
  int min;
  int sec;
  } TIME;

typedef struct{
  float latitude;
  char NS;
  float longtitude;
  char EW;
  } LOCATION;

typedef struct{
  float altitude;
  char unit;
  } ALTITUDE;
typedef struct {
  int Day;
  int Mon;
  int Year;
  } DATE;
typedef  struct{
  LOCATION lcation;
  TIME tim;
  int isfixValid;
  ALTITUDE alt;
  int momofsat;
  } GGASTRUCT;
  
 typedef struct {
  DATE date;
  float speed;
  float course;
  int isValid;
  } RMCSTRUCT;
  
  typedef struct {
  GGASTRUCT ggastruct;
  RMCSTRUCT rmcstruct ;
  } GPSSTRUCT;

 int decodeGGA (char *GGAbuffer, GGASTRUCT *gga);
 int decodeRMC ( char *RMCbuffer, RMCSTRUCT *rmc);

#endif
