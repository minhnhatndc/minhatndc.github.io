#ifndef  BLE_GPS_H
#define  BLE_GPS_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "app_gps.h"
#include "nrf_log.h"
#define BLE_GPS_BASE_UUID  {{0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0x00, 0xAD, 0x64, 0xF3}}

#define  BLE_GPS_SERVICE_UUID 0x1801
#define  BLE_GPS_TX_SERVICE_UUID 0x1802

#define BLE_GPS_DEF(_name)     \
        static ble_gps_t _name; \

typedef  struct {
    GPS_t gps_value;
    ble_srv_cccd_security_mode_t gps_value_char_attr_md;
}ble_gps_init_t ;

struct ble_gps_s 
{
  uint16_t    service_handler;
  ble_gatts_char_handles_t gps_value_handles;
  uint16_t     conn_handle;
  uint8_t       uuid_type;
};

typedef  struct ble_gps_s ble_gps_t;

uint32_t ble_gps_init(ble_gps_t *p_gps, ble_gps_init_t *p_gps_init);
 

#endif