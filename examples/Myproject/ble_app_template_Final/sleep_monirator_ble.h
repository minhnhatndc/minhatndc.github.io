#ifndef SLEEP_MONIRATOR_BLE_H
#define SLEEP_MONIRATOR_BLE_H
#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

//Random UUID 128-bit f0e90c32-7e50-11ee-b962-0242ac120002
#define MAX_BUFFER_INTERVALS      20
#define MAX_INTERVALS             20
#define OPCODE_LENGTH             1
#define HANDLE_LENGTH             2

#define MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)
                                        


#define SLEEP_SERVICE_UUID                    0x1400//BLE_UUID_HEART_RATE_SERVICE
#define CUSTOM_SLEEP_VALUE_CHAR_UUID          0x1401
#define CUSTOM_TIME_SLEEP_VALUE_CHAR_UUID     BLE_UUID_DAY_DATE_TIME_CHAR

#define BLE_CUS_SLEEP_DEF(_name)                                                                          \
        static ble_sleep_t _name;                                                                         \
        NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                               \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                           \
                     ble_sleep_on_evt, &_name)

typedef  enum{
  BLE_CUS_EVT_NOTIFICATION_ENABLED,                             /**< Custom value notification enabled event. */
  BLE_CUS_EVT_NOTIFICATION_DISABLED,
  BLE_CUS_EVT_CONNECTED,
  BLE_CUS_EVT_DISCONNECTED
} ble_sleep_evt_type_t;

typedef  struct{
  ble_sleep_evt_type_t  evt_type;

} ble_sleep_evt_t;

typedef struct ble_sleep_s ble_sleep_t;
typedef void (*ble_sleep_evt_handler_t)(ble_sleep_t *p_sleep, ble_sleep_evt_t *p_evt);

typedef  struct{
    uint8_t                       initial_sleep_value;
    ble_srv_cccd_security_mode_t  sleep_value_char_attr_md;
    ble_sleep_evt_handler_t       evt_handler; 
}ble_sleep_init_t;


struct ble_sleep_s
{
  uint16_t                      service_handle;     /**< Handle of Custom Service (as provided by the BLE stack). */
  ble_gatts_char_handles_t      sleep_value_handle; /**< Handles related to the Custom Value characteristic. */
  uint16_t                      conn_handle;        /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
  uint16_t                      uuid_type;
  ble_sleep_evt_handler_t       evt_handler;        /**< Event handler to be called for handling events in the Custom Service. */
};



uint32_t ble_sleep_init(ble_sleep_t *p_sleep, const ble_sleep_init_t *p_sleep_init);

/* This code belongs in ble_cus.h*/

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
 void ble_sleep_on_evt(ble_evt_t const *p_event, void *p_context);
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
 uint32_t ble_sleep_custom_value_update(ble_sleep_t * p_sleep, uint8_t custom_value);
#endif