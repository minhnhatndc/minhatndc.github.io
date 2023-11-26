
#include "sdk_common.h"

#include "ble.h"
#include "ble_sleep_dev.h"
#include "ble_srv_common.h"

#define NRF_LOG_MODULE_NAME ble_nus
#if BLE_NUS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       BLE_NUS_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  BLE_NUS_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR BLE_NUS_CONFIG_DEBUG_COLOR
#else // BLE_NUS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // BLE_NUS_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


#define BLE_UUID_SLEEP_READ_CHARACTERISTIC  0x0003               /**< The UUID of the TX Characteristic. */
#define BLE_UUID_NUS_RX_CHARACTERISTIC      0x0002               /**< The UUID of the RX Characteristic. */

#define BLE_SLEEP_MAX_RX_CHAR_LEN        BLE_SLEEP_MAX_DATA_LEN /**< Maximum length of the RX Characteristic (in bytes). */
#define BLE_SLEEP_MAX_TX_CHAR_LEN        BLE_SLEEP_MAX_DATA_LEN /**< Maximum length of the TX Characteristic (in bytes). */




static void on_connect(ble_sleep_t * p_slp, ble_evt_t const * p_ble_evt)
{
    ret_code_t                 err_code;
    ble_sleep_evt_t              evt;
    ble_gatts_value_t          gatts_val;
    uint8_t                    cccd_value[2];
    ble_sleep_client_context_t * p_client = NULL;

    err_code = blcm_link_ctx_get(p_slp->p_link_ctx_storage,
                                 p_ble_evt->evt.gap_evt.conn_handle,
                                 (void *) &p_client);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Link context for 0x%02X connection handle could not be fetched.",
                      p_ble_evt->evt.gap_evt.conn_handle);
    }

    /* Check the hosts CCCD value to inform of readiness to send data using the RX characteristic */
    memset(&gatts_val, 0, sizeof(ble_gatts_value_t));
    gatts_val.p_value = cccd_value;
    gatts_val.len     = sizeof(cccd_value);
    gatts_val.offset  = 0;

    err_code = sd_ble_gatts_value_get(p_ble_evt->evt.gap_evt.conn_handle,
                                      p_slp->slp_handles.cccd_handle,
                                      &gatts_val);

    if ((err_code == NRF_SUCCESS)     &&
        (p_slp->evt_handler != NULL) &&
        ble_srv_is_notification_enabled(gatts_val.p_value))
    {
        if (p_client != NULL)
        {
            p_client->is_notification_enabled = true;
        }

        memset(&evt, 0, sizeof(ble_sleep_evt_t));
        evt.evt_type        = BLE_SLEEP_EVT_CONNECT;
        evt.p_slp           = p_slp;
        evt.conn_handle     = p_ble_evt->evt.gap_evt.conn_handle;
        evt.p_link_ctx      = p_client;

        p_slp->evt_handler(p_slp,&evt);
    }
}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_sleep_t *p_slp, ble_evt_t const *p_ble_evt)
 {
  UNUSED_PARAMETER(p_ble_evt);
  p_slp->conn_handle = BLE_CONN_HANDLE_INVALID;
  ble_sleep_evt_t evt;
  evt.evt_type       = BLE_SLEEP_EVT_DISCONNECT;
  p_slp->evt_handler(p_slp,&evt);
 }

/**@brief Function for handling the @ref BLE_GATTS_EVT_WRITE event from the SoftDevice.
 *
 * @param[in] p_nus     Nordic UART Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_write(ble_sleep_t * p_slp, ble_evt_t const * p_ble_evt)
{
    ret_code_t                    err_code;
    ble_sleep_evt_t               evt;
    ble_sleep_client_context_t    * p_client;
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    err_code = blcm_link_ctx_get(p_slp->p_link_ctx_storage,
                                 p_ble_evt->evt.gatts_evt.conn_handle,
                                 (void *) &p_client);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Link context for 0x%02X connection handle could not be fetched.",
                      p_ble_evt->evt.gatts_evt.conn_handle);
    }

    memset(&evt, 0, sizeof(ble_sleep_evt_t));
    evt.p_slp       = p_slp;
    evt.conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;
    evt.p_link_ctx  = p_client;


// Check if the Custom value CCCD is written to and that the value is the appropriate length, i.e 2 bytes.
    if ((p_evt_write->handle == p_slp->slp_handles.cccd_handle) &&
        (p_evt_write->len == 2))
    {
        if (p_client != NULL)
        {
            if (ble_srv_is_notification_enabled(p_evt_write->data))
            {
                p_client->is_notification_enabled = true;
                evt.evt_type                      = BLE_EVT_NOTIFICATION_ENABLED;
            }
            else
            {
                p_client->is_notification_enabled = false;
                evt.evt_type                      = BLE_EVT_NOTIFICATION_DISABLED;
            }

            if (p_slp->evt_handler != NULL)
            {
                p_slp->evt_handler(p_slp,&evt);
            }

        }
    }

    else
    {
        // Do Nothing. This event is not relevant for this service.
    }
}


/**@brief Function for handling the @ref BLE_GATTS_EVT_HVN_TX_COMPLETE event from the SoftDevice.
 *
 * @param[in] p_nus     Nordic UART Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_hvx_tx_complete(ble_sleep_t * p_slp, ble_evt_t const * p_ble_evt)
{
    ret_code_t                 err_code;
    ble_sleep_evt_t              evt;
    ble_sleep_client_context_t * p_client;

    err_code = blcm_link_ctx_get(p_slp->p_link_ctx_storage,
                                 p_ble_evt->evt.gatts_evt.conn_handle,
                                 (void *) &p_client);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Link context for 0x%02X connection handle could not be fetched.",
                      p_ble_evt->evt.gatts_evt.conn_handle);
        return;
    }

    if ((p_client->is_notification_enabled) && (p_slp->evt_handler != NULL))
    {
        memset(&evt, 0, sizeof(ble_sleep_evt_t));
        evt.evt_type    = BLE_SLEEP_EVT_READ_RDY;
        evt.p_slp       = p_slp;
        evt.conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;
        evt.p_link_ctx  = p_client;

        p_slp->evt_handler(p_slp,&evt);
    }
}


void ble_sleep_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    if ((p_context == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    ble_sleep_t * p_slp = (ble_sleep_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_slp, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_slp, p_ble_evt);
            break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
            on_hvx_tx_complete(p_slp, p_ble_evt);
            break;
       case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_slp,p_ble_evt);
            break;
        default:
            // No implementation needed.
            break;
    }
}


uint32_t ble_sleep_init(ble_sleep_t * p_slp, ble_sleep_init_t const * p_slp_init)
{
    ret_code_t            err_code;
    ble_uuid_t            ble_uuid;
    ble_add_char_params_t add_char_params;

    VERIFY_PARAM_NOT_NULL(p_slp);
    VERIFY_PARAM_NOT_NULL(p_slp_init);

    // Initialize the service structure.
    p_slp->evt_handler = p_slp_init->evt_handler;
    ble_uuid.type = p_slp->uuid_type;
    

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_SLEEP_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_slp->service_handle);
    /**@snippet [Adding proprietary Service to the SoftDevice] */
    VERIFY_SUCCESS(err_code);

    // Add the Sleep Adc Read Characteristic.
    /**@snippet [Adding proprietary characteristic to the SoftDevice] */
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = BLE_UUID_SLEEP_READ_CHARACTERISTIC;
    add_char_params.uuid_type         = p_slp->uuid_type;
    add_char_params.max_len           = BLE_SLEEP_MAX_TX_CHAR_LEN;
    add_char_params.init_len          = sizeof(uint8_t);
    add_char_params.is_var_len        = true;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access       = SEC_OPEN;
    add_char_params.write_access      = SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;

    err_code = characteristic_add(p_slp->service_handle, &add_char_params, &p_slp->slp_handles);
    /**@snippet [Adding proprietary characteristic to the SoftDevice] */
    VERIFY_SUCCESS(err_code);
     
     // Add Characteristic count sleep nop
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR;
    add_char_params.uuid_type         = p_slp->uuid_type;
    add_char_params.max_len           = BLE_SLEEP_MAX_TX_CHAR_LEN;
    add_char_params.init_len          = sizeof(uint8_t);
    add_char_params.is_var_len        = true;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access       = SEC_OPEN;
    add_char_params.write_access      = SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;

    err_code = characteristic_add(p_slp->service_handle, &add_char_params, &p_slp->slp_cnt_handles);
    /**@snippet [Adding proprietary characteristic to the SoftDevice] */
    VERIFY_SUCCESS(err_code);

    return  NRF_SUCCESS;
}


uint32_t ble_sleep_data_send(ble_sleep_t * p_slp,
                           uint8_t   * p_data,
                           uint16_t  * p_length,
                           uint16_t    conn_handle)
{
    ret_code_t                 err_code;
    ble_gatts_hvx_params_t     hvx_params;
    ble_sleep_client_context_t * p_client;

    VERIFY_PARAM_NOT_NULL(p_slp);

    err_code = blcm_link_ctx_get(p_slp->p_link_ctx_storage, conn_handle, (void *) &p_client);
    VERIFY_SUCCESS(err_code);

    if ((conn_handle == BLE_CONN_HANDLE_INVALID) || (p_client == NULL))
    {
        return NRF_ERROR_NOT_FOUND;
    }

    if (!p_client->is_notification_enabled)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (*p_length > BLE_SLEEP_MAX_DATA_LEN)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_params.handle = p_slp->slp_handles.value_handle;
    hvx_params.p_data = p_data;
    hvx_params.p_len  = p_length;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;

    return sd_ble_gatts_hvx(conn_handle, &hvx_params);
}

uint32_t ble_sleep_data_count_send(ble_sleep_t *p_slp, uint8_t data)
{
    uint32_t err_code;

    // Send value if connected and notifying
    if (p_slp->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
       
        uint16_t               len;
        uint16_t               hvx_len;
        ble_gatts_hvx_params_t hvx_params;

        len     = sizeof(data);
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_slp->slp_cnt_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = &data;

        err_code = sd_ble_gatts_hvx(p_slp->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}
