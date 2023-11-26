#include "ble_app_sleep_dev.h"
uint32_t ble_dev_init(ble_dev_t *p_dev, ble_dev_init_t *p_init)
{
  ret_code_t err_code;
  ble_uuid_t ble_uuid;
  ble_add_char_params_t add_char_params;

  if(p_dev == NULL || p_init == NULL)
  {
    return NRF_ERROR_NULL;
  }
  //init struct service
  p_dev->conn_handle = BLE_CONN_HANDLE_INVALID;
  p_dev->is_sensor_supported = p_init->is_sensor_supported;
  p_dev->evt_handler         = p_init->evt_handler;

  //add service
  BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_APP_SLEEP_DEV_SERVICE_UUID);
  err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_dev->service_handle);
  VERIFY_SUCCESS(err_code);
  //ADD Sleep Measurement Char
  memset(&add_char_params,0,sizeof(add_char_params));
  add_char_params.uuid        = BLE_APP_SLEEP_DEV_SLEEP_CHAR_UUID;
  add_char_params.uuid_type   = p_dev->uuid_type;
  add_char_params.max_len     = MAX_DATA_SIZE;
  add_char_params.is_var_len  = true;
  add_char_params.init_len    =sizeof(uint8_t);
  add_char_params.p_init_value=NULL;

  add_char_params.char_props.notify = 1;
  add_char_params.cccd_write_access = SEC_OPEN;
  err_code = characteristic_add(p_dev->service_handle,&add_char_params,&p_dev->sleep_handle);
  if(err_code != NRF_SUCCESS)
  {
    return err_code;
  }
  memset(&add_char_params,0,sizeof(add_char_params));
  add_char_params.uuid        = BLE_APP_SLEEP_DEC_TEMPERATURE_CHAR_UUID;
  add_char_params.uuid_type   = p_dev->uuid_type;
  add_char_params.max_len     = MAX_DATA_SIZE;
  add_char_params.init_len    = sizeof(uint8_t);

  add_char_params.char_props.notify = 1;
  add_char_params.cccd_write_access = SEC_OPEN;
  err_code = characteristic_add(p_dev->service_handle,&add_char_params,&p_dev->temp_handle);
  if(err_code != NRF_SUCCESS)
  {
    return err_code;
  }
  return NRF_SUCCESS;

}
/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_dev_t *p_dev, ble_evt_t const *p_ble_evt)
{
  p_dev->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
  ble_dev_evt_t evt;
  evt.evt_type  = BLE_DEV_SLEEP_EVT_CONNECTED;
  p_dev->evt_handler(p_dev,&evt);

}
/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_dev_t *p_dev, ble_evt_t const *p_ble_evt)
 {
  UNUSED_PARAMETER(p_ble_evt);
  p_dev->conn_handle = BLE_CONN_HANDLE_INVALID;
  ble_dev_evt_t evt;
  evt.evt_type  = BLE_DEV_SLEEP_EVT_DISCONNECTED;
  p_dev->evt_handler(p_dev,&evt);
 }
/**@brief Function for handling the Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_dev_t *p_dev, ble_evt_t const *p_ble_evt)
 {
    ret_code_t err_code;
    ble_gatts_evt_write_t const *p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    if(p_evt_write->handle == p_dev->sleep_handle.value_handle)
    {
      // Do task here
    } 
 }
void ble_dev_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context)
{
  ret_code_t err_code;
  ble_dev_t *p_dev = (ble_dev_t *) p_context;
  if(p_ble_evt == NULL|| p_dev == NULL)
  {
    return;
  }
  switch(p_ble_evt->header.evt_id)
  {
    case BLE_GAP_EVT_CONNECTED:
        on_connect(p_dev,p_ble_evt);
    break;
    case BLE_GAP_EVT_DISCONNECTED:
        on_disconnect(p_dev,p_ble_evt);
    break;
    case BLE_GATTS_EVT_WRITE:
        on_write(p_dev,p_ble_evt);
    break;
    default:
    break;
  }
}

uint32_t ble_cus_value_update(ble_dev_t *p_dev, uint8_t cus_value);
uint32_t ble_sleep_value_update(ble_dev_t *p_dev, uint16_t sleep_value);
uint32_t ble_temp_value_update(ble_dev_t  *p_dev, uint16_t temp_value);