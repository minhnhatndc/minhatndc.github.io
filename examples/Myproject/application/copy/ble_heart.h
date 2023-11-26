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
/**@brief   Macro for defining a ble_cus instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_HEART_DEF(_name)                          \
    static ble_heart_t _name;                         \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,                   \
                     BLE_HRS_BLE_OBSERVER_PRIO,       \
                     ble_heart_on_ble_evt, &_name)
   
/*
#define BLE_UUID_HEART_RATE_SERVICE 0x180D
*/
#define BLE_HEART_BASE_UUID {{0xBC, 0x8A, 0xBF, 0x45, 0xCA, 0x05, 0x50, 0xBA, \
                                          0x40, 0x42, 0xB0, 0x00, 0x00, 0xAD, 0x64, 0xF3}}

#define BLE_HEART_SERVICE_UUID 0x1400
#define BLE_HEART_VALUE_CHAR_UUID 0x1401
//Step 7 - Propagating Custom Service events to the application
typedef  enum{
  BLE_HEART_EVT_CONNECTED,
  BLE_HEART_EVT_DISCONNECTED,
  BLE_HEART_NOTIFICATION_ENABLE,
  BLE_HEART_NOTIFICATION_DISABLE
}ble_heart_evt_type_t; 
/**@brief Custom Service event. */
typedef  struct{
  ble_heart_evt_type_t evt_type;
} ble_heart_evt_t;
// Forward declaration of the ble_cus_t type.
 typedef  struct ble_heart_s ble_heart_t;
/**@brief Custom Service event handler type. */
 typedef  void (*ble_heart_evt_handler_t) (ble_heart_t *p_hrs, ble_heart_evt_t *p_evt);

/**@brief Custom Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
 typedef  struct{
  ble_heart_evt_handler_t   evt_handler;
  uint8_t heart_value;
  ble_srv_cccd_security_mode_t heart_value_char_attr_md;  /**< Initial security level for Custom characteristics attribute */
  security_req_t cccd_read_sec;
  security_req_t cccd_write_sec;
} ble_heart_init_t;
 
 /**@brief Custom Service structure. This contains various status information for the service. */
 struct ble_heart_s
 {
    ble_heart_evt_handler_t     evt_handler;
    uint16_t                    service_handle;      /**< Handle of Custom Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t    heart_value_handles; /**< Handles related to the Custom Value characteristic. */
    uint16_t                    conn_handle;         /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                     uuid_type;
  
 };
 // Forward declaration of the ble_cus_t type.
 


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

//Step 5 - Handling events from the SoftDevice.

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */  

void ble_heart_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);
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
 uint32_t ble_heart_custom_value_update(ble_heart_t *p_hrs, uint8_t heart_value);

#endif
// Step 2 - Creating a Custom Base UUID
/*
ow we need to create two structures in ble_cus.h, one Custom Service init structure, ble_cus_init_t struct to hold all the options and data needed to initialize our custom service.
The second struct that we need to create is the Custom Service structure, ble_cus_s, which holds the status information of the service.
The next step is to add a forward declaration of the ble_cus_t type
The first function we're going to implement is ble_cus_init function, which we're going to initialize our service with. First, we need to do is to add its function decleration in the ble_cus.h file
*/
//Step 3 - Initializing the Service and advertising our 128-bit UUID.
/*
The next step is to find the empty services_init function in main.c, which should look like this
static void services_init(void)
{}

We need to replace the BLE_UUID_DEVICE_INFORMATION_SERVICE 
with the CUSTOM_SERVICE_UUID we defined in ble_cus.h 
as well as replace BLE_UUID_TYPE_BLE with BLE_UUID_TYPE_VENDOR_BEGIN 
since this is a 128-bit vendor specific UUID and not a 16-bit Bluetooth SIG UUDID. m_adv_uuids should now look like this

ble_uuid_t m_adv_uuids[] = {{CUSTOM_SERVICE_UUID, BLE_UUID_TYPE_VENDOR_BEGIN }};

After this step we need to tell the BLE stack that we're using a vendor-specific 128-bit UUID and not a 16-bit bit UUID. This is done 
by changing the following define in sdk_config.h from

#define NRF_SDH_BLE_VS_UUID_COUNT 1

The final step we have to do is to change the calling order in main() so that services_init() is called before advertising_init().

*/
// Step 4 - Adding a Custom Value Characteristic to the Custom Service.
/*
creating the custom_value_char_add function to ble_cus.c.



*/

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