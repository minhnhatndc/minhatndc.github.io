#ifndef BLE_NUS_DATA_H
#define BLE_NUS_DATA_H
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "sdk_config.h"
#include "ble_link_ctx_manager.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"


#define NUS_DATA_SERVICE_UUID_BASE {{0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0xC9, 0xAD, 0x64, 0xF3}}
// Service & characteristics UUIDs
#define BLE_NUS_DATA_SERVICE_UUID    0x1400
//#define BLE_NUS_DATA_VALUE_CHAR_UUID 0x1401

#define OPCODE_LENGTH  1
#define HANDLE_LENGTH  2

/**@brief   Macro for defining a ble_cus instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */

#define BLE_NUS_DATA_DEF(_name, _nus_data_max_clients)                  \
    BLE_LINK_CTX_MANAGER_DEF(CONCAT_2(_name, _link_ctx_storage),        \
                            (_nus_data_max_clients),                    \
                            sizeof(ble_nus_data_client_context_t));     \
    static ble_nus_data_t _name =                                       \
        {                                                               \
            .p_link_ctx_storage = &CONCAT_2(_name, _link_ctx_storage)   \
        };                                                              \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,                                 \
                        BLE_NUS_BLE_OBSERVER_PRIO,                      \
                        ble_nus_data_on_ble_evt,                        \
                        &_name)
/**@brief   Maximum length of data (in bytes) that can be transmitted to the peer by the Nordic UART service module. */
#if defined(NRF_SDH_BLE_GAP_EVENT_LENGTH) && (NRF_SDH_BLE_GATT_MAX_MTU_SIZE != 0)
    #define BLE_NUS_DATA_MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE- OPCODE_LENGTH - HANDLE_LENGTH)
#else  
    #define BLE_NUS_DATA_MAX_DATA_LEN (BLE_GATT_MTU_SIZE_DEFAULT - OPCODE_LENGTH - HANDLE_LENGTH)
    #warning BLE_NUS_DATA_MAX_DATA_LEN is not defined.
#endif


// Service evt type
typedef enum {
    BLE_NUS_DATA_EVT_RX_DATA, // data received
    BLE_NUS_DATA_EVT_TX_RDY, // Service is ready to accept new data to be transmitted
    BLE_NUS_DATA_EVT_COMM_STARTED, // Notification has been enabled
    BLE_NUS_DATA_EVT_COMM_STOPPED, // Notification has been disabled
} ble_nus_data_evt_type_t;

typedef struct ble_nus_data_s ble_nus_data_t;

typedef struct {
    uint8_t const *p_data; /**< A pointer to the buffer with received data. */
    uint16_t length;
} ble_nus_data_evt_rx_data_t;

typedef struct {
    bool is_notification_enabled;
} ble_nus_data_client_context_t;

typedef struct {
    ble_nus_data_evt_type_t type;
    ble_nus_data_t          *p_nus_data;
    uint16_t                 conn_handle;
    ble_nus_data_client_context_t   *p_link_ctx;
    union 
    {
        /* data */
        ble_nus_data_evt_rx_data_t rx_data;
    } params;
    
} ble_nus_data_evt_t;

typedef void (*ble_nus_data_handler_t) (ble_nus_data_evt_t *p_evt);

typedef struct {
    ble_nus_data_handler_t data_handler;
} ble_nus_data_init_t;
// This structure contains status information related to the service.
struct ble_nus_data_s 
{
    uint8_t     uuid_type;
    uint16_t    service_handler;
    ble_gatts_char_handles_t tx_handles;
    ble_gatts_char_handles_t rx_handles;
    blcm_link_ctx_storage_t *const p_link_ctx_storage;
    ble_nus_data_handler_t  data_handler;
};

// init service
uint32_t ble_nus_data_init(ble_nus_data_t *p_nus, ble_nus_data_init_t const *p_nus_init);// handling service
void ble_nus_data_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);
// sending data to the peer
uint32_t ble_nus_data_cus_send(ble_nus_data_t *p_nus, uint8_t *p_data, uint16_t *p_length, uint16_t conn_handle);

#endif