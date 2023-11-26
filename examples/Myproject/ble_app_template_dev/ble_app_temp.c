#include "ble_app_temp.h"
#include "nrf_log.h"
static uint8_t encode_value(ble_temp_t *p_temp, uint16_t value, uint8_t *p_buffer)
{
  uint8_t len = 1;
  int i;

}
uint32_t ble_temp_init(ble_temp_t *p_tmp, ble_temp_init_t *p_init)
{
  ret_code_t err_code;
  ble_add_char_params_t add_char_params;

  if(p_tmp == NULL || p_init == NULL)
    {
      return NRF_ERROR_NULL;
    }
   //init service structure
   p_tmp->conn_handle = BLE_CONN_HANDLE_INVALID;
   p_tmp->evt_handler  = p_init->evt_handler;
   //Add service
   ble_uuid_t     ble_uuid;

   BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_TEMP_SERVICE_UUID);
   err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_tmp->service_handle);
   VERIFY_SUCCESS(err_code);

   // Add Characteristic
   memset(&add_char_params,0,sizeof(add_char_params));
   add_char_params.uuid       =  BLE_TEMP_CHAR_UUID;
   add_char_params.uuid_type  =  p_tmp->uuid_type;
   add_char_params.max_len    =   sizeof(uint8_t);
   add_char_params.init_len   =   sizeof(uint8_t);
   add_char_params.char_props.notify  = 1;
   add_char_params.char_props.read    = 1;

   add_char_params.read_access    = SEC_OPEN;
   add_char_params.cccd_write_access   = SEC_OPEN;
   err_code = characteristic_add(p_tmp->service_handle,&add_char_params,&(p_tmp->tmp_value_handle));
   if(err_code != NRF_SUCCESS) return err_code;

   return NRF_SUCCESS; 
}


static void on_connect(ble_temp_t *p_tmp, ble_evt_t const *p_ble_evt)
{
  p_tmp->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
  ble_temp_evt_t evt;
  evt.evt_type  = BLE_TEMP_CONNECTED;
  p_tmp->evt_handler(p_tmp,&evt);


}
static void on_disconnect(ble_temp_t *p_tmp, ble_evt_t const *p_ble_evt)
{
  UNUSED_PARAMETER(p_ble_evt);
  ble_temp_evt_t evt;
  evt.evt_type = BLE_TEMP_DISCONTED;

  p_tmp->conn_handle  = BLE_CONN_HANDLE_INVALID;
  p_tmp->evt_handler(p_tmp,&evt);
}
static void on_write(ble_temp_t *p_ble_tmp, ble_evt_t const *p_ble_evt)
{
  ret_code_t err_code;
  ble_gatts_evt_write_t const *p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
  //Check if the handle passed with the event match he Custom Value Characteristic handle.
  if(p_evt_write->handle == p_ble_tmp->tmp_value_handle.value_handle);
  {
    // do some thing
  }
 // Check if the Custom value CCCD is written to and that the value is the appropriate length, i.e 2 bytes.
  if((p_evt_write->handle == p_ble_tmp->tmp_value_handle.cccd_handle) 
      && (p_evt_write->len == 2))
  { if(p_ble_tmp->evt_handler != NULL)
    {
    ble_temp_evt_t evt;
    if(ble_srv_is_notification_enabled(p_evt_write->data))
    {
      evt.evt_type = BLE_TEMP_NOTIFICATION_ENABLED;
    }
    else
    {
      evt.evt_type = BLE_TEMP_NOTIFICATION_DISABLED;
    }
    p_ble_tmp->evt_handler(p_ble_tmp,&evt);
  
  }
  
  }
}
void ble_temp_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context)
{
  ret_code_t err_code;
  ble_temp_t *p_ble_tmp = (ble_temp_t *) p_context;
  if(p_ble_evt == NULL || p_ble_tmp == NULL)
  {
    return;
  }
  switch(p_ble_evt->header.evt_id)
  {
    case BLE_GAP_EVT_CONNECTED:
      on_connect(p_ble_tmp,p_ble_evt);
    break;
    case BLE_GAP_EVT_DISCONNECTED:
      on_disconnect(p_ble_tmp,p_ble_evt);

    break;
    case BLE_GATTS_EVT_WRITE:
      on_write(p_ble_tmp,p_ble_evt);
    break;
    default:
    break;
  }
}
uint32_t ble_temp_value_update(ble_temp_t *p_tmp, uint8_t value)
{ 
 
  ret_code_t err_code;
  if (p_tmp == NULL)
    {
        return NRF_ERROR_NULL;
    }

  ble_gatts_value_t gatts_value;

  memset(&gatts_value,0,sizeof(gatts_value));
  gatts_value.len     = sizeof(uint8_t);
  gatts_value.offset  = 0;
  gatts_value.p_value = &value;

  err_code = sd_ble_gatts_value_set(p_tmp->conn_handle,p_tmp->tmp_value_handle.value_handle,&gatts_value);
  if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
 
  if((p_tmp->conn_handle != BLE_CONN_HANDLE_INVALID))
  {
    ble_gatts_hvx_params_t hvx_params;
    memset(&hvx_params,0,sizeof(hvx_params));
    hvx_params.handle = p_tmp->tmp_value_handle.value_handle;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
    hvx_params.offset = gatts_value.offset;
    hvx_params.p_len  = &gatts_value.len;
    hvx_params.p_data = gatts_value.p_value;

    err_code  = sd_ble_gatts_hvx(p_tmp->conn_handle,&hvx_params);
    
  }
  else{
    err_code = NRF_ERROR_INVALID_STATE;
  }

  return  err_code;
 
}