#ifndef  BLE_CUSTOM_DEV_H
#define  BLE_CUSTOM_DEV_H
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"

#define BLE_MAX_BUFFER_INTERVAL      20
#define OPCODE_LENGTH 1
#define HANDLE_LENGTH 2
#define MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)

//Sensor location
#define BLE_BODY_SERSOR_LOCATION_OTHER   0
#define BLE_BODY_SENSOR_LOCATION_CHEST   1
#define BLE_BODY_SENSOR_LOCATION_WRIST   2                    
#define FLAG_MASK_VALUE_16BITS            (0x01 << 0)
#define FLAG_MASK_SENSOR_DETECTED         (0x01 << 1)
#define FLAG_MASK_SENSOR_SUPPORTED        (0x01 << 2)
#define FLAG_MASK_ENERGY_INCLUDED         (0x01 << 3)
#define FLAG_MASK_SLEEP_INTERVAL_INCLUDED (0x01 << 4)
#define INITIAL_VALUE  0
//============================================================
#define CUSTOM_SERVICE_128BITS_UUID_BASE {{0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0xC9, 0xAD, 0x64, 0xF3}}

#define BLE_CUS_DEF(_name)                    \
        static ble_cus_t        _name;         \
       // NRF_SDH_BLE_OBSERVER( _name ## _obs,    \
         //                     BLE_HRS_BLE_OBSERVER_PRIO,  \
           //                   ble_cus_on_ble_evt, &_name)

//Service UUID
#define BLE_CUS_SERVICE_UUID      BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE
//Characteristic UUID
#define BLE_HRS_CHAR_UUID         BLE_UUID_HEART_RATE_MEASUREMENT_CHAR
#define BLE_TMP_CHAR_UUID         BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR

typedef struct
{
  uint8_t                           tmp_value;
  uint8_t                          *p_sensor_location;
  bool                              is_sensor_supported;
  security_req_t                    cccd_wr_sec;
  security_req_t                    rd_sec;
}ble_cus_init_t;

typedef  struct ble_cus_s  ble_cus_t;
 
struct ble_cus_s{
    uint16_t                         conn_handle;
    uint16_t                         service_handle;
    uint8_t                          uuid_type;

    bool                             is_sensor_supported;
    bool                             is_sensor_detected;
    bool                             is_expended_energy_supported;

    ble_gatts_char_handles_t         temp_value_handle;
    ble_gatts_char_handles_t         sleep_value_handle;
    ble_gatts_char_handles_t         bsl_handle;

    uint16_t                         sleep_interval[BLE_MAX_BUFFER_INTERVAL];
    uint16_t                         sleep_interval_count;
    uint8_t                          max_tmp_len;
};
/**@brief Function for initializing the Custom Service.
 *
 * @param[out]  p_cus       Custom Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_cus_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
 uint32_t ble_cus_init(ble_cus_t *p_cus, ble_cus_init_t *p_init);
#endif