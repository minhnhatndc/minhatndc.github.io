#include "ble_sleep.h"
#include "sdk_common.h"
#include "boards.h"
#include "nrf_log.h"
static uint32_t add_value_char_add(ble_sleep_t *p_sleep, ble_sleep_init_t *p_init);
/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_sleep_t *p_sleep, ble_evt_t const *p_ble_evt)
{
  p_sleep->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
  ble_sleep_evt_t evt;
  evt.evt_type = BLE_SLEEP_EVT_CONNECTED;
  p_sleep->evt_handler(p_sleep,&evt);
}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_sleep_t *p_sleep, ble_evt_t *p_ble_evt)
{
  UNUSED_PARAMETER(p_ble_evt);
  p_sleep->conn_handle = BLE_CONN_HANDLE_INVALID;
}
/**@brief Function for handling the Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
 static void on_write(ble_sleep_t *p_sleep, ble_evt_t const *p_ble_evt)
 {/*
 Now, once we get the Write event we have to get hold of the Write event parameters 
 that are passed with the event and we have to verify that the the handle 
 that is written to matches the Custom Value Characteristic handle, i.e.*/
  ble_gatts_evt_write_t *p_write_evt = &p_ble_evt->evt.gatts_evt.params.write;

  if(p_write_evt->handle == p_sleep->sleep_value_handles.value_handle)
  {
    //Do something
  }
 if((p_write_evt->handle == p_sleep->sleep_value_handles.cccd_handle)
                            &&(p_write_evt->len == 2))
  {
    // CCCD written, call application event handler
       if(p_sleep->evt_handler == NULL)
       {
        ble_sleep_evt_t evt;
        if(ble_srv_is_notification_enabled(p_write_evt->data))
          {
            evt.evt_type = BLE_CUS_EVT_NOTIFICATION_ENABLED;
          }
       else{
            evt.evt_type = BLE_CUS_EVT_NOTIFICATION_DISABLED;
            }
        p_sleep->evt_handler(p_sleep,&evt);// Call the application event handler.
       }    
  }
 }

 uint32_t ble_sleep_init(ble_sleep_t *p_sleep, ble_sleep_init_t *p_sleep_init)
 {
   ret_code_t err_code;
   ble_uuid_t ble_uuid;
   ble_add_char_params_t add_char_params; 

   if(p_sleep == NULL || p_sleep_init == NULL)
    {
      return NRF_ERROR_NULL;
    }
    // Initialize service structure
    p_sleep->conn_handle = BLE_CONN_HANDLE_INVALID;
    p_sleep->evt_handler = p_sleep_init->evt_handler;
    //ADD Service UUID
    BLE_UUID_BLE_ASSIGN(ble_uuid, SLEEP_SERVICE_UUID);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_sleep->service_handle);
    
     if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    //ADD Characteristic
   
    memset(&add_char_params,0, sizeof(add_char_params));
    add_char_params.uuid      = SLEEP_MEASURE_VALUE_CHAR_UUID;
    add_char_params.uuid_type= p_sleep->uuid_type;
    add_char_params.max_len   = MAX_DATA_LEN;
    add_char_params.init_len  = sizeof(uint8_t);
    add_char_params.is_var_len= true;
    add_char_params.char_props.notify = 1;

    add_char_params.read_access = SEC_OPEN;
    add_char_params.cccd_write_access = SEC_OPEN;// cai dong nay can phai co a nha

    err_code= characteristic_add(p_sleep->service_handle, &add_char_params, &(p_sleep->sleep_value_handles));
    if(err_code != NRF_SUCCESS)
    {
        return err_code;
    }
     return NRF_SUCCESS;
 }
  void ble_sleep_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context)
  {
    ble_sleep_t *p_sleep = (ble_sleep_t *) p_context;
    if(p_sleep == NULL || p_ble_evt == NULL);
    {
      return;

    } 
    switch(p_ble_evt->header.evt_id)
      {
          case BLE_GAP_EVT_CONNECTED:
            on_connect(p_sleep,p_ble_evt);
          break;
          case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_sleep, p_ble_evt);
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
    
    NRF_LOG_INFO("In ble_cus_custom_value_update. \r\n"); 
    ret_code_t err_code;
    if(p_sleep == NULL)
    {
      return NRF_ERROR_NULL;
    }
/*
Next, we're going to update the value in the GATT table with our custom_value 
that we passed as an argument to the ble_cus_custom_value_update() function.
*/
    ble_gatts_value_t gatts_value;
    // Initialize value struct.
    memset(&gatts_value,0,sizeof(gatts_value));
    gatts_value.len = sizeof(uint8_t);
    gatts_value.offset = 0;
    gatts_value.p_value = &value;
     // Update database.
    err_code = sd_ble_gatts_value_set(p_sleep->conn_handle,p_sleep->sleep_value_handles.value_handle,&gatts_value);
    VERIFY_SUCCESS(err_code);
/*
After updating the value in the GATT table we're ready to notify our peer 
that the value of our Custom Value Characteristic has changed.
*/
// Send value if connected and notifying.
    if((p_sleep->conn_handle != BLE_CONN_HANDLE_INVALID))
    {
        ble_gatts_hvx_params_t hvx_params;
        memset(&hvx_params,0,sizeof(hvx_params));
        hvx_params.handle = p_sleep->sleep_value_handles.value_handle;
        hvx_params.type = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.p_len = &gatts_value.len;
        hvx_params.offset = gatts_value.offset;
        hvx_params.p_data= gatts_value.p_value;
        err_code = sd_ble_gatts_hvx(p_sleep->conn_handle,&hvx_params);
    
    }
    else{
      err_code = NRF_ERROR_INVALID_STATE;
    
    }
    return  err_code;

 }
/*
The first thing we should do is to verify that we have a valid connection handle, 
i.e. that we're actually connected to a peer, if not we should return an error indicating 
that we're in an invalid state. Next, we set the ble_gatts_hvx_params_t, which contains the handle of custom value attribute, 
the type(i.e. if its a Notification or Indication), the value offsett( only used if its larger than 20bytes), the length and the data. 
After setting the hvx_params, we notify the peer by calling sd_ble_gatts_hvx(). Lastly, we should return the error code.

*/



 //======================= TEST====================================================
 static uint32_t add_value_char_add(ble_sleep_t *p_sleep, ble_sleep_init_t *p_init)
 {
  ret_code_t              err_code;
  ble_gatts_char_md_t     char_md;
  ble_gatts_attr_md_t     cccd_md;
  ble_gatts_attr_t        attr_char_value;
  ble_uuid_t              ble_uuid;
  ble_gatts_attr_md_t     attr_md;
  
  memset(&char_md,0, sizeof(char_md));
  char_md.char_props.read   = 1;
  char_md.char_props.notify = 1;
  char_md.p_char_user_desc  = NULL;
  char_md.p_char_pf         = NULL;
  char_md.p_user_desc_md    = NULL;
  char_md.p_cccd_md         = NULL; 
  char_md.p_sccd_md         = NULL;
  
  memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_init->sleep_value_char_attr_md.read_perm;
    attr_md.write_perm = p_init->sleep_value_char_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    ble_uuid.type = p_sleep->uuid_type;
    ble_uuid.uuid = SLEEP_MEASURE_VALUE_CHAR_UUID;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(uint8_t);

    err_code =sd_ble_gatts_characteristic_add(p_sleep->service_handle,&char_md,&attr_char_value,&p_sleep->sleep_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
 
 }
