#include "ble_heart.h"
static uint32_t ble_heart_value_char_add(ble_heart_t *p_hrs, const ble_heart_init_t * p_hrs_init);
static void on_connect(ble_heart_t *p_hrs, ble_evt_t const *p_ble_evt)
{
  p_hrs->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
  ble_heart_evt_t evt;
  evt.evt_type = BLE_HEART_EVT_CONNECTED;
  p_hrs->evt_handler(p_hrs,&evt);

}
static void on_disconnect(ble_heart_t *p_hrs, ble_evt_t const *p_ble_evt)
{
  UNUSED_PARAMETER(p_ble_evt);
  p_hrs->conn_handle = BLE_CONN_HANDLE_INVALID;

}
/*
Now, once we get the Write event we have to get hold of the Write event parameters 
that are passed with the event and we have to verify that the the handle 
that is written to matches the Custom Value Characteristic handle, i.e.
*/
static void on_write(ble_heart_t *p_hrs, ble_evt_t const *p_ble_evt)
{
  ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
  if(p_evt_write->handle == p_hrs->heart_value_handles.value_handle)
  {
    // Put specific task here
    //nrf_gpio_pin_toggle(leds);
  }
  // Check if the Custom value CCCD is written to and that the value is the appropriate length, i.e 2 bytes.
  if((p_evt_write->handle == p_hrs->heart_value_handles.cccd_handle) && (p_evt_write->len == 2))
    {
      if(p_hrs->evt_handler != NULL)
        {
          ble_heart_evt_t evt;
          if(ble_srv_is_notification_enabled(p_evt_write->data))
            {
              evt.evt_type = BLE_HEART_NOTIFICATION_ENABLE;
            }
          else{
              evt.evt_type = BLE_HEART_NOTIFICATION_DISABLE;
            }
             // Call the application event handler.
            p_hrs->evt_handler(p_hrs,&evt);
        }
    }

}
uint32_t ble_heart_init(ble_heart_t * p_hrs, ble_heart_init_t *p_hrs_init)
{
    ret_code_t err_code;
    ble_uuid_t ble_uuid;
    ble_uuid128_t base_uuid = BLE_HEART_BASE_UUID;

    if((p_hrs == NULL) || (p_hrs_init == NULL))
        {
            return NRF_ERROR_NULL;
        }
    
    // Initialize service structure
    p_hrs->evt_handler = p_hrs_init->evt_handler;
    p_hrs->conn_handle = BLE_CONN_HANDLE_INVALID;



    // Add Custom Service UUID
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_hrs->uuid_type);
    if(err_code != NRF_SUCCESS)
      {
        return err_code;
      }

    ble_uuid.type = p_hrs->uuid_type;
    ble_uuid.uuid = BLE_HEART_SERVICE_UUID;
 /*
 We're almost done, the last thing we have to do is to add the Custom Service decleration to the BLE Stack's GATT table.
 */   
    // Add the Custom Service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid,&p_hrs->service_handle);
    if(err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    // Add  Characteristic

    return  ble_heart_value_char_add(p_hrs,p_hrs_init);

}
static uint32_t ble_heart_value_char_add(ble_heart_t *p_hrs, const ble_heart_init_t * p_hrs_init)
{
  ret_code_t err_code;
  ble_gatts_char_md_t char_md;
  ble_gatts_attr_md_t cccd_md;
  ble_gatts_attr_t    attr_char_value;
  ble_uuid_t          ble_uuid;
  ble_gatts_attr_md_t attr_md;
  memset(&cccd_md,0,sizeof(cccd_md));
  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
  cccd_md.vloc = BLE_GATTS_VLOC_STACK;

  memset(&char_md, 0, sizeof(char_md));

  char_md.char_props.read = 1;
  char_md.char_props.write = 1;
  char_md.char_props.notify = 0;
  char_md.p_char_user_desc = NULL;
  char_md.p_char_pf = NULL;
  char_md.p_cccd_md = NULL;
  char_md.p_sccd_md = NULL;
  char_md.char_props.notify = 1;

  char_md.p_cccd_md = &cccd_md;
  memset(&attr_md,0,sizeof(attr_md));
  attr_md.read_perm = p_hrs_init->ble_heart_value_char_attr_md.read_perm;
  attr_md.write_perm = p_hrs_init->ble_heart_value_char_attr_md.write_perm;
  attr_md.vloc    = BLE_GATTS_VLOC_STACK;
  attr_md.wr_auth = 0;
  attr_md.vlen = 0;

  ble_uuid.type = p_hrs->uuid_type;
  ble_uuid.uuid = BLE_HEART_VALUE_CHAR_UUID;
  


  memset(&attr_char_value,0,sizeof(attr_char_value));
  attr_char_value.p_uuid = &ble_uuid;
  attr_char_value.p_attr_md = &attr_md;
  attr_char_value.init_len = sizeof(uint8_t);
  attr_char_value.init_offs = 0;
  attr_char_value.max_len = sizeof(uint8_t);
  // Add cus characteristics
  err_code = sd_ble_gatts_characteristic_add(p_hrs->service_handle,&char_md,&attr_char_value,&p_hrs->heart_value_handles);
  if(err_code != NRF_SUCCESS)
    {
      return err_code;
    }
  return NRF_SUCCESS;
}

void ble_heart_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
  ble_heart_t *p_hrs = (ble_heart_t *)p_context;
  if( p_hrs == NULL || p_ble_evt == NULL)
      {
        return;
      }
  switch(p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
          on_connect(p_hrs,p_ble_evt);
          break;
        case BLE_GAP_EVT_DISCONNECTED:
          on_disconnect(p_hrs,p_ble_evt);
          break;
        case BLE_GATTS_EVT_WRITE:
          on_write(p_hrs,p_ble_evt);
          break;
        default:
          break;
    
    }
  
}
uint32_t ble_heart_custom_value_update(ble_heart_t *p_hrs, uint8_t hrs_value)
{  
  NRF_LOG_INFO("In ble_cus_custom_value_update. \r\n"); 
  if(p_hrs == NULL)
    {
      return NRF_ERROR_NULL;
    }
 /*
 Next, we're going to update the value in the GATT table with our custom_value 
 that we passed as an argument to the ble_cus_custom_value_update() function.
 */
 ret_code_t err_code = NRF_SUCCESS;
 ble_gatts_value_t  gatts_value;
 //// Initialize value struct.
 memset(&gatts_value,0,sizeof(gatts_value));
 gatts_value.len = sizeof(uint8_t);
 gatts_value.offset = 0;
 gatts_value.p_value = &hrs_value;
 err_code = sd_ble_gatts_value_set(p_hrs->conn_handle,
                                   p_hrs->heart_value_handles.value_handle,
                                   &gatts_value);
 if( err_code != NRF_SUCCESS)
  { 
    return  err_code;
  }
/*
After updating the value in the GATT table 
we're ready to notify our peer that the value of our Custom Value Characteristic has changed.
*/
if((p_hrs->conn_handle != BLE_CONN_HANDLE_INVALID))
  {
    ble_gatts_hvx_params_t hvx_params;
    memset(&hvx_params,0,sizeof(hvx_params));
    hvx_params.handle = p_hrs->heart_value_handles.value_handle;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
    hvx_params.offset = gatts_value.offset;
    hvx_params.p_len  = &gatts_value.len;
    hvx_params.p_data = gatts_value.p_value;
    err_code = sd_ble_gatts_hvx(p_hrs->conn_handle,&hvx_params);
  }
  else{
    err_code = NRF_ERROR_INVALID_STATE;
  }
  return  err_code;
}