#ifndef  BLE_SLEEP_H
#define BLE_SLEEP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ble.h"
#include "ble_srv_common.h"
#define OPCODE_LENGTH 1
#define HANDLE_LENGTH 2
#define MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)

#define SLEEP_SERVICE_BASE_UUID {{0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0x00, 0xAD, 0x64, 0xF3}}

#define SLEEP_SERVICE_UUID          BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE
#define SLEEP_MEASURE_VALUE_CHAR_UUID BLE_UUID_BLOOD_PRESSURE_MEASUREMENT_CHAR

/**@brief   Macro for defining a ble_cus instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
 #define BLE_SLEEP_DEF(_name)         \
          static ble_sleep_t _name;   \
          NRF_SDH_BLE_OBSERVER(_name ## _obs,       \
                        BLE_HRS_BLE_OBSERVER_PRIO, \
                        ble_sleep_on_ble_evt,&_name) 
 typedef  enum{
  BLE_SLEEP_EVT_DISCONNECTED,
  BLE_SLEEP_EVT_CONNECTED,
  BLE_CUS_EVT_NOTIFICATION_ENABLED,
  BLE_CUS_EVT_NOTIFICATION_DISABLED
 }ble_sleep_evt_type_t;

 typedef struct{
  ble_sleep_evt_type_t evt_type;
 }ble_sleep_evt_t;  

typedef struct ble_sleep_s ble_sleep_t;
typedef  void (*ble_sleep_evt_handler_t) (ble_sleep_t *p_sleep, ble_sleep_evt_t *p_evt);          
 typedef  struct 
 {
  uint8_t         sleep_value;
  ble_sleep_evt_handler_t         evt_handler;
  security_req_t  read_sec;
  ble_srv_cccd_security_mode_t sleep_value_char_attr_md;
 }ble_sleep_init_t;


 struct ble_sleep_s {
    uint8_t uuid_type;
    uint16_t service_handle;
    uint16_t conn_handle;
    ble_sleep_evt_handler_t evt_handler;
    ble_gatts_char_handles_t sleep_value_handles;
    ble_gatts_char_handles_t hrs_value_handles;
    ble_gatts_char_handles_t  rr_value_handles;
 };

 
 uint32_t ble_sleep_init(ble_sleep_t *p_sleep, ble_sleep_init_t *p_sleep_init);
  
/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
 void ble_sleep_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);
 /*
 Next, we're going to add the ble_cus_custom_value_update function decleration to the ble_cus.h file,
  which we're going to use to update our Custom Value Characteristic.
 */
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
 uint32_t ble_sleep_value_update(ble_sleep_t *p_sleep, uint8_t value);
#endif