#ifndef  BLE_CUS_C_H
#define BLE_CUS_C_H
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ble.h"
#include "ble_db_discovery.h"
#include "ble_srv_common.h"
#include "nrf_ble_gq.h"
#include "nrf_sdh_ble.h"
#include "sdk_common.h"


//Service UUID

#define BLE_CUS_C_SERVICE_UUID  BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE
// Characteristic UUID
#define BLE_CUS_C_CHAR_UUID    BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR

#define BLE_CUS_C_DEF(_name) \
        static ble_cus_c_t  _name; \
        NRF_SDH_BLE_OBSERVER(_name ## _obs, \
                             BLE_HRS_C_BLE_OBSERVER_PRIO, \  
                             ble_cus_c_on_ble_evt, &_name)    
#define BLE_CUSS_C_DEF(_name, _cnt)          \
        static ble_cus_c_t _name[_cnt];      \
        NRF_SDH_BLE_OBSERVERS(_name ## _obs,   \
                             BLE_HRS_C_BLE_OBSERVER_PRIO,          \
                            ble_cus_c_on_ble_evt,&_name,_cnt)         
typedef enum{                             
  BLE_CUS_C_DISCOVERY_COMPLETED,
  BLE_CUS_C_NOTIFICATION,
  BLE_CUS_C_DISCONNECTED,
  BLE_CUS_C_CONNECTED
} ble_cus_c_evt_type_t;
typedef struct
{
  uint8_t   tmp_value;
  uint8_t   sleep_intervals_cnt;
  uint16_t  sleep_intervals[20];
}ble_tmp_t;

typedef  struct
{
  uint16_t temp_cccd_handle;
  uint16_t temp_handle;
} tmp_db_t;

typedef  struct
{
  ble_cus_c_evt_type_t      evt_type;
  uint16_t                  conn_handle;
  union{
    ble_tmp_t   tmp;
    tmp_db_t    peer_db;
  }params;
} ble_cus_c_evt_t;

typedef struct ble_cus_c_s ble_cus_c_t;
typedef void (* ble_cus_c_evt_handler_t) (ble_cus_c_t *p_cus, ble_cus_c_evt_t *p_cus_evt);

struct ble_cus_c_s{
     uint16_t       conn_handle;
     tmp_db_t       peer_tmp_db;
     ble_cus_c_evt_handler_t      evt_handler;
     ble_srv_error_handler_t      error_handler;

     nrf_ble_gq_t                 *p_gatt_queue;
};

typedef struct{
  ble_cus_c_evt_handler_t   evt_handler;
  ble_srv_error_handler_t   error_handler;
  nrf_ble_gq_t              *p_gatt_queue;
  
}ble_cus_c_init_t;
uint32_t ble_cus_c_init(ble_cus_c_t *p_cus, ble_cus_c_init_t *p_init);
void ble_cus_c_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);      

uint32_t ble_cus_c_notif_enable(ble_cus_c_t *p_ble_cus_c);
void ble_cus_on_db_disc_evt(ble_cus_c_t *p_ble_cus_c, const ble_db_discovery_evt_t *p_evt);

uint32_t ble_cus_c_handle_assign(ble_cus_c_t *p_ble_cus_c, uint16_t conn_handle, const tmp_db_t *p_peer_tmp_handles);
#endif