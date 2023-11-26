#ifndef  BLE_APP_SLEEP_H
#define  BLE_APP_SLEEP_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "nrf_log.h"
#include "nrf_ble_gatt.h"


#define BLE_APP_SLEEP_SERVICE_UUID      BLE_UUID_HEALTH_THERMOMETER_SERVICE

#define BLE_APP_SLEEP_CHAR_UUID         BLE_UUID_HEART_RATE_MEASUREMENT_CHAR
#define BLE_APP_TEMPERATURE_CHAR_UUID   BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR

#define MAX_BUFFER_INTERVALS      20
#define MAX_INTERVALS 20
#define OPCODE_LENGTH 1
#define HANDLE_LENGTH 2

#define MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)
// Body Sensor Location values
#define BLE_BODY_SENSOR_LOCATION_OTHER      0
#define BLE_BODY_SENSOR_LOCATION_CHEST      1
#define BLE_BODY_SENSOR_LOCATION_WRIST      2
#define BLE_BODY_SENSOR_LOCATION_FINGER     3
#define BLE_BODY_SENSOR_LOCATION_HAND       4
#define BLE_BODY_SENSOR_LOCATION_EAR_LOBE   5
#define BLE_BODY_SENSOR_LOCATION_FOOT       6

#define FLAG_MASK_VALUE_16BIT                   (0x01 << 0)
#define FLAG_MASK_SENSOR_CONTACT_DETECTED       (0x01 << 1)
#define FLAG_MASK_SENSOR_CONTACT_SUPPORTED      (0x01 << 2)
#define FLAG_MASK_EXPENDED_ENERGY_INCLUDE       (0x01 << 3)
#define FLAG_MASK_SLEEP_INTERVAL_INCLUDED       (0x01 << 4)

typedef struct ble_sleep_s ble_sleep_t;
#define BLE_APP_SLEEP_DEF(_name)   \
        static ble_sleep_t _name; \
      
typedef struct{
  uint8_t             temp_value;
  bool                is_sensor_contact_supported;
  //uint8_t *         p_body_sensor_location;
  //security_req_t    temp_cccd_wr_sec;
  //security_req_t    bsl_rd_sec;
} ble_sleep_init_t;



struct ble_sleep_s{
  uint8_t           uuid_type;
  uint16_t          conn_handle;
  uint16_t          service_handle;
  //bool              is_expended_energy_supported;
  bool              is_sensor_temp_contact_supported;
  bool              is_sensor_temp_contact_detected;
  ble_gatts_char_handles_t  temp_value;
  ble_gatts_char_handles_t  sleep_handle;

  //ble_gatts_char_handles_t  bsl_handle;
  //ble_gatts_char_handles_t  hrco_handle;

  uint16_t                  sleep_interval[MAX_BUFFER_INTERVALS];
  uint16_t                  sleep_interval_count;
  uint8_t                   max_temp_len;
};

uint32_t ble_sleep_init(ble_sleep_t *p_sleep, const ble_sleep_init_t *p_init);
#endif
