#include "ble_nus_data.h"
#include "nrf_sdh_ble.h"
#include "ble.h"
#include "sdk_common.h"

#define NRF_LOG_MODULE_NAME ble_nus_data_client_context_t
#define NRF_LOG_LEVEL 3
#define NRF_LOG_INFO_COLOR 0
#define NRF_LOG_DEBUG_COLOR 0
#include "nrf_log.h"

NRF_LOG_MODULE_REGISTER();

#define BLE_UUID_NUS_DATA_TX_CHARACTERISTIC 0x0003
#define BLE_UUID_NUS_DATA_RX_CHARACTERISTIC 0x0002

#define BLE_NUS_DATA_MAX_RX_CHAR_LEN BLE_NUS_DATA_MAX_DATA_LEN
#define BLE_NUS_DATA_MAX_TX_CHAR_LEN BLE_NUS_DATA_MAX_DATA_LEN
/**@brief Function for handling the @ref BLE_GAP_EVT_CONNECTED event from the SoftDevice.
 *
 * @param[in] p_nus     Nordic UART Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_connect(ble_nus_data_t *p_nus, ble_evt_t const *p_ble_evt)
{
    ret_code_t err_code;
    ble_nus_data_evt_t evt;
    ble_gatts_value_t gatts_val;
    uint8_t cccd_value[2];
    ble_nus_data_client_context_t *p_client = NULL;

    err_code = blcm_link_ctx_get(p_nus->p_link_ctx_storage,p_ble_evt->evt.gap_evt.conn_handle,(void *)&p_client);

    if(err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("link context for 0x%02X connection hanler failed.", p_ble_evt->evt.gap_evt.conn_handle);
        }
    // check the host cccd value to inform of readlines to send data using RX Characteristic/
    memset(&gatts_val,0,sizeof(ble_gatts_value_t));
    gatts_val.p_value = cccd_value;
    gatts_val.len = sizeof(cccd_value);
    gatts_val.offset = 0;
    err_code = sd_ble_gatts_value_get(p_ble_evt->evt.gap_evt.conn_handle, p_nus->tx_handles.cccd_handle, &gatts_val);
    if((err_code == NRF_SUCCESS) && (p_nus->data_handler != NULL) && (ble_srv_is_notification_enabled(gatts_val.p_value)))
        {
            if(p_client != NULL)
                {
                    p_client->is_notification_enabled = true;
                }
            memset(&evt,0, sizeof(evt));
            evt.type = BLE_NUS_DATA_EVT_COMM_STARTED;
            evt.p_nus_data = p_nus;
            evt.conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            evt.p_link_ctx = p_client;
            p_nus->data_handler(&evt);
        }

}
/**@brief Function for handling the @ref BLE_GATTS_EVT_WRITE event from the SoftDevice.
 *
 * @param[in] p_nus     Nordic UART Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_write(ble_nus_data_t *p_nus, ble_evt_t *p_ble_evt)
{
    ret_code_t err_code;
    ble_nus_data_evt_t evt;
    ble_nus_data_client_context_t *p_client;
    ble_gatts_evt_write_t const *p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    err_code = blcm_link_ctx_get(p_nus->p_link_ctx_storage, p_ble_evt->evt.gatts_evt.conn_handle,(void *)&p_client);
    if(err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Link context for 0x%02X connection handle could not be fetched.", p_ble_evt->evt.gatts_evt.conn_handle);
            
        }
    memset(&evt, 0, sizeof(ble_nus_data_evt_t));
    evt.p_nus_data = p_nus;
    evt.conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;
    evt.p_link_ctx = p_client;
    if((p_evt_write->handle == p_nus->tx_handles.cccd_handle) && (p_evt_write->len == 2))
        {
            if(p_client != NULL)
                {
                    if(ble_srv_is_notification_enabled(p_evt_write->data))
                        {
                            p_client->is_notification_enabled = true;
                            evt.type = BLE_NUS_DATA_EVT_COMM_STARTED;
                        }
                    else{
                        p_client->is_notification_enabled = false;
                        evt.type = BLE_NUS_DATA_EVT_COMM_STOPPED;
                    }
                    if(p_nus->data_handler != NULL)
                        {
                            p_nus->data_handler(&evt);

                        }
                }
        }
    else{
            if((p_evt_write->handle == p_nus->rx_handles.value_handle) && (p_nus->data_handler != NULL))
                {
                    evt.type = BLE_NUS_DATA_EVT_RX_DATA;
                    evt.params.rx_data.p_data = p_evt_write->data;
                    evt.params.rx_data.length = p_evt_write->len;
                    p_nus->data_handler(&evt);
                }
        }
    //else
        //{
            // do nothing
        //}
}
//for handling the @ref BLE_GATTS_EVT_HVN_TX_COMPLETE event from the SoftDevice. 
static void on_hvx_tx_complete(ble_nus_data_t * p_nus, ble_evt_t const * p_ble_evt)
{
    ret_code_t err_code;
    ble_nus_data_evt_t evt;
    ble_nus_data_client_context_t *p_client;
    err_code = blcm_link_ctx_get(p_nus->p_link_ctx_storage, p_ble_evt->evt.gatts_evt.conn_handle,(void *)&p_client);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Link context for 0x%02X connection handle could not be fetched.",
                      p_ble_evt->evt.gatts_evt.conn_handle);
        return;
    }
    if ((p_client->is_notification_enabled) && (p_nus->data_handler != NULL))
    {
        memset(&evt, 0, sizeof(ble_nus_data_evt_t));
        evt.type             = BLE_NUS_DATA_EVT_TX_RDY;
        evt.p_nus_data       = p_nus;
        evt.conn_handle      = p_ble_evt->evt.gatts_evt.conn_handle;
        evt.p_link_ctx       = p_client;

        p_nus->data_handler(&evt);
    }
}
/*
/// @brief 
/// @param p_ble_evt 
/// @param p_context
*/ 
void ble_nus_data_on_ble_evt(ble_evt_t const *p_ble_evt,void *p_context)
{
    if((p_context == NULL)|| (p_ble_evt == NULL))
    {
        return;
    }
    ble_nus_data_t *p_nus = (ble_nus_data_t *)p_context;
    switch ((p_ble_evt->header.evt_id))
    {
    case BLE_GAP_EVT_CONNECTED:
        on_connect(p_nus, p_ble_evt);
        /* code */
        break;
    case BLE_GATTS_EVT_WRITE:
        on_write(p_nus,p_ble_evt);
        break;
    case BLE_GATTS_EVT_HVN_TX_COMPLETE:
        on_hvx_tx_complete(p_nus,p_ble_evt);
        break;
    
    default:
        break;
    }

}
uint32_t ble_nus_data_init(ble_nus_data_t *p_nus, ble_nus_data_init_t const *p_nus_init)
{

    ret_code_t err_code;
    ble_uuid_t ble_uuid;
    ble_uuid128_t nus_base_uuid = NUS_DATA_SERVICE_UUID_BASE;
    ble_add_char_params_t add_char_params;

    VERIFY_PARAM_NOT_NULL(p_nus);
    VERIFY_PARAM_NOT_NULL(p_nus_init);

    // init service structure
    p_nus->data_handler = p_nus_init->data_handler;

    /**@snippet [Adding proprietary Service to the SoftDevice] */
    // Add a custom base UUID.
    err_code = sd_ble_uuid_vs_add(&nus_base_uuid,&p_nus->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_nus->uuid_type;
    ble_uuid.uuid = BLE_NUS_DATA_SERVICE_UUID;

    //add the service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_nus->service_handler);

    /**@snippet [Adding proprietary Service to the SoftDevice] */
    VERIFY_SUCCESS(err_code);

    // RX Characteristic
    memset(&add_char_params, 0 , sizeof(add_char_params));
    add_char_params.uuid = BLE_UUID_NUS_DATA_RX_CHARACTERISTIC;
    add_char_params.uuid_type = p_nus->uuid_type;
    add_char_params.max_len = BLE_NUS_DATA_MAX_RX_CHAR_LEN;
    add_char_params.init_len = sizeof(uint8_t);
    add_char_params.is_var_len = true;
    add_char_params.char_props.write = 1;
    add_char_params.char_props.write_wo_resp = 1;
    
    add_char_params.read_access = SEC_OPEN;
    add_char_params.write_access = SEC_OPEN;

    err_code = characteristic_add(p_nus->service_handler,&add_char_params,&p_nus->rx_handles);
      if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // add TX Characrteristic
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid = BLE_UUID_NUS_DATA_TX_CHARACTERISTIC;
    add_char_params.uuid_type = p_nus->uuid_type;
    add_char_params.max_len = BLE_NUS_DATA_MAX_TX_CHAR_LEN;
    add_char_params.init_len = sizeof(uint8_t);
    add_char_params.is_var_len = true;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access = SEC_OPEN;
    add_char_params.write_access= SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;
    return characteristic_add(p_nus->service_handler,&add_char_params,&p_nus->tx_handles);
     


}
uint32_t ble_nus_data_cus_send(ble_nus_data_t *p_nus, uint8_t *p_data, uint16_t *p_length,uint16_t conn_handle)
{
    ret_code_t err_code;
    ble_gatts_hvx_params_t hvx_params;
    ble_nus_data_client_context_t *p_client;
    err_code = blcm_link_ctx_get(p_nus->p_link_ctx_storage,conn_handle,(void*)&p_client);
    VERIFY_SUCCESS(err_code);

    if((conn_handle == BLE_CONN_HANDLE_INVALID) || (p_client == NULL))
        {
            return NRF_ERROR_NOT_FOUND;
        }
    if(!p_client->is_notification_enabled)
        {
            return NRF_ERROR_INVALID_STATE;
        }
    if(*p_length > BLE_NUS_DATA_MAX_DATA_LEN)
        {
            return NRF_ERROR_INVALID_PARAM;
        }
    memset(&hvx_params,0, sizeof(hvx_params));
    hvx_params.handle = p_nus->tx_handles.value_handle;
    hvx_params.p_data = p_data;
    hvx_params.p_len = p_length;
    hvx_params.type = BLE_GATT_HVX_NOTIFICATION;
    return sd_ble_gatts_hvx(conn_handle,&hvx_params);

}