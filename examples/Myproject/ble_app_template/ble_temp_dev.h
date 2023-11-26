#ifndef BLE_TEMP_DEV_H__
#define BLE_TEMP_DEV_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  BLE_TEMPARETURE_UNIT_FAHRENHET   (0x1  << 0)
#define  BLE_TEMPARETURE_TIME_STEMP_FLAG  (0x01 << 1)
#define  BLE_TEMPERATURE_TYPE_FLAG        (0x01 << 2)




/**@brief Macro for defining a ble_bas instance.
 *
 * @param   _name  Name of the instance.
 * @hideinitializer
 */
#define BLE_TEMP_DEF(_name)                          \
    static ble_bas_t _name;                         \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,             \
                         BLE_BAS_BLE_OBSERVER_PRIO, \
                         ble_bas_on_ble_evt,        \
                         &_name)

/**@brief Battery Service event type. */
typedef enum
{
    BLE_TEMP_EVT_NOTIFICATION_ENABLED,     /**< Battery value notification enabled event. */
    BLE_TEMP_EVT_NOTIFICATION_DISABLED,    /**< Battery value notification disabled event. */
    BLE_TEMP_EVT_CONNECTED,
    BLE_TEMP_EVT_DISCONNECTED

} ble_temp_evt_type_t;

/**@brief Battery Service event. */
typedef struct
{
    ble_temp_evt_type_t   evt_type;         /**< Type of event. */
    uint16_t              conn_handle;       /**< Connection handle. */

} ble_temp_evt_t;

// Forward declaration of the ble_bas_t type.
typedef struct ble_temp_s ble_temp_t;

/**@brief Battery Service event handler type. */
typedef void (* ble_temp_evt_handler_t) (ble_temp_t * p_temp, ble_temp_evt_t * p_evt);

/**@brief Battery Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_temp_evt_handler_t  evt_handler;                    /**< Event handler to be called for handling events in the Battery Service. */
    bool                    is_tempareture_uint_F;

    security_req_t          bl_rd_sec;                      /**< Security requirement for reading the BL characteristic value. */
    security_req_t          bl_cccd_wr_sec;                 /**< Security requirement for writing the BL characteristic CCCD. */
  
} ble_temp_init_t;

/**@brief Battery Service structure. This contains various status information for the service. */
struct ble_temp_s
{
    uint16_t                        service_handle;            /**< Handle of Battery Service (as provided by the BLE stack). */
    uint16_t                        conn_handle; 

    bool                            is_tempareture_uint_F;
    bool                            is_time_stamp_flag_enable;
    bool                            is_tempareture_type_flag_enable;

    ble_temp_evt_handler_t          evt_handler;               /**< Event handler to be called for handling events in the Battery Service. */
   
    

    ble_gatts_char_handles_t        tempareture_handles;
    ble_gatts_char_handles_t        humidation_handles;
};


/**@brief Function for initializing the Battery Service.
 *
 * @param[out]  p_bas       Battery Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_bas_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
ret_code_t ble_temp_init(ble_temp_t * p_temp, const ble_temp_init_t * p_temp_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note For the requirements in the BAS specification to be fulfilled,
 *       ble_bas_battery_level_update() must be called upon reconnection if the
 *       battery level has changed while the service has been disconnected from a bonded
 *       client.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Battery Service structure.
 */
void ble_temp_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for updating the battery level.
 *
 * @details The application calls this function after having performed a battery measurement.
 *          The battery level characteristic will only be sent to the clients which have
 *          enabled notifications. \ref BLE_CONN_HANDLE_ALL can be used as a connection handle
 *          to send notifications to all connected devices.
 *
 * @param[in]   p_bas          Battery Service structure.
 * @param[in]   battery_level  New battery measurement value (in percent of full capacity).
 * @param[in]   conn_handle    Connection handle.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
ret_code_t ble_temp_battery_level_update(ble_temp_t * p_temp,
                                        uint8_t     battery_level,
                                        uint16_t    conn_handle);


/**@brief Function for sending the last battery level when bonded client reconnects.
 *
 * @details The application calls this function, in the case of a reconnection of
 *          a bonded client if the value of the battery has changed since
 *          its disconnection.
 *
 * @note For the requirements in the BAS specification to be fulfilled,
 *       this function must be called upon reconnection if the battery level has changed
 *       while the service has been disconnected from a bonded client.
 *
 * @param[in]   p_bas          Battery Service structure.
 * @param[in]   conn_handle    Connection handle.
 *
 * @return      NRF_SUCCESS on success,
 *              NRF_ERROR_INVALID_STATE when notification is not supported,
 *              otherwise an error code returned by @ref sd_ble_gatts_hvx.
 */
ret_code_t ble_temp_battery_lvl_on_reconnection_update(ble_temp_t * p_temp,
                                                      uint16_t    conn_handle);


#ifdef __cplusplus
}
#endif

#endif // BLE_BAS_H__

/** @} */
