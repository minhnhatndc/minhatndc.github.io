#include "sdk_common.h"

#include "ble_temp_dev.h"
#include <string.h>
#include "ble_srv_common.h"
#include "ble_conn_state.h"

#define NRF_LOG_MODULE_NAME ble_temp
#if BLE_BAS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       BLE_BAS_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  BLE_BAS_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR BLE_BAS_CONFIG_DEBUG_COLOR
#else // BLE_BAS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // BLE_BAS_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


#define INVALID_BATTERY_LEVEL 255


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_bas       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_temp_t * p_temp, ble_evt_t const * p_ble_evt)
{

    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (    (p_evt_write->handle == p_temp->tempareture_handles.value_handle)
        &&  (p_evt_write->len == 2))
    {
        if (p_temp->evt_handler == NULL)
        {
            return;
        }

        ble_temp_evt_t evt;

        if (ble_srv_is_notification_enabled(p_evt_write->data))
        {
            evt.evt_type = BLE_TEMP_EVT_NOTIFICATION_ENABLED;
        }
        else
        {
            evt.evt_type = BLE_TEMP_EVT_NOTIFICATION_DISABLED;
        }
        evt.conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;

        // CCCD written, call application event handler.
        p_temp->evt_handler(p_temp, &evt);
    }
}

/* This code belongs in ble_cus.c*/

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_temp_t * p_temp, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_temp->conn_handle = BLE_CONN_HANDLE_INVALID;
}

/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_temp_t * p_temp, ble_evt_t const * p_ble_evt)
{
    p_temp->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}


void ble_temp_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    if ((p_context == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    ble_temp_t * p_temp = (ble_temp_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_WRITE:
            on_write(p_temp, p_ble_evt);
            break;
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_temp, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_temp, p_ble_evt);
            break;
        default:
            // No implementation needed.
            break;
    }
}

static uint8_t tempareture_encode(ble_temp_t * temp_, uint16_t value, uint8_t * p_encoded_buffer)
{
  ret_code_t err_code = NRF_SUCCESS;
  uint8_t flags = 0;
  uint8_t len   = 1;
  int     i;



}


/**@brief Function for adding the Battery Level characteristic.
 *
 * @param[in]   p_bas        Battery Service structure.
 * @param[in]   p_bas_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t battery_level_char_add(ble_temp_t * p_temp, const ble_temp_init_t * p_temp_init)
{
    ret_code_t             err_code;
    ble_add_char_params_t  add_char_params;
    ble_add_descr_params_t add_descr_params;
    uint8_t                initial_battery_level;
    uint8_t                init_len;
    uint8_t                encoded_report_ref[BLE_SRV_ENCODED_REPORT_REF_LEN];

   


    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = BLE_UUID_BATTERY_LEVEL_CHAR;
    add_char_params.max_len           = sizeof(uint8_t);
    add_char_params.init_len          = sizeof(uint8_t);
    add_char_params.p_init_value      = 0;

    add_char_params.char_props.notify = 1;
    add_char_params.char_props.read   = 1;

    add_char_params.cccd_write_access = p_temp_init->bl_cccd_wr_sec;
    add_char_params.read_access       = p_temp_init->bl_rd_sec;

    err_code = characteristic_add(p_temp->service_handle,
                                  &add_char_params,
                                  &(p_temp->tempareture_handles));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

        // Add Humid measure


    memset(&add_descr_params, 0, sizeof(add_descr_params));





    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    return NRF_SUCCESS;
}


ret_code_t ble_temp_init(ble_temp_t * p_temp, const ble_temp_init_t * p_temp_init)
{
    if (p_temp == NULL || p_temp_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_code_t err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_temp->evt_handler               = p_temp_init->evt_handler;
    p_temp->conn_handle               = BLE_CONN_HANDLE_INVALID;


    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_temp->service_handle);
    VERIFY_SUCCESS(err_code);

    // Add battery level characteristic
    err_code = battery_level_char_add(p_temp, p_temp_init);
    return err_code;
}


/**@brief Function for sending notifications with the Battery Level characteristic.
 *
 * @param[in]   p_hvx_params Pointer to structure with notification data.
 * @param[in]   conn_handle  Connection handle.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t battery_notification_send(ble_gatts_hvx_params_t * const p_hvx_params,
                                            uint16_t                       conn_handle)
{
    ret_code_t err_code = sd_ble_gatts_hvx(conn_handle, p_hvx_params);
    if (err_code == NRF_SUCCESS)
    {
        NRF_LOG_INFO("Battery notification has been sent using conn_handle: 0x%04X", conn_handle);
    }
    else
    {
        NRF_LOG_DEBUG("Error: 0x%08X while sending notification with conn_handle: 0x%04X",
                      err_code,
                      conn_handle);
    }
    return err_code;
}


ret_code_t ble_temp_battery_level_update(ble_temp_t * p_temp,
                                        uint8_t     battery_level,
                                        uint16_t    conn_handle)
{
    if (p_temp == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_code_t         err_code = NRF_SUCCESS;
    ble_gatts_value_t  gatts_value;

  

    return err_code;
}





