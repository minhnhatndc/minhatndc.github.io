#include "ble_app_c.h"
#include "nrf_log.h"
#define NRF_LOG_MODULE_NAME ble_app_c
NRF_LOG_MODULE_REGISTER();

#define TMP_FLAG_MASK_16BIT (0x01 << 0)/**< Bit mask used to extract the type of heart rate value. This is used to find if the received heart rate is a 16 bit value or an 8 bit value. */
#define TMP_FLAG_MASK_TMP_RR_INT (0x01 << 4) /**< Bit mask used to extract the presence of RR_INTERVALS. This is used to find if the received measurement includes RR_INTERVALS. */

uint32_t ble_app_c_init(ble_app_c_t *p_app, ble_app_c_init_t *p_init)
 {
  ret_code_t err_code;
  if(p_app == NULL || p_init == NULL)
  {
    return NRF_ERROR_NULL;
  }
  ble_uuid_t  ble_uuid;
  ble_uuid.type = BLE_UUID_TYPE_BLE;
  ble_uuid.uuid = BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE;
  p_app->evt_handler =  p_init->evt_handler;
  p_app->error_handler  = p_init->error_handler;
  p_app->p_gatt_queue = p_init->p_gatt_queue;

  p_app->conn_handle  = BLE_CONN_HANDLE_INVALID;
  p_app->peer_tmp_db.tmp_cccd_handle  = BLE_GATT_HANDLE_INVALID;
  p_app->peer_tmp_db.tmp_handle       = BLE_GATT_HANDLE_INVALID;
  return  ble_db_discovery_evt_register(&ble_uuid);
 
 }
 static void on_hvx(ble_app_c_t *p_ble_tmp_c, const ble_evt_t *p_evt)
 {
  // Check if the event is the link for this instance
  if(p_ble_tmp_c->conn_handle != p_evt->evt.gattc_evt.conn_handle)
  {
    NRF_LOG_DEBUG("Received HVX on link 0x%x, not associated to this instance. Ignore.",
                  p_evt->evt.gattc_evt.conn_handle);
    return;
  }
  NRF_LOG_DEBUG("Received HVX on link 0x%x, tmp_handle 0x%x",
                p_evt->evt.gattc_evt.params.hvx.handle,
                p_ble_tmp_c->peer_tmp_db.tmp_handle);
   //Check if this is a temp notification
   if(p_evt->evt.gattc_evt.params.hvx.handle == p_ble_tmp_c->peer_tmp_db.tmp_handle)
   {
      ble_app_c_evt_t ble_tmp_c_evt;
      uint32_t index = 0;
      ble_tmp_c_evt.evt_type = BLE_APP_C_EVT_DISCOVERY_COMPLETE;
      ble_tmp_c_evt.conn_handle   = p_ble_tmp_c->conn_handle;
      ble_tmp_c_evt.params.tmp.tmp_value   = 0;
      if((p_evt->evt.gattc_evt.params.hvx.data[index++] & TMP_FLAG_MASK_16BIT))
      { 
          // 8-bit Temp value received.
          ble_tmp_c_evt.params.tmp.tmp_value = p_evt->evt.gattc_evt.params.hvx.data[index++];//lint !e415 suppress Lint Warning 415: Likely access out of bond
      }
      else{
        ble_tmp_c_evt.params.tmp.tmp_value= uint16_decode(&(p_evt->evt.gattc_evt.params.hvx.data[index]));
        index += sizeof(uint16_t);
      }
      p_ble_tmp_c->evt_handler(p_ble_tmp_c,&ble_tmp_c_evt);
   
   }
  
 }
 /**@brief Function for interception of the errors of GATTC and the BLE GATT Queue.
 *
 * @param[in] nrf_error   Error code.
 * @param[in] p_ctx       Parameter from the event handler.
 * @param[in] conn_handle Connection handle.
 */
static void gatt_error_handler(uint32_t nrf_error, void *p_ctx, uint16_t conn_handle)
{
  ble_app_c_t *p_ble_app_c  = (ble_app_c_t *)p_ctx;
  if(p_ble_app_c->error_handler != NULL)
  {
    p_ble_app_c->error_handler(nrf_error);
  }
}
/**@brief     Function for handling Disconnected event received from the SoftDevice.
 *
 * @details   This function checks whether the disconnect event is happening on the link
 *            associated with the current instance of the module. If the event is happening, the function sets the instance's
 *            conn_handle to invalid.
 *
 * @param[in] p_ble_hrs_c Pointer to the Heart Rate Client structure.
 * @param[in] p_ble_evt   Pointer to the BLE event received.
 */
 static void on_disconnect(ble_app_c_t *p_app, const ble_evt_t *p_ble_evt)
 {
  if(p_app->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
  {
    p_app->conn_handle  = BLE_CONN_HANDLE_INVALID;
    p_app->peer_tmp_db.tmp_cccd_handle  = BLE_GATT_HANDLE_INVALID;
    p_app->peer_tmp_db.tmp_handle       = BLE_GATT_HANDLE_INVALID;
  
  }
 }

  void ble_app_c_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context)
  {
  ble_app_c_t *p_ble_app_c  = (ble_app_c_t *) p_context;
  if(p_ble_evt == NULL || p_ble_app_c == NULL) return;

  switch(p_ble_evt->header.evt_id)
  {
    case BLE_GATTC_EVT_HVX:
    on_hvx(p_ble_app_c,p_ble_evt);

    break;
    case BLE_GAP_EVT_DISCONNECTED:
      on_disconnect(p_ble_app_c, p_ble_evt);
    break;
  }
  }
static uint32_t cccd_configure(ble_app_c_t *p_ble_app_c, bool enable)
{
  nrf_ble_gq_req_t  tmp_c_req;
  uint8_t cccd[BLE_CCCD_VALUE_LEN];
  uint16_t cccd_val = enable ? BLE_GATT_HVX_NOTIFICATION : 0;
  cccd[0] = LSB_16(cccd_val);
  cccd[1] = MSB_16(cccd_val);
  memset(&tmp_c_req,0,sizeof(tmp_c_req));
  tmp_c_req.type    = NRF_BLE_GQ_REQ_GATTC_WRITE;
  tmp_c_req.error_handler.cb  = gatt_error_handler;
  tmp_c_req.error_handler.p_ctx = p_ble_app_c;
  tmp_c_req.params.gattc_write.handle = p_ble_app_c->peer_tmp_db.tmp_handle;
  tmp_c_req.params.gattc_write.len  = BLE_CCCD_VALUE_LEN;
  tmp_c_req.params.gattc_write.p_value  = cccd;
  tmp_c_req.params.gattc_write.write_op = BLE_GATT_OP_WRITE_REQ;
  return nrf_ble_gq_item_add(p_ble_app_c->p_gatt_queue,&tmp_c_req,p_ble_app_c->conn_handle);

}
uint32_t ble_app_c_tmp_notify_enable(ble_app_c_t *p_ble_app_c)
{
  VERIFY_PARAM_NOT_NULL(p_ble_app_c);
  return  cccd_configure(p_ble_app_c,true);
      
}

void ble_app_on_db_disc_evt(ble_app_c_t *p_ble_app_c, const ble_db_discovery_evt_t *p_evt)
{
  ret_code_t err_code;
  // Check if HRS Service was discovered.
  if(p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE &&
     p_evt->params.discovered_db.srv_uuid.uuid == BLE_UUID_HEART_RATE_SERVICE &&
     p_evt->params.discovered_db.srv_uuid.type  == BLE_UUID_TYPE_BLE)
  {
    // Find the CCCD handle of the Temp Measuremet characteristic.
    uint32_t i;
    ble_app_c_evt_t evt;
    
    evt.evt_type  = BLE_APP_C_EVT_DISCOVERY_COMPLETE;
    evt.conn_handle = p_evt->conn_handle;

    for(i = 0 ; i < p_evt->params.discovered_db.char_count;i++)
    {
      if(p_evt->params.discovered_db.charateristics[i].characteristic.uuid.uuid == BLE_UUID_HEART_RATE_MEASUREMENT_CHAR)
      {
       // Found Heart Rate characteristic. Store CCCD handle and break.
       evt.params.peer_db.tmp_cccd_handle=
          p_evt->params.discovered_db.charateristics[i].cccd_handle;
          evt.params.peer_db.tmp_handle=
                        p_evt->params.discovered_db.charateristics[i].characteristic.handle_value;
       break;              
      }
    
    }
  NRF_LOG_DEBUG("Heart Rate Service discovered at peer.");
  //If the instance has been assigned prior to db_discovery, assign the db_handles.
  if(p_ble_app_c->conn_handle != BLE_CONN_HANDLE_INVALID)
  {
    if((p_ble_app_c->peer_tmp_db.tmp_cccd_handle == BLE_GATT_HANDLE_INVALID)&&
        (p_ble_app_c->peer_tmp_db.tmp_handle == BLE_GATT_HANDLE_INVALID))
        {
          p_ble_app_c->peer_tmp_db = evt.params.peer_db;
        }
  }
  p_ble_app_c->evt_handler(p_ble_app_c,&evt);
  } 
}

uint32_t ble_tmp_c_handles_assign(ble_app_c_t *p_ble_tmp_c,
                                  uint16_t     conn_handle,
                                  const tmp_db_t  *p_peer_tmp_handles)
{
         VERIFY_PARAM_NOT_NULL(p_ble_tmp_c);
         p_ble_tmp_c->conn_handle = conn_handle;
         if(p_peer_tmp_handles!= NULL)
         {
          p_ble_tmp_c->peer_tmp_db = *p_peer_tmp_handles;
         }
         return nrf_ble_gq_conn_handle_register(p_ble_tmp_c->p_gatt_queue, conn_handle);
         
}