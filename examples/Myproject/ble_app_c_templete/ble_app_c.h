#ifndef  BLE_APP_C_H
#define BLE_APP_C_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "ble_db_discovery.h"
#include "sdk_config.h"
#include "nrf_ble_gq.h"
#include "ble_types.h"
#include "ble_gattc.h"

/**@brief   Macro for defining a ble_app_c instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
 #define BLE_APP_C_DEF(_name)     \
        static ble_app_c_t _name; \
        NRF_SDH_BLE_OBSERVER(_name ## _obs,     \
                            BLE_HRS_C_BLE_OBSERVER_PRIO,  \
                            ble_app_c_on_ble_evt,&_name)

 /** @brief Macro for defining multiple ble_app_c instances.
 *
 * @param   _name   Name of the array of instances.
 * @param   _cnt    Number of instances to define.
 * @hideinitializer
 */
#define BLE_APP_CS_DEF(_name, _cnt)   \
        static ble_app_c_t _name[_cnt]; \

// Define event
typedef enum{
  BLE_APP_C_EVT_DISCOVERY_COMPLETE,
  BLE_APP_C_EVT_TMP_NOTIFICATION
}ble_app_c_evt_type_t;

/**@brief Structure containing the Temperature Measurement received from the peer. */
typedef struct{
  uint16_t tmp_value;
} ble_tmp_t;

/**@brief Structure containing the handles related to the Temparature Service found on the peer. */
typedef  struct{
  uint16_t tmp_cccd_handle;/**< Handle of the CCCD of the Temp Measurement characteristic. */ 
  uint16_t tmp_handle;/**< Handle of the Temp Measurement characteristic, as provided by the SoftDevice. */
} tmp_db_t;
/**@brief Temp Event structure. */
typedef struct{
  ble_app_c_evt_type_t  evt_type;
  uint16_t              conn_handle;
  union{
    tmp_db_t            peer_db;/**< Handles related to the Temp, found on the peer device. This is filled if the evt_type is @ref BLE_HRS_C_EVT_DISCOVERY_COMPLETE.*/
    ble_tmp_t           tmp;/**< Temp Measurement received. This is filled if the evt_type is @ref BLE_HRS_C_EVT_HRM_NOTIFICATION. */
  }params;
}ble_app_c_evt_t;

typedef  struct ble_app_s ble_app_c_t;
/**@brief   Event handler type.
 *
 * @details This is the type of the event handler that is to be provided by the application
 *          of this module to receive events.
 */ 
 typedef void (* ble_app_c_evt_handler_t) (ble_app_c_t *p_app, ble_app_c_evt_t *p_evt);
/**@brief Temp Client structure.
 */
 struct ble_app_s{
  uint16_t      conn_handle;/**< Connection handle, as provided by the SoftDevice. */
  tmp_db_t      peer_tmp_db;/**< Handles related to TMP on the peer. */

  ble_app_c_evt_handler_t evt_handler;/**< Application event handler to be called when there is an event related to the Temp Service. */
  ble_srv_error_handler_t error_handler;/**< Function to be called in case of an error. */
  nrf_ble_gq_t            *p_gatt_queue;/**< Pointer to the BLE GATT Queue instance. */
};

/**@brief Temp Client initialization structure.
 */
 typedef struct
 {
  ble_app_c_evt_handler_t   evt_handler;/**< Event handler to be called by the Heart Rate Client module when there is an event related to the Temp Service. */
  ble_srv_error_handler_t   error_handler;/**< Function to be called in case of an error. */
  nrf_ble_gq_t              *p_gatt_queue;/**< Pointer to the BLE GATT Queue instance. */
 } ble_app_c_init_t;
/**@brief     Function for initializing the Heart Rate Client module.
 *
 * @details   This function registers with the Database Discovery module for the Heart Rate Service.
 *		   	  The module looks for the presence of a Heart Rate Service instance at the peer
 *            when a discovery is started.
 *
 * @param[in] p_ble_hrs_c      Pointer to the Heart Rate Client structure.
 * @param[in] p_ble_hrs_c_init Pointer to the Heart Rate initialization structure that contains
 *                             the initialization information.
 *
 * @retval    NRF_SUCCESS On successful initialization. 
 * @retval    err_code    Otherwise, this function propagates the error code returned by the Database Discovery module API
 *                        @ref ble_db_discovery_evt_register.
 */
 
 uint32_t ble_app_c_init(ble_app_c_t *p_app, ble_app_c_init_t *p_init);
 /**@brief     Function for handling BLE events from the SoftDevice.
 *
 * @details   This function handles the BLE events received from the SoftDevice. If a BLE
 *            event is relevant to the Heart Rate Client module, the function uses the event's data to update
 *            interval variables and, if necessary, send events to the application.
 *
 * @param[in] p_ble_evt     Pointer to the BLE event.
 * @param[in] p_context     Pointer to the Heart Rate Client structure.
 */
 void ble_app_c_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);
 /**@brief   Function for requesting the peer to start sending notification of Heart Rate
 *          Measurement.
 *
 * @details This function enables notification of the Heart Rate Measurement at the peer
 *          by writing to the CCCD of the Heart Rate Measurement characteristic.
 *
 * @param   p_ble_hrs_c Pointer to the Heart Rate Client structure.
 *
 * @retval  NRF_SUCCESS If the SoftDevice is requested to write to the CCCD of the peer.
 * @retval	err_code	Otherwise, this function propagates the error code returned
 *                      by the SoftDevice API @ref sd_ble_gattc_write.
 */

 uint32_t ble_app_c_tmp_notify_enable(ble_app_c_t *p_ble_app_c);
 
 /**@brief     Function for handling events from the Database Discovery module.
 *
 * @details   Call this function when you get a callback event from the Database Discovery module.
 *            This function handles an event from the Database Discovery module and determines
 *            whether it relates to the discovery of Heart Rate Service at the peer. If it does, the function 
 *            calls the application's event handler to indicate that the Heart Rate Service was
 *            discovered at the peer. The function also populates the event with service-related
 *            information before providing it to the application.
 *
 * @param[in] p_ble_hrs_c Pointer to the Heart Rate Client structure instance for associating the link.
 * @param[in] p_evt Pointer to the event received from the Database Discovery module.
 *
 */
void ble_app_on_db_disc_evt(ble_app_c_t *p_ble_app_c, const ble_db_discovery_evt_t *p_evt);
/**@brief     Function for assigning handles to an instance of hrs_c.
 *
 * @details   Call this function when a link has been established with a peer to
 *            associate the link to this instance of the module. This association makes it
 *            possible to handle several links and associate each link to a particular
 *            instance of this module. The connection handle and attribute handles are
 *            provided from the discovery event @ref BLE_HRS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ble_hrs_c        Pointer to the Heart Rate Client structure instance for associating the link.
 * @param[in] conn_handle        Connection handle to associate with the given Heart Rate Client Instance.
 * @param[in] p_peer_hrs_handles Attribute handles for the HRS server you want this HRS_C client to
 *                               interact with.
 */
uint32_t ble_tmp_c_handles_assign(ble_app_c_t *p_ble_tmp_c,
                                  uint16_t     conn_handle,
                                  const tmp_db_t  *p_peer_tmp_handles);
 #endif