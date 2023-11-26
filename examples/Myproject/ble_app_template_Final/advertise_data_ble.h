#ifndef ADVERTISE_DATA_BLE_H
#define ADVERTISE_DATA_BLE_H
#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

//Random UUID 128-bit fb2cc9b0-7e53-11ee-b962-0242ac120002
#define ADVERTISE_CUSTOM_SERVICE_UUID_BASE {0x02, 0x00,0x12, 0xAC, 0x42, 0x02, 0x62, 0xB9, \
                                            0xEE, 0x11, 0x53, 0x7E, 0xB0, 0xC9, 0x2C, 0xF0 }



#define CUS_AVTERTISE_SERVICE_UUID                BLE_UUID_LOCATION_AND_NAVIGATION_SERVICE 
#define CUSTOM_TEMPHUMID_VALUE_CHAR_UUID          BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR 
#define CUSTOM_GPS_VALUE_CHAR_UUID                BLE_UUID_LN_POSITION_QUALITY_CHAR


#endif