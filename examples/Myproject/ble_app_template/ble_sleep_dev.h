#ifndef BLE_SLEEP_DEV_H__
#define BLE_SLEEP_DEV_H__

#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "ble_link_ctx_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_nus instance.
 *
 * @param     _name            Name of the instance.
 * @param[in] _nus_max_clients Maximum number of NUS clients connected at a time.
 * @hideinitializer
 */
#define BLE_SLEEP_DEF(_name, _nus_max_clients)                      \
    BLE_LINK_CTX_MANAGER_DEF(CONCAT_2(_name, _link_ctx_storage),  \
                             (_nus_max_clients),                  \
                             sizeof(ble_sleep_client_context_t));   \
    static ble_sleep_t _name =                                      \
    {                                                             \
        .p_link_ctx_storage = &CONCAT_2(_name, _link_ctx_storage) \
    };                                                            \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,                           \
                         BLE_NUS_BLE_OBSERVER_PRIO,               \
                         ble_sleep_on_ble_evt,                      \
                         &_name)

#define BLE_UUID_SLEEP_SERVICE              0x1400                               /**< The UUID of the Nordic UART Service. */
#define BLE_SLEEP_CHARACTERISTIC_UUID       0x1401
#define BLE_SLEEP_COUNT_CHARACTERISTIC_UUID 0x1402

#define OPCODE_LENGTH        1
#define HANDLE_LENGTH        2

/**@brief   Maximum length of data (in bytes) that can be transmitted to the peer by the Nordic UART service module. */
#if defined(NRF_SDH_BLE_GATT_MAX_MTU_SIZE) && (NRF_SDH_BLE_GATT_MAX_MTU_SIZE != 0)
    #define BLE_SLEEP_MAX_DATA_LEN (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - OPCODE_LENGTH - HANDLE_LENGTH)
#else
    #define BLE_NUS_MAX_DATA_LEN (BLE_GATT_MTU_SIZE_DEFAULT - OPCODE_LENGTH - HANDLE_LENGTH)
    #warning NRF_SDH_BLE_GATT_MAX_MTU_SIZE is not defined.
#endif


/**@brief   Nordic UART Service event types. */
typedef enum
{
    BLE_SLEEP_EVT_CONNECT, 
    BLE_SLEEP_EVT_DISCONNECT, 
    BLE_EVT_NOTIFICATION_ENABLED,
    BLE_EVT_NOTIFICATION_DISABLED,
    BLE_SLEEP_EVT_READ_RDY
} ble_sleep_evt_type_t;


/* Forward declaration of the ble_nus_t type. */
typedef struct ble_sleep_s ble_sleep_t;


/**@brief   Nordic UART Service @ref BLE_NUS_EVT_RX_DATA event data.
 *
 * @details This structure is passed to an event when @ref BLE_NUS_EVT_RX_DATA occurs.
 */
typedef struct
{
    uint8_t const * p_data; /**< A pointer to the buffer with received data. */
    uint16_t        length; /**< Length of received data. */
} ble_sleep_evt_rx_data_t;


/**@brief Nordic UART Service client context structure.
 *
 * @details This structure contains state context related to hosts.
 */
typedef struct
{
    bool is_notification_enabled; /**< Variable to indicate if the peer has enabled notification of the RX characteristic.*/
} ble_sleep_client_context_t;


/**@brief   Nordic UART Service event structure.
 *
 * @details This structure is passed to an event coming from service.
 */
typedef struct
{
    ble_sleep_evt_type_t          evt_type;        /**< Event type. */
    ble_sleep_t                *  p_slp;       /**< A pointer to the instance. */
    uint16_t                      conn_handle; /**< Connection handle. */ 
    ble_sleep_client_context_t *  p_link_ctx;  /**< A pointer to the link context. */
    union
    {
        ble_sleep_evt_rx_data_t rx_data; /**< @ref BLE_NUS_EVT_RX_DATA event data. */
    } params;
} ble_sleep_evt_t;


/**@brief Nordic UART Service event handler type. */
typedef void (* ble_sleep_data_handler_t) (ble_sleep_t *p_slp,ble_sleep_evt_t * p_evt);


/**@brief   Nordic UART Service initialization structure.
 *
 * @details This structure contains the initialization information for the service. The application
 * must fill this structure and pass it to the service using the @ref ble_nus_init
 *          function.
 */
typedef struct
{   
    ble_sleep_data_handler_t evt_handler; /**< Event handler to be called for handling received data. */
} ble_sleep_init_t;


/**@brief   Nordic UART Service structure.
 *
 * @details This structure contains status information related to the service.
 */
struct ble_sleep_s
{
    uint8_t                         uuid_type;          /**< UUID type for Nordic UART Service Base UUID. */
    uint16_t                        service_handle;     /**< Handle of Nordic UART Service (as provided by the SoftDevice). */
    uint16_t                        conn_handle;        /**< Handle connection state*/
    
    ble_gatts_char_handles_t        slp_cnt_handles;        
    ble_gatts_char_handles_t        slp_handles;
    
    
    
    ble_sleep_data_handler_t          evt_handler;       /**< Event handler to be called for handling received data. */
    blcm_link_ctx_storage_t * const   p_link_ctx_storage; 
    uint8_t                           slp_count;
};


/**@brief   Function for initializing the Nordic UART Service.
 *
 * @param[out] p_nus      Nordic UART Service structure. This structure must be supplied
 *                        by the application. It is initialized by this function and will
 *                        later be used to identify this particular service instance.
 * @param[in] p_nus_init  Information needed to initialize the service.
 *
 * @retval NRF_SUCCESS If the service was successfully initialized. Otherwise, an error code is returned.
 * @retval NRF_ERROR_NULL If either of the pointers p_nus or p_nus_init is NULL.
 */
uint32_t ble_sleep_init(ble_sleep_t * p_nus, ble_sleep_init_t const * p_sleep_init);


/**@brief   Function for handling the Nordic UART Service's BLE events.
 *
 * @details The Nordic UART Service expects the application to call this function each time an
 * event is received from the SoftDevice. This function processes the event if it
 * is relevant and calls the Nordic UART Service event handler of the
 * application if necessary.
 *
 * @param[in] p_ble_evt     Event received from the SoftDevice.
 * @param[in] p_context     Nordic UART Service structure.
 */
void ble_sleep_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief   Function for sending a data to the peer.
 *
 * @details This function sends the input string as an RX characteristic notification to the
 *          peer.
 *
 * @param[in]     p_nus       Pointer to the Nordic UART Service structure.
 * @param[in]     p_data      String to be sent.
 * @param[in,out] p_length    Pointer Length of the string. Amount of sent bytes.
 * @param[in]     conn_handle Connection Handle of the destination client.
 *
 * @retval NRF_SUCCESS If the string was sent successfully. Otherwise, an error code is returned.
 */
uint32_t ble_sleep_data_send(ble_sleep_t * p_nus,
                           uint8_t   * p_data,
                           uint16_t  * p_length,
                           uint16_t    conn_handle);


uint32_t ble_sleep_data_count_send(ble_sleep_t *p_slp, uint8_t data);
#ifdef __cplusplus
}
#endif

#endif // BLE_NUS_H__

/** @} */
