#ifndef   BLE_APP_TEMP_H
#define   BLE_APP_TEMP_H
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
//Service UUID
#define BLE_TEMP_SERVICE_UUID       BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE
//Characteristic UUID
#define BLE_TEMP_CHAR_UUID          BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR

#define OPCODE_LENGTH 1
#define HANDLE_LENGTH 2
#define MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)

/**@brief   Macro for defining a ble_cus instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_TEMP_DEF(_name)     \
        static ble_temp_t _name;  \
        NRF_SDH_BLE_OBSERVER(_name ## _obs,     \
                          BLE_HRS_BLE_OBSERVER_PRIO,    \
                          ble_temp_on_ble_evt,&_name)
 
typedef enum{
  BLE_TEMP_CONNECTED,
  BLE_TEMP_DISCONTED,
  BLE_TEMP_NOTIFICATION_ENABLED,
  BLE_TEMP_NOTIFICATION_DISABLED
} ble_temp_evt_type_t;

typedef  struct{

  ble_temp_evt_type_t evt_type;
} ble_temp_evt_t;
typedef struct ble_temp_s ble_temp_t;
typedef void (* ble_tmp_evt_handler_t) ( ble_temp_t *p_ble_tmp, ble_temp_evt_t *p_evt);
/**@brief Custom Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
 typedef  struct{
      uint16_t     tmp_value;
      ble_tmp_evt_handler_t     evt_handler;
 }ble_temp_init_t;


 
/**@brief Custom Service structure. This contains various status information for the service. */ 
struct ble_temp_s{
    uint8_t       uuid_type;
    uint16_t      conn_handle;
    uint16_t      service_handle;
    ble_tmp_evt_handler_t   evt_handler;

    ble_gatts_char_handles_t    tmp_value_handle;
};
typedef struct ble_temp_s ble_temp_t;
typedef void (* ble_tmp_evt_handler_t) ( ble_temp_t *p_ble_tmp, ble_temp_evt_t *p_evt);

uint32_t ble_temp_init(ble_temp_t *p_tmp, ble_temp_init_t *p_init);
void ble_temp_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);
uint32_t ble_temp_value_update(ble_temp_t *p_tmp, uint8_t value);  
#endif