#ifndef BLE_HRART_H
#define BLE_HEART_H
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
//Step 2 - Implementing the Custom Service
#define BLE_HEART_DEF(_name)                          \
    static ble_heart_t _name;                         \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,               \
                        BLE_HRS_BLE_OBSERVER_PRIO,    \
                        ble_heart_on_ble_evt, &_name)

/*
#define BLE_UUID_HEART_RATE_SERVICE 0x180D
*/
#define BLE_HEART_BASE_UUID {{0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0xC9, 0xAD, 0x64, 0xF3}}

#define BLE_HEART_SERVICE_UUID 0x1400
#define BLE_HEART_VALUE_CHAR_UUID 0x1401
// declare an event type specific to our service
typedef enum 
{
    BLE_HEART_NOTIFICATION_ENABLE,
    BLE_HEART_NOTIFICATION_DISABLE,
    BLE_HEART_EVT_CONNECTED,
    BLE_HEART_EVT_DISCONNECTED
}ble_heart_evt_type_t;
/**@brief Custom Service event. */
typedef struct 
{
    ble_heart_evt_type_t evt_type;
}ble_heart_evt_t;


typedef struct ble_heart_s ble_heart_t;
/**@brief Heart Rate Service event handler type. */
typedef void (*ble_heart_evt_handler_t) (ble_heart_t *p_hrs, ble_heart_evt_t *p_hrs_evt);
/**@brief Custom Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct{
    uint8_t time;
    ble_srv_cccd_security_mode_t cccd;
    ble_srv_cccd_security_mode_t ble_heart_value_char_attr_md; /**< Initial security level for Custom characteristics attribute */
    ble_heart_evt_handler_t evt_handler; /**< Event handler to be called for handling events in the Custom Service. */ //step 7
}ble_heart_init_t;


struct ble_heart_s{
    uint16_t                    service_handle;
    ble_gatts_char_handles_t    heart_value_handles;
    uint16_t                    conn_handle;
    uint8_t                     uuid_type;

    ble_heart_evt_handler_t     evt_handler;/**< Event handler to be called for handling events in the Custom Service. */
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
uint32_t ble_heart_init(ble_heart_t *p_hrs, ble_heart_init_t *p_hrs_init);
/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */

void ble_heart_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);
//Step 8 - Notifying the Custom Value Characteristic
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
uint32_t ble_heart_custom_value_update(ble_heart_t *p_hrs, uint8_t hrs_value);




#endif
// Step 2 - Creating a Custom Base UUID
//Step 3 - Initializing the Service and advertising our 128-bit UUID.
// Step 4 - Adding a Custom Value Characteristic to the Custom Service.
//Step 5 - Handling events from the SoftDevice.
//Step 6 - Handling the Write event from the SoftDevice.
// Step 7 - Propagating Custom Service events to the application
/*
Until now we've only handled the events that are propagated by the SoftDevice, 
but in some cases it makes sense to propagate events to the application.
In order to do this 
we need to add an event handler to our Custom Service Init structure 
and Custom Service structure.
*/
//Step 8 - Notifying the Custom Value Characteristic