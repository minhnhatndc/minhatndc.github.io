#include "ble_app_dev.h"
/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_app_t *p_app, ble_evt_t const *p_evt)
{
  ret_code_t err_code;
  p_app->conn_handle = p_evt->evt.gap_evt.conn_handle;
  ble_app_evt_t evt;
  evt.evt_type  = BLE_APP_NOTIFICATION_ENABLED;
  p_app->evt_handler(p_app,&evt);

}
/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_app_t *p_app, ble_evt_t const *p_evt)
 {
    UNUSED_PARAMETER(p_evt);
    p_app->conn_handle  = BLE_CONN_HANDLE_INVALID; 
 }
 /**@brief Function for handling the Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_app_t *p_app, ble_evt_t const *p_evt)
{
  ret_code_t err_code;
  ble_gatts_evt_write_t *p_write_evt = &p_evt->evt.gatts_evt.params.write;
  if(p_write_evt->handle = p_app->hrs_value_handles.value_handle)
  {
  
  }
// Check if the Custom value CCCD is written to and that the value is the appropriate length, i.e 2 bytes.
  if((p_write_evt->handle == p_app->hrs_value_handles.value_handle) && (p_write_evt->len == 2))
  {
    if(p_app->evt_handler != NULL)
      {
        ble_app_evt_t evt;
        if(ble_srv_is_notification_enabled(p_write_evt->data))
        {
          evt.evt_type = BLE_APP_NOTIFICATION_ENABLED;
        }
        else{
          evt.evt_type = BLE_APP_NOTIFICATION_DISABLED;
        }
        // Call the application event handler.
        p_app->evt_handler(p_app,&evt);
      
      }
  
  
  }
}
uint32_t ble_app_init(ble_app_t *p_app, ble_app_init_t *p_init)
 {
    ret_code_t err_code;
    ble_uuid_t ble_uuid;
    ble_add_char_params_t add_char_params;

    if(p_app == NULL || p_init == NULL)
      {
        return NRF_ERROR_NULL;
      }
    // Init service structure
    p_app->conn_handle = BLE_CONN_HANDLE_INVALID;
    p_app->evt_handler  = p_init->evt_handler;

    //Add Service UUID
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_APP_SERVICE_UUID);
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_app->service_handle);
    VERIFY_SUCCESS(err_code);

    // ADD Characteristic UUID
    //add Sleep Characteristic UUID
    memset(&add_char_params,0,sizeof(add_char_params));
    add_char_params.uuid          =     BLE_APP_SLEEP_CHAR_UUID;
    add_char_params.uuid_type     =     p_app->uuid_type;
    add_char_params.max_len       =     MAX_DATA_LEN;
    add_char_params.init_len      =     sizeof(uint8_t);
    add_char_params.char_props.notify   = 1;
    add_char_params.char_props.read     = 1;
    
    add_char_params.read_access         = SEC_OPEN;
    add_char_params.cccd_write_access   = SEC_OPEN;
    err_code= characteristic_add(p_app->service_handle,&add_char_params,&(p_app->sleep_value_handle));
    if(err_code != NRF_SUCCESS)
      {
         return err_code;
      }
    
    // Add Heart rate Characteristic UUID
    memset(&add_char_params,0,sizeof(add_char_params));
    add_char_params.uuid                  =  BLE_APP_HEART_RATE_CHAR_UUID;
    add_char_params.uuid_type             =  p_app->uuid_type;
    add_char_params.max_len               =  MAX_DATA_LEN;
    add_char_params.init_len              =  sizeof(uint16_t);
    add_char_params.char_props.notify     =   1;
    add_char_params.char_props.read       =   1;
    add_char_params.read_access           =  SEC_OPEN;
    add_char_params.cccd_write_access     =  SEC_OPEN;
    err_code = characteristic_add(p_app->service_handle,&add_char_params,&(p_app->hrs_value_handles));
    if(err_code != NRF_SUCCESS)
      {
         return err_code;
      }
    return NRF_SUCCESS;
 }
void ble_app_on_ble_evt(ble_evt_t const *p_evt, void *p_context)
{
  ble_app_t *p_app = (ble_app_t *) p_context;
  if(p_evt == NULL || p_app == NULL)
    {
      return ;
    }
   switch(p_evt->header.evt_id)
   {
    case BLE_GAP_EVT_CONNECTED:
        on_connect(p_app,p_evt);
    break;
    case BLE_GAP_EVT_DISCONNECTED:
        on_disconnect(p_app,p_evt);
    break;
    case BLE_GATTS_EVT_WRITE:
        on_write(p_app,p_evt);
    break;


    default:
        // Nothing
    break;
   }

}
uint32_t ble_hrs_value_update(ble_app_t *p_app, uint8_t value)
{
  ret_code_t err_code;
  if(p_app == NULL) return NRF_ERROR_NULL;
  ble_gatts_value_t gatts_value;
  memset(&gatts_value,0,sizeof(gatts_value));
  gatts_value.len     = sizeof(uint8_t);
  gatts_value.offset  = 0;
  gatts_value.p_value = &value;

  // Update database
  err_code = sd_ble_gatts_value_set(p_app->conn_handle,p_app->hrs_value_handles.value_handle,&gatts_value);
  VERIFY_SUCCESS(err_code);
  // Send value if connected and notifying.
  if((p_app->conn_handle != BLE_CONN_HANDLE_INVALID))
  {
    ble_gatts_hvx_params_t hvx_params;
    memset(&hvx_params,0,sizeof(hvx_params));
    hvx_params.handle     = p_app->hrs_value_handles.value_handle;
    hvx_params.type       = BLE_GATT_HVX_NOTIFICATION;
    hvx_params.p_len      = &gatts_value.len;
    hvx_params.offset     = gatts_value.offset;
    hvx_params.p_data     = gatts_value.p_value;
    
    err_code  = sd_ble_gatts_hvx(p_app->conn_handle,&hvx_params);
  
  }
  else{
    err_code = NRF_ERROR_INVALID_STATE;
  }
  return err_code;


}
