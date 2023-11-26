#ifndef  BLE_TEMP_C_H
#define  BLE_TEMP_C_H
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "ble_db_discovery.h"
#include "sdk_config.h"
#include "nrf_ble_gq.h"
#include "nrf_sdh_ble.h"

#include "nrf_log.h"

#define BLE_TEMP_C_DEF(_name)                 \
        static ble_temp_c_t _name;            \
        NRF_SDH_BLE_OBSERVER(_name ## __obs,  \
                            BLE_HRS_C_BLE_OBSERVER_PRIO,          \
                            ble_temp_c_on_ble_evt,&_name)

#define BLE_TEMPS_C_DEF(_name, _cnt)          \
        static ble_temp_c_t _name[_cnt];      \
        NRF_SDH_BLE_OBSERVERS(_name ## _obs,   \
                             BLE_HRS_C_BLE_OBSERVER_PRIO,          \
                            ble_temp_c_on_ble_evt,&_name,_cnt)
                              

// Define =====================================
#define BLE_TEMP_C_SERVICE_UUID BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE
#define BLE_TEMP_C_CHAR_UUID    BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR
// Event type
typedef enum{
  BLE_TEMP_C_EVT_DISCOVERY_COMPLETED,
  BLE_TEMP_C_EVT_TEMP_NOTIFICATION
}ble_temp_c_evt_type_t;
// Temp Measurement handles related to the Temp Service found on the peer. */
typedef struct
{
  uint8_t tmp_value;
}ble_tmp_t;
// contain handle handles related to the Temp Service found on the peer.
typedef  struct
{
  uint16_t tmp_cccd_handle;
  uint16_t tmp_handle;
} tmp_db_t;
typedef struct
{
  uint16_t                  conn_handle;
  ble_temp_c_evt_type_t     evt_type;
  union
  {
    tmp_db_t                peer_db;
    ble_tmp_t               tmp;
  }params;
}ble_temp_c_evt_t;

typedef struct ble_temp_c_s ble_temp_c_t;
typedef  void  (* ble_temp_c_evt_handler_t) (ble_temp_c_t *p_ble_tmp_c, ble_temp_c_evt_t *p_evt);

struct ble_temp_c_s
{
  uint16_t                  conn_handle;/**< Connection handle, as provided by the SoftDevice. */
  uint16_t                  service_handle;
  tmp_db_t                  peer_tmp_db;/**< Handles related to TEMP on the peer. */
  ble_temp_c_evt_handler_t  evt_handler;/**< Application event handler to be called when there is an event related to the Heart Rate Service. */
  ble_srv_error_handler_t   error_handler;/**< Function to be called in case of an error. */
  nrf_ble_gq_t              *p_gatt_queue;/**< Pointer to the BLE GATT Queue instance. */
};
typedef struct{
  ble_temp_c_evt_handler_t  evt_handle;
  ble_srv_error_handler_t   error_handle;
  nrf_ble_gq_t              *p_gatt_queue;
}ble_temp_c_init_t;

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
uint32_t ble_temp_c_init(ble_temp_c_t *p_ble_tmp_c, ble_temp_c_init_t *p_ble_tmp_c_init);
/**@brief     Function for handling BLE events from the SoftDevice.
 *
 * @details   This function handles the BLE events received from the SoftDevice. If a BLE
 *            event is relevant to the Heart Rate Client module, the function uses the event's data to update
 *            interval variables and, if necessary, send events to the application.
 *
 * @param[in] p_ble_evt     Pointer to the BLE event.
 * @param[in] p_context     Pointer to the Heart Rate Client structure.
 */
 void ble_temp_c_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);
/**@brief   Function for enabling notifications on the Battery Level characteristic.
 *
 * @details This function enables the notification of the Battery Level characteristic at the
 *          peer by writing to the CCCD of the Battery Level Characteristic.
 *
 * @param   p_ble_bas_c Pointer to the Battery Service client structure.
 *
 * @retval  NRF_SUCCESS     If the SoftDevice has been requested to write to the CCCD of the peer.
 * @retval  NRF_ERROR_NULL  Parameter is NULL.
 * @retval  err_code        Otherwise, an error code returned by the SoftDevice API @ref
 *                          sd_ble_gattc_write.
 */
uint32_t ble_tmp_c_ble_notif_enable(ble_temp_c_t *p_ble_tmp_c);
/**@brief   Function for reading the Battery Level characteristic.
 *
 * @param   p_ble_bas_c Pointer to the Battery Service client structure.
 *
 * @retval  NRF_SUCCESS If the read request was successfully queued to be sent to peer.
 */
uint32_t ble_tmp_c_read(ble_temp_c_t *p_ble_tmp_c);
/**@brief     Function for handling events from the Database Discovery module.
 *
 * @details   Call this function when you get a callback event from the Database Discovery module.
 *            This function handles an event from the Database Discovery module, and determines
 *            whether it relates to the discovery of Battery Service at the peer. If it does, this function
 *			  calls the application's event handler to indicate that the Battery Service was
 *            discovered at the peer. The function also populates the event with service-related
 *            information before providing it to the application.
 *
 * @param     p_ble_bas_c Pointer to the Battery Service client structure.
 * @param[in] p_evt Pointer to the event received from the Database Discovery module.
 *
 */
 void ble_tmp_on_db_disc_evt(ble_temp_c_t *p_ble_tmp_c, ble_db_discovery_evt_t *p_evt);
/**@brief     Function for assigning handles to this instance of bas_c.
 *
 * @details   Call this function when a link has been established with a peer to
 *            associate the link to this instance of the module. This makes it
 *            possible to handle several links and associate each link to a particular
 *            instance of this module. The connection handle and attribute handles are
 *            provided from the discovery event @ref BLE_BAS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ble_bas_c    Pointer to the Battery client structure instance for associating the link.
 * @param[in] conn_handle    Connection handle associated with the given Battery Client Instance.
 * @param[in] p_peer_handles Attribute handles on the BAS server you want this BAS client to
 *                           interact with.
 */
 uint32_t ble_tmp_c_handles_assign(ble_temp_c_t *p_ble_tmp_c, uint16_t conn_handle, tmp_db_t *p_peer_handle);

#endif