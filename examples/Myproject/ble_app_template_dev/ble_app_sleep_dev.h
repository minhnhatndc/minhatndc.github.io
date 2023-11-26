#ifndef  BLE_APP_SLEEP_DEV_H
#define BLE_APP_SLEEP_DEV_H
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "nrf_ble_gatt.h"
#include "nrf_log.h"
#define BLE_UUID_PHYSICAL_ACTIVITY_MONITOR_SERVICE_UUID 0x183E
#define BLE_UUID_SLEEP_ACTIVITY_INSTANTANEOUS_DATA_CHAR 0x2B41
#define BLE_UUID_SLEEP_ACTIVITY_SUMMARY_DATA_CHAR       0x2B42

#define BLE_APP_SLEEP_DEV_SERVICE_UUID    BLE_UUID_PHYSICAL_ACTIVITY_MONITOR_SERVICE_UUID

#define BLE_APP_SLEEP_DEV_SLEEP_CHAR_UUID         BLE_UUID_SLEEP_ACTIVITY_INSTANTANEOUS_DATA_CHAR
#define BLE_APP_SLEEP_DEC_TEMPERATURE_CHAR_UUID   BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR

#define OPCODE_LENGTH 1
#define HANDLE_LENGTH 2
#define MAX_DATA_SIZE (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)
#define FIX_VALUE 0

#define FLAG_MASK_VALUE_TYPE_16BIT (0x01 << 0)
#define FLAG_MASK_SENSOR_SUPPORTED (0x01 << 1)
#define FLAG_MASK_SENSOR_DETECTED  (0x01 << 2)
#define FLAG_MASK_VALUE_TYPE_8BIT  (0x01 << 3)
#define FLAG_MASK_VALUE_INVALID    (0x01 << 4)

// Body Sensor Location values
#define BLE_BODY_SENSOR_LOCATION_OTHER      0
#define BLE_BODY_SENSOR_LOCATION_CHEST      1
#define BLE_BODY_SENSOR_LOCATION_WRIST      2
#define BLE_BODY_SENSOR_LOCATION_FINGER     3
#define BLE_BODY_SENSOR_LOCATION_HAND       4
#define BLE_BODY_SENSOR_LOCATION_EAR_LOBE   5
#define BLE_BODY_SENSOR_LOCATION_FOOT       6

#define BLE_DEV_DEF(_name)  \
        static ble_dev_t  _name;  \
        NRF_SDH_BLE_OBSERVER(_name ## _obs,   \
                            BLE_HRS_BLE_OBSERVER_PRIO,  \
                            ble_dev_on_ble_evt, &_name)

typedef enum
{
  BLE_DEV_SLEEP_EVT_CONNECTED,
  BLE_DEV_SLEEP_EVT_DISCONNECTED,
  BLE_DEV_SLEEP_EVT_NOTIFICATION_ENABLED,
  BLE_DEV_SLEEP_EVT_NOTIFICATION_DISENABLED
} ble_dev_evt_type_t;
typedef  struct
{
  ble_dev_evt_type_t evt_type;
} ble_dev_evt_t;

   

typedef  struct ble_dev_s ble_dev_t;
typedef void (*ble_dev_evt_handler_t)(ble_dev_t *p_dev, ble_dev_evt_t *p_evt);
typedef struct
{
  uint16_t     temp_value;
  uint16_t     sleep_value;
  ble_dev_evt_handler_t evt_handler;
  bool         is_sensor_supported;
}ble_dev_init_t;  
struct ble_dev_s{
  uint16_t     conn_handle; /**< Handle connection state*/
  uint16_t     service_handle; /**<handle service state*/
  uint8_t      uuid_type;     /**<type of uuid supply*/
  bool         is_sensor_supported; 
  ble_gatts_char_handles_t temp_handle; /**< Handles related to the Temperature Measurement characteristic.*/
  ble_gatts_char_handles_t sleep_handle; /**< Handles related to the Sleep Measurement characteristic.*/
  
  ble_dev_evt_handler_t    evt_handler;
};

uint32_t ble_dev_init(ble_dev_t *p_dev, ble_dev_init_t *p_init);
/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
void ble_dev_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);
/**@brief Function for updating the custom value.
 *
 * @details The application calls this function when the cutom value should be updated. If
 *          notification has been enabled, the custom value characteristic is sent to the client.
 *
 * @note 
 *       
 * @param[in]   p_cus          Custom Service structure.
 * @param[in]   Custom value 
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_cus_value_update(ble_dev_t *p_dev, uint8_t cus_value);
uint32_t ble_sleep_value_update(ble_dev_t *p_dev, uint16_t sleep_value);
uint32_t ble_temp_value_update(ble_dev_t  *p_dev, uint16_t temp_value);
#endif