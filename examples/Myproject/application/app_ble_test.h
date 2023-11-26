#ifndef APP_BLE_TEST_H
#define APP_BLE_TEST_H
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"


/*
@Def Implemeting the Custom Service
*/
#define BLE_APP_HRS_DEF(_name)      \
        static ble_heart_t _name;     \


// UUID Service
// #define BLE_UUID_HEART_RATE_SERVICE 0x180D

// ==============UUID Characteristics====================================

//#define BLE_UUID_DATE_TIME_CHAR                                  0x2A08     /**< Date Time characteristic UUID. */
//#define BLE_UUID_HEART_RATE_MEASUREMENT_CHAR                     0x2A37     /**< Heart Rate Measurement characteristic UUID. */
//#define BLE_UUID_DAY_DATE_TIME_CHAR                              0x2A0A     /**< Day Date Time characteristic UUID. */

//=======================================================================
#define BLE_MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - 3 )

typedef struct{
    bool is_notification_enable;
}ble_client_context_t;

typedef struct {
    uint8_t *p_data;
    uint16_t length;
} ble_evt_rx_data_t;

typedef enum{
    BLE_HEART_NOTIFICATION_ENABLE,
    BLE_HEART_NOTIFICATION_DISABLE,
    BLE_HEART_EVT_CONNECTED,
    BLE_HEART_EVT_DISCONNECTED,
    BLE_EVT_RX_DATA,
    BLE_EVT_TX_DATA,
    BLE_EVT_TIME_INIT,
    BLE_EVT_TIME_INIT_END
}ble_heart_evt_type_t;

typedef struct{
    ble_heart_evt_type_t evt_type;
    ble_heart_t *p_hrs;
    
}ble_heart_evt_t;

typedef void (* ble_heart_data_handler_t) (ble_heart_evt_t *p_evt);
typedef void (* ble_heart_evt_handler_t)  (ble_heart_evt_t *p_evt);

typedef struct ble_heart_s ble_heart_t;

typedef struct{
    ble_heart_data_handler_t data_handler; /**< Event handler to be called for handling received data. */
    ble_heart_evt_handler_t evt_handler;   /**< Event handler to be called for handling events in the Heart Rate Service. */
}ble_heart_init_t;

struct ble_heart_s{
    uint8_t                  uuid_type;
    uint16_t                 service_handle;
    uint16_t                 conn_handle;

    ble_gatts_char_handles_t tx_handles;
    ble_gatts_char_handles_t rx_handled;
    ble_heart_data_handler_t data_handler;
    
};

uint32_t ble_heart_init(ble_heart_t *p_hrs, ble_heart_init_t const *p_heart_init);

#endif