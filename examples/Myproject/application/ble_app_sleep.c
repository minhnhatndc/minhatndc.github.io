#include "ble_app_sleep1.h"
static uint8_t encode_value(ble_sleep_t *p_sleep, uint16_t value, uint8_t *p_buffer)
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
  
  if ( value > 0xFF)
  {
    flag |= FLAG_MASK_VALUE_16BIT;
    len += uint16_encode(value, &p_buffer[len]);
  }
  else
  {
    p_buffer[len++] = (uint8_t)value;
  }
  p_buffer[0] = flag;
  return len;


}
uint32_t ble_sleep_init(ble_sleep_t *p_sleep,const ble_sleep_init_t *p_init)
{
  NRF_LOG_INFO("Service init");
  if(p_sleep == NULL || p_init == NULL)
  {
    return  NRF_ERROR_NULL;
  }
  p_sleep->conn_handle = BLE_CONN_HANDLE_INVALID;
  
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
  add_char_params.max_len   = sizeof(uint8_t);
  add_char_params.init_len  = sizeof(uint8_t);
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
  add_char_params.max_len = sizeof(uint8_t);
  add_char_params.init_len = sizeof(uint8_t);

  add_char_params.char_props.read = 1;;
  add_char_params.read_access = SEC_OPEN;
  err_code = characteristic_add(p_sleep->service_handle,&add_char_params,&p_sleep->temp_value);
  if(err_code!= NRF_SUCCESS)
  {
    return err_code;
  }
  return NRF_SUCCESS;

}
int main()
{
printf("Hello");

return 0;
}
