#include "sleep_monirator_ble.h"
#include "sdk_common.h"
#include "ble_srv_common.h"

#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"

/* This code belongs in ble_cus.c*/

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void on_disconnect(ble_sleep_t *p_sleep, ble_evt_t const *p_ble_evt)
{
  UNUSED_PARAMETER(p_ble_evt);
  p_sleep->conn_handle = BLE_CONN_HANDLE_INVALID;

}

/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void on_connect(ble_sleep_t *p_sleep, ble_evt_t const *p_ble_evt)
{
  p_sleep->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

  ble_sleep_evt_t evt;

  evt.evt_type = BLE_CUS_EVT_CONNECTED;
  p_sleep->evt_handler(p_sleep,&evt);
}

static void on_write(ble_sleep_t *p_sleep, ble_evt_t const *p_ble_evt)
{
  ble_gatts_evt_write_t const *p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

      // Check if the handle passed with the event matches the Custom Value Characteristic handle.
  if (p_evt_write->handle == p_sleep->sleep_value_handle.value_handle)
    {
        // Put specific task here. 
        nrf_gpio_pin_toggle(LED_4);
    }
  // Check if the Custom value CCCD is written to and that the value is the appropriate length, i.e 2 bytes.
    if ((p_evt_write->handle == p_sleep->sleep_value_handle.cccd_handle)
        && (p_evt_write->len == 2)
       )
    {

        // CCCD written, call application event handler
        if (p_sleep->evt_handler != NULL)
        {
            ble_sleep_evt_t evt;

            if (ble_srv_is_notification_enabled(p_evt_write->data))
            {
                evt.evt_type = BLE_CUS_EVT_NOTIFICATION_ENABLED;
            }
            else
            {
                evt.evt_type = BLE_CUS_EVT_NOTIFICATION_DISABLED;
            }
            // Call the application event handler.
            p_sleep->evt_handler(p_sleep, &evt);
        }

}
void ble_sleep_on_evt(ble_evt_t const *p_event, void *p_context)
 {
    ble_sleep_t *p_sleep = (ble_sleep_t *)p_context;
    if(p_sleep == NULL || p_event == NULL)
    {
      return NRF_ERROR_NULL;
    }
    switch(p_event->header.evt_id)
    {
      case(BLE_GAP_EVT_CONNECTED):
        on_connect(p_sleep,p_event);

        break;
      case(BLE_GAP_EVT_DISCONNECTED):
        on_disconnect(p_sleep,p_event);
        break;
      case(BLE_GATTS_EVT_WRITE):
        on_write(p_sleep,p_event);
        break;
      default:
        break;
    }
 
 }
uint32_t ble_sleep_init(ble_sleep_t *p_sleep, const ble_sleep_init_t *p_sleep_init)\
{
  ret_code_t      err_code;
  ble_uuid_t      ble_uuid;
  ble_add_char_params_t add_char_params;
  
  if(p_sleep == NULL || p_sleep_init == NULL)
  {
    return NRF_ERROR_NULL;
  }

  p_sleep->conn_handle    = BLE_CONN_HANDLE_INVALID;
  p_sleep->evt_handler    = p_sleep_init->evt_handler;
  //Add Custom Service UUID
  BLE_UUID_BLE_ASSIGN(ble_uuid,SLEEP_SERVICE_UUID);
  err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_sleep->service_handle);
  if(err_code != NRF_SUCCESS)
  {
    return err_code;
  }
  //add Characteristic
  memset(&add_char_params,0,sizeof(add_char_params));
  add_char_params.uuid      = CUSTOM_SLEEP_VALUE_CHAR_UUID;
  add_char_params.uuid_type = p_sleep->uuid_type;
  add_char_params.max_len   = MAX_DATA_LEN;
  add_char_params.init_len  = MAX_DATA_LEN;
  add_char_params.is_var_len  = true;
  add_char_params.char_props.notify = 1;
  add_char_params.char_props.read   = 1;

  add_char_params.cccd_write_access = SEC_OPEN;
  add_char_params.read_access        = SEC_OPEN;
  err_code = characteristic_add(p_sleep->service_handle,&add_char_params,&p_sleep->sleep_value_handle);
  
    if(err_code!= NRF_SUCCESS)
  {
    return err_code;
  }
  return NRF_SUCCESS;
}}
 uint32_t ble_sleep_custom_value_update(ble_sleep_t * p_sleep, uint8_t custom_value)
 {
  if(p_sleep == NULL){
    return  NRF_ERROR_NULL;
  
  }

  ret_code_t err_code = NRF_SUCCESS;
  ble_gatts_value_t  gatts_value;

  memset(&gatts_value,0, sizeof(gatts_value));

  gatts_value.len = sizeof(uint8_t);
  gatts_value.offset = 0;
  gatts_value.p_value = &custom_value;

  err_code = sd_ble_gatts_value_set(p_sleep->conn_handle, p_sleep->sleep_value_handle.value_handle,&gatts_value);

  if(err_code != NRF_SUCCESS)
  {
    return  err_code;
  }
  // Send value if connected and notifying.
  if(p_sleep->conn_handle != BLE_CONN_HANDLE_INVALID)
  {
    ble_gatts_hvx_params_t hvx_params;

    memset(&hvx_params,0,sizeof(hvx_params));

    hvx_params.handle = p_sleep->sleep_value_handle.value_handle;
    hvx_params.offset = gatts_value.offset;
    hvx_params.p_data = gatts_value.p_value;
    hvx_params.p_len  = &gatts_value.len;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
    err_code = sd_ble_gatts_hvx(p_sleep->conn_handle,&hvx_params);
  
  
  
  
  }else{
    err_code = NRF_ERROR_INVALID_STATE;
  
  }
return err_code;

 
 }