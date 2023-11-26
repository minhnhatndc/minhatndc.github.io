#include "ble_app_sleep.h"
static uint8_t encode_temp_value(ble_sleep_t *p_sleep, uint16_t temp_value, uint8_t *p_buffer)
{ uint8_t flag = 0;
  uint8_t len = 1;
  int i;
  if(p_sleep->is_sensor_temp_contact_supported)
  {
    flag |= FLAG_MASK_SENSOR_CONTACT_SUPPORTED;
  }
  if(temp_value > 0xFF)
  {
    flag |= FLAG_MASK_VALUE_16BIT;
    len+= uint16_encode(temp_value,&p_buffer[len]);
  }
  else{
    p_buffer[len++]= (uint8_t) temp_value;
  }
  p_buffer[0]= flag;
  return  len;

}
static uint8_t encode_value(ble_sleep_t *p_sleep, uint16_t sleep_value, uint8_t *p_buffer)
{
  uint8_t flag = 0; //0x00
  uint8_t len  = 1;
  int i;

  if(p_sleep->is_sensor_temp_contact_supported)
  {
    flag|= FLAG_MASK_SENSOR_CONTACT_SUPPORTED;
  }
  if(p_sleep->is_sensor_temp_contact_detected)
  {
    flag |= FLAG_MASK_SENSOR_CONTACT_DETECTED;
  }
  
  if ( sleep_value > 0xFF)
  {
    flag |= FLAG_MASK_VALUE_16BIT;
    len += uint16_encode(sleep_value, &p_buffer[len]);
  }
  else
  {
    p_buffer[len++] = (uint8_t)sleep_value;
  }
  p_buffer[0] = flag;
  return len;


}
uint32_t ble_sleep_init(ble_sleep_t *p_sleep,const ble_sleep_init_t *p_init)
{
  
  uint8_t encode_buffer[MAX_DATA_LEN];
  uint8_t encoded_temp_buffer[MAX_DATA_LEN];

  if(p_sleep == NULL || p_init == NULL)
  {
    return  NRF_ERROR_NULL;
  }
  p_sleep->conn_handle = BLE_CONN_HANDLE_INVALID;
  p_sleep->evt_handler = p_init->evt_handler;

  ret_code_t err_code;
  ble_uuid_t ble_uuid;
  ble_add_char_params_t add_char_params;

  BLE_UUID_BLE_ASSIGN(ble_uuid,BLE_APP_SLEEP_SERVICE_UUID);
  err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_sleep->service_handle);
  if(err_code != NRF_SUCCESS)
  {
    return err_code;
  }
  memset(&add_char_params,0,sizeof(add_char_params));
  add_char_params.uuid      = BLE_APP_SLEEP_CHAR_UUID;
  add_char_params.uuid_type = p_sleep->uuid_type;
  add_char_params.max_len   = MAX_DATA_LEN;
  add_char_params.init_len  = encode_value(p_sleep,0,encode_buffer);//sizeof(uint8_t);
  add_char_params.p_init_value = encode_buffer;
  add_char_params.is_var_len   = true;
  
  add_char_params.char_props.notify = 1;
  add_char_params.cccd_write_access = SEC_OPEN;
  err_code = characteristic_add(p_sleep->service_handle,&add_char_params,&p_sleep->sleep_handle);
  if(err_code != NRF_SUCCESS)
  {
    return  err_code;
  }
  memset(&add_char_params,0,sizeof(add_char_params));
  add_char_params.uuid    = BLE_APP_TEMPERATURE_CHAR_UUID;
  add_char_params.uuid_type = p_sleep->uuid_type;
  add_char_params.max_len =  MAX_DATA_LEN;
  add_char_params.init_len = encode_temp_value(p_sleep,0,encoded_temp_buffer);
  add_char_params.p_init_value= encoded_temp_buffer;
  add_char_params.is_var_len  = true;
  add_char_params.char_props.notify= 1;
  add_char_params.char_props.read = 1;

  add_char_params.cccd_write_access= SEC_OPEN;
  add_char_params.read_access = SEC_OPEN;
  err_code = characteristic_add(p_sleep->service_handle,&add_char_params,&p_sleep->temp_handle);
  if(err_code!= NRF_SUCCESS)
  {
    return err_code;
  }
  return NRF_SUCCESS;

}
static void on_connect(ble_sleep_t *p_sleep, ble_evt_t const *p_ble_evt)
{
  p_sleep->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
  ble_sleep_evt_t evt;
  evt.evt_type = BLE_SLEEP_EVT_CONNECTED;
  p_sleep->evt_handler(p_sleep,&evt);
}
static void on_diconnect(ble_sleep_t *p_sleep, ble_evt_t const *p_ble_evt)
{
  UNUSED_PARAMETER(p_ble_evt);
  p_sleep->conn_handle = BLE_CONN_HANDLE_INVALID;
  ble_sleep_evt_t evt;
  evt.evt_type = BLE_SLEEP_EVT_DISCONNECTED;
  p_sleep->evt_handler(p_sleep,&evt);
}
static void on_write(ble_sleep_t *p_sleep, ble_evt_t const * p_ble_evt)
{
  ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
  // Check if the handle passed with the event matches the Custom Value Characteristic handle.
  if(p_evt_write->handle == p_sleep->sleep_handle.value_handle)
  {
    NRF_LOG_INFO("Write CCCD success");
  }
  if(p_evt_write->handle == p_sleep->sleep_handle.cccd_handle &&
    p_evt_write->len     == 2)
    {
      if(p_sleep->evt_handler != NULL)
      {
        ble_sleep_evt_t evt;
        if(ble_srv_is_notification_enabled(p_evt_write->data))
        {
          evt.evt_type = BLE_SLEEP_EVT_NOTIFICATION_ENABLED;
        }
        else{
          evt.evt_type = BLE_SLEEP_EVT_NOTIFICATION_DISABLED;
        }
        p_sleep->evt_handler(p_sleep,&evt);
      }
    
    }

}
void     ble_sleep_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
{
  ble_sleep_t *p_sleep = (ble_sleep_t *) p_context;

  if(p_ble_evt == NULL || p_sleep == NULL)
  {
    return NRF_ERROR_NULL;
  }
  switch(p_ble_evt->header.evt_id)
  {
    case BLE_GAP_EVT_CONNECTED:
        on_connect(p_sleep, p_ble_evt);
    break;
    case BLE_GAP_EVT_DISCONNECTED:
        on_diconnect(p_sleep,p_ble_evt);
    break;
    case BLE_GATTS_EVT_WRITE:
        on_write(p_sleep,p_ble_evt);
    break;
    default:
    break;
  
  }

}

uint32_t ble_sleep_value_update(ble_sleep_t *p_sleep, uint8_t value)
{
  ret_code_t err_code;
  if(p_sleep == NULL) return  NRF_ERROR_NULL;

  ble_gatts_value_t gatts_value;
  memset(&gatts_value,0,sizeof(gatts_value));
  gatts_value.len       = sizeof(uint16_t);
  gatts_value.offset    = 0;
  gatts_value.p_value   = &value;

  err_code= sd_ble_gatts_value_set(p_sleep->conn_handle,p_sleep->sleep_handle.value_handle,&gatts_value);
  VERIFY_SUCCESS(err_code);

  if(p_sleep->conn_handle != BLE_CONN_HANDLE_INVALID)
  {
    ble_gatts_hvx_params_t hvx_params;
    memset(&hvx_params,0,sizeof(hvx_params));
    hvx_params.handle = p_sleep->sleep_handle.value_handle;
    hvx_params.offset = gatts_value.offset;
    hvx_params.p_data = gatts_value.p_value;
    hvx_params.p_len  = &gatts_value.len;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;

    err_code = sd_ble_gatts_hvx(p_sleep->conn_handle,&hvx_params);
    VERIFY_SUCCESS(err_code);

    return  NRF_SUCCESS;
  }
}
uint32_t ble_value_update(ble_sleep_t *p_sleep, uint16_t val)
{
  ret_code_t err_code;
  if(p_sleep->conn_handle != BLE_CONN_HANDLE_INVALID)
  {
    uint8_t ecoded_value[MAX_DATA_LEN];
    uint16_t len;
    uint16_t hvx_len;
    ble_gatts_hvx_params_t hvx_params;

    len = encode_value(p_sleep,val,ecoded_value);
    hvx_len = len;
    memset(&hvx_params,0,sizeof(hvx_params));
    hvx_params.handle= p_sleep->sleep_handle.value_handle;
    hvx_params.type = BLE_GATT_HVX_NOTIFICATION;
    hvx_params.offset = 0;
    hvx_params.p_len = &hvx_len;
    hvx_params.p_data = ecoded_value;

    err_code= sd_ble_gatts_hvx(p_sleep->conn_handle,&hvx_params);
    VERIFY_SUCCESS(err_code);
  
  }
  else{
      err_code = NRF_ERROR_INVALID_STATE;
  }
  return  err_code;
}
uint32_t ble_tmp_value_update(ble_sleep_t *p_sleep, uint16_t tmp_val)
{
  ret_code_t err_code;
  if(p_sleep->conn_handle != BLE_CONN_HANDLE_INVALID)
  {
    uint8_t encoded_temp_value[MAX_DATA_LEN];
    uint16_t len;
    uint16_t hvx_len;
    ble_gatts_hvx_params_t hvx_params;
    len = encode_temp_value(p_sleep,tmp_val,encoded_temp_value);
    hvx_len=len;
    memset(&hvx_params,0,sizeof(hvx_params));
    hvx_params.handle = p_sleep->temp_handle.value_handle;
    hvx_params.offset =0;
    hvx_params.p_data = encoded_temp_value;
    hvx_params.p_len  = &hvx_len;
    hvx_params.type = BLE_GATT_HVX_NOTIFICATION;
    err_code = sd_ble_gatts_hvx(p_sleep->conn_handle,&hvx_params);
    VERIFY_SUCCESS(err_code);

  }
  else{
    err_code= NRF_ERROR_INVALID_STATE;
  }
  return  err_code;
}