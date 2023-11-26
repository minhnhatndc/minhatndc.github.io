#include "ble_temp_c.h"

#include "nrf_log.h"

/**@brief Function for interception of the errors of GATTC and the BLE GATT Queue.
 *
 * @param[in] nrf_error   Error code.
 * @param[in] p_ctx       Parameter from the event handler.
 * @param[in] conn_handle Connection handle.
 */
static void gatt_error_handler(uint32_t nrf_error, void *p_ctx, uint16_t conn_handle)
{
  ble_temp_c_t * p_ble_tmp_c = (ble_temp_c_t *)p_ctx;

  NRF_LOG_DEBUG("A GATT Client error has occurred on conn_handle: 0X%X", conn_handle);
  if(p_ble_tmp_c->error_handler != NULL)
  {
    p_ble_tmp_c->error_handler(nrf_error);
  }
}


uint32_t ble_temp_c_init(ble_temp_c_t *p_ble_tmp_c, ble_temp_c_init_t *p_ble_tmp_c_initt)
{
  VERIFY_PARAM_NOT_NULL(p_ble_tmp_c);
  VERIFY_PARAM_NOT_NULL(p_ble_tmp_c_initt);
  //SERVICE UUID
  ble_uuid_t ble_uuid;
  
  ble_uuid.type     = BLE_UUID_TYPE_BLE;
  ble_uuid.uuid     = BLE_TEMP_C_SERVICE_UUID;
  
  // init structure Service
  p_ble_tmp_c->error_handler = p_ble_tmp_c_initt->error_handle;
  p_ble_tmp_c->evt_handler   = p_ble_tmp_c_initt->evt_handle;
  p_ble_tmp_c->p_gatt_queue  = p_ble_tmp_c_initt->p_gatt_queue;
  
  p_ble_tmp_c->conn_handle                  = BLE_CONN_HANDLE_INVALID;
  p_ble_tmp_c->peer_tmp_db.tmp_cccd_handle  = BLE_GATT_HANDLE_INVALID;
  p_ble_tmp_c->peer_tmp_db.tmp_handle       = BLE_GATT_HANDLE_INVALID;

  return ble_db_discovery_evt_register(&ble_uuid);
}
/**@brief     Function for handling Handle Value Notification received from the SoftDevice.
 *
 * @details   This function uses the Handle Value Notification received from the SoftDevice
 *            and checks whether it is a notification of the heart rate measurement from the peer. If
 *            it is, this function decodes the heart rate measurement and sends it to the
 *            application.
 *
 * @param[in] p_ble_hrs_c Pointer to the Heart Rate Client structure.
 * @param[in] p_ble_evt   Pointer to the BLE event received.
 */

static void on_hvx(ble_temp_c_t *p_ble_tmp,  ble_evt_t const *p_ble_evt)
{
  // Check if the event is on the link for this instance.
  if(p_ble_tmp->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
  {
    return;
  }
  NRF_LOG_INFO("Received HVX on link is correct");
 // Check if this is a temperature notification.
 if(p_ble_evt->evt.gattc_evt.params.hvx.handle == p_ble_tmp->peer_tmp_db.tmp_handle);
 {
 if(p_ble_evt->evt.gattc_evt.params.hvx.len == 1)
 {
  ble_temp_c_evt_t p_ble_tmp_evt;
  p_ble_tmp_evt.evt_type = BLE_TEMP_C_EVT_TEMP_NOTIFICATION;
  p_ble_tmp_evt.conn_handle = p_ble_evt->evt.gattc_evt.conn_handle;
  p_ble_tmp_evt.params.tmp.tmp_value  = p_ble_evt->evt.gattc_evt.params.hvx.data[0];
  
  p_ble_tmp->evt_handler(p_ble_tmp,&p_ble_tmp_evt);
  }
 }
 }

static void on_disconnect(ble_temp_c_t *p_ble_tmp_c, const ble_evt_t  *p_ble_evt)
{
  if(p_ble_tmp_c->conn_handle == p_ble_evt->evt.gattc_evt.conn_handle)
  {
    p_ble_tmp_c->conn_handle = BLE_CONN_HANDLE_INVALID;
    p_ble_tmp_c->peer_tmp_db.tmp_cccd_handle = BLE_GATT_HANDLE_INVALID;
    p_ble_tmp_c->peer_tmp_db.tmp_handle      = BLE_GATT_HANDLE_INVALID;
  } 

} 

 void ble_temp_c_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context)
 {
    ret_code_t err_code;
    ble_temp_c_t *p_ble_tmp_c = (ble_temp_c_t *) p_context;
    if(p_ble_evt == NULL || p_context == NULL)
    {
      return;
    }
    switch(p_ble_evt->header.evt_id)
    {
      case BLE_GATTC_EVT_HVX:
        on_hvx(p_ble_tmp_c,p_ble_evt);
      break;
      case BLE_GAP_EVT_DISCONNECTED:
        on_disconnect(p_ble_tmp_c,p_ble_evt);
      break;
    
    }
 
 }
 /**@brief Function for creating a message for writing to the CCCD.
 */
static uint32_t cccd_configure(ble_temp_c_t *p_ble_tmp_c,bool notification_enable)
{
  ret_code_t err_code;
  NRF_LOG_DEBUG("Configuring CCCD. CCCD Handle = %d, Connection Handle = %d",
                p_ble_tmp_c->peer_tmp_db.tmp_cccd_handle,
                p_ble_tmp_c->peer_tmp_db.tmp_handle);

  nrf_ble_gq_req_t tmp_c_req; // Request value;

  uint8_t cccd[BLE_CCCD_VALUE_LEN];
  uint16_t  cccd_val = notification_enable ? BLE_GATT_HVX_NOTIFICATION:0;

  cccd[0] = LSB_16(cccd_val);
  cccd[1] = MSB_16(cccd_val);
  
  memset(&tmp_c_req,0,sizeof(tmp_c_req));
  tmp_c_req.type          = NRF_BLE_GQ_REQ_GATTC_WRITE;
  tmp_c_req.error_handler.cb  = gatt_error_handler;
  tmp_c_req.error_handler.p_ctx = p_ble_tmp_c;

  tmp_c_req.params.gattc_write.handle = p_ble_tmp_c->peer_tmp_db.tmp_cccd_handle;
  tmp_c_req.params.gattc_write.len    = BLE_CCCD_VALUE_LEN;
  tmp_c_req.params.gattc_write.p_value = cccd;
  tmp_c_req.params.gattc_write.offset = 0;
  tmp_c_req.params.gattc_write.write_op = BLE_GATT_OP_WRITE_REQ;
  return nrf_ble_gq_item_add(p_ble_tmp_c->p_gatt_queue, &tmp_c_req,p_ble_tmp_c->conn_handle);

}

uint32_t ble_tmp_c_ble_notif_enable(ble_temp_c_t *p_ble_tmp_c){
 
 VERIFY_PARAM_NOT_NULL(p_ble_tmp_c);
 if(p_ble_tmp_c->conn_handle == BLE_CONN_HANDLE_INVALID)
 {
  return NRF_ERROR_INVALID_STATE;
 }
 return cccd_configure(p_ble_tmp_c,true);
 }


uint32_t ble_tmp_c_read(ble_temp_c_t *p_ble_tmp_c)
{
  ret_code_t err_code;
  VERIFY_PARAM_NOT_NULL(p_ble_tmp_c);
  if(p_ble_tmp_c->conn_handle == BLE_CONN_HANDLE_INVALID)
  {
    return NRF_ERROR_INVALID_STATE;
  }
  nrf_ble_gq_req_t tmp_c_req;
  memset(&tmp_c_req,0,sizeof(tmp_c_req));
  tmp_c_req.type   = NRF_BLE_GQ_REQ_GATTC_READ;
  tmp_c_req.error_handler.cb = gatt_error_handler;
  tmp_c_req.error_handler.p_ctx = p_ble_tmp_c;
  tmp_c_req.params.gattc_read.handle = p_ble_tmp_c->peer_tmp_db.tmp_handle;
  return nrf_ble_gq_item_add(p_ble_tmp_c->p_gatt_queue,&tmp_c_req,p_ble_tmp_c->conn_handle);
}



void ble_tmp_on_db_disc_evt(ble_temp_c_t *p_ble_tmp_c, ble_db_discovery_evt_t *p_evt)
{
  ret_code_t err_code;
  //Check if the Service was discovered.
  if((p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE) 
      &&(p_evt->params.discovered_db.srv_uuid.uuid == BLE_TEMP_C_SERVICE_UUID)
      &&(p_evt->params.discovered_db.srv_uuid.type == BLE_UUID_TYPE_BLE))
    {
      // Fine the CCCD handle of Temp Level Characteristic.
      uint8_t i;
      ble_temp_c_evt_t evt;
      evt.evt_type      = BLE_TEMP_C_EVT_DISCOVERY_COMPLETED;
      evt.conn_handle   = p_evt->conn_handle;

      for(i= 0; i<p_evt->params.discovered_db.char_count;i++)
      {
        if(p_evt->params.discovered_db.charateristics[i].characteristic.uuid.uuid == BLE_TEMP_C_CHAR_UUID)
        {
          //Found Temp Characteristic UUID. Store CCCD Handle and break;
          evt.params.peer_db.tmp_cccd_handle=
              p_evt->params.discovered_db.charateristics[i].cccd_handle;
          evt.params.peer_db.tmp_handle =
              p_evt->params.discovered_db.charateristics[i].characteristic.handle_value;
          break;
        }
      }
      NRF_LOG_DEBUG("Service and Characteristic discovered at peer");
      //If the instance has been assigned prior to db_discovery, assign the db_handles.
      if(p_ble_tmp_c->conn_handle != BLE_CONN_HANDLE_INVALID)
      {
        if((p_ble_tmp_c->peer_tmp_db.tmp_cccd_handle == BLE_GATT_HANDLE_INVALID)
            &&(p_ble_tmp_c->peer_tmp_db.tmp_handle  == BLE_GATT_HANDLE_INVALID))
            {
              p_ble_tmp_c->peer_tmp_db = evt.params.peer_db;
            }
      }
      p_ble_tmp_c->evt_handler(p_ble_tmp_c,&evt);  
      
    }
    else if((p_evt->evt_type == BLE_DB_DISCOVERY_SRV_NOT_FOUND)
         &&(p_evt->evt_type == BLE_DB_DISCOVERY_ERROR))
         {
          NRF_LOG_DEBUG("Service discovery failure at peer")
         }
    else{
      // Do nothing
    }
}
 uint32_t ble_tmp_c_handles_assign(ble_temp_c_t *p_ble_tmp_c, uint16_t conn_handle, tmp_db_t *p_peer_handle)
 {
  VERIFY_PARAM_NOT_NULL(p_ble_tmp_c);
  p_ble_tmp_c->conn_handle = conn_handle;
  if(p_peer_handle != NULL)
  {
    p_ble_tmp_c->peer_tmp_db = *p_peer_handle;
  }
  return nrf_ble_gq_conn_handle_register(p_ble_tmp_c->p_gatt_queue,conn_handle);
 }
