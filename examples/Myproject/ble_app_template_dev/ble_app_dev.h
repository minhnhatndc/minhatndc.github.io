#ifndef  BLE_APP_DEV_H
#define  BLE_APP_DEV_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "nrf_log.h"
//Define Service UUID
#define  BLE_APP_SERVICE_UUID           BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE
//Define Characteristics UUID
#define BLE_APP_SLEEP_CHAR_UUID         BLE_UUID_MEASUREMENT_INTERVAL_CHAR
#define BLE_APP_HEART_RATE_CHAR_UUID    BLE_UUID_HEART_RATE_MEASUREMENT_CHAR
#define BLE_APP_RR_RATE_CHAR_UUID       0x1401

#define OPCODE_LENGTH 1
#define HANDLE_LENGTH 2
#define MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)

#define BLE_APP_DEF(_name)      \
        static ble_app_t _name;  \
        NRF_SDH_BLE_OBSERVER(_name ## _obs,     \
                            BLE_HRS_BLE_OBSERVER_PRIO,    \
                            ble_app_on_ble_evt, &_name)
typedef  enum{
  BLE_APP_NOTIFICATION_ENABLED,
  BLE_APP_NOTIFICATION_DISABLED
} ble_app_evt_type_t;
typedef  struct{
    ble_app_evt_type_t  evt_type;
} ble_app_evt_t;

typedef struct ble_app_s ble_app_t; 
typedef  void (* ble_app_evt_handler_t) (ble_app_t *p_app, ble_app_evt_t *p_evt);
 
typedef  struct
 {
  uint8_t  init_sleep_value;
  ble_app_evt_handler_t   evt_handler;
 } ble_app_init_t;
 struct ble_app_s {
      uint8_t           uuid_type;
      uint16_t          conn_handle;
      uint16_t          service_handle;
      ble_app_evt_handler_t       evt_handler;
      ble_gatts_char_handles_t    sleep_value_handle;
      ble_gatts_char_handles_t    hrs_value_handles;/**< Handles related to the Custom Value characteristic. */
      ble_gatts_char_handles_t    rr_value_handles;
      ble_gatts_char_handles_t    temp_value_handles;
 
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
 uint32_t ble_app_init(ble_app_t *p_app, ble_app_init_t *p_init);
/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
void ble_app_on_ble_evt(ble_evt_t const *p_evt, void *p_context);
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
uint32_t ble_hrs_value_update(ble_app_t *p_app, uint8_t value);

#endif