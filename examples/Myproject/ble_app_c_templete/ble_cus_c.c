#include "ble_cus_c.h"
#include "nrf_log.h"
#define FLAG_MASK_HR_16BIT  (0x01 << 0)           /**< Bit mask used to extract the type of heart rate value. This is used to find if the received heart rate is a 16 bit value or an 8 bit value. */
#define FLAG_MASK_HR_RR_INT (0x01 << 4) 
static void gatt_error_handler(uint32_t nrf_error, void *p_ctx, uint16_t conn_handle)
{
  ble_cus_c_t *p_ble_cus_c = (ble_cus_c_t *) p_ctx;
  NRF_LOG_INFO("GATT Client error has occurred on conn_handle");
  if(p_ble_cus_c->error_handler != NULL)
  {
    p_ble_cus_c->error_handler(nrf_error);
  }
}

uint32_t ble_cus_c_init(ble_cus_c_t *p_cus, ble_cus_c_init_t *p_init)
{
  ret_code_t err_code;
  if(p_cus == NULL || p_init == NULL)
  {
    return NRF_ERROR_NULL;
  }
  ble_uuid_t ble_uuid;
  ble_uuid.type = BLE_UUID_TYPE_BLE;
  ble_uuid.uuid = BLE_CUS_C_SERVICE_UUID;
  
  p_cus->error_handler = p_init->error_handler;
  p_cus->evt_handler   = p_init->evt_handler;
  p_cus->conn_handle   = BLE_CONN_HANDLE_INVALID;
  p_cus->p_gatt_queue  = p_init->p_gatt_queue;

  p_cus->peer_tmp_db.temp_cccd_handle = BLE_GATT_HANDLE_INVALID;
  p_cus->peer_tmp_db.temp_handle      = BLE_GATT_HANDLE_INVALID;
  
  err_code = ble_db_discovery_evt_register(&ble_uuid);
  if(err_code != NRF_SUCCESS)
  {
    return err_code;
  }
  return NRF_SUCCESS;
}
static void on_hvx(ble_cus_c_t *p_ble_cus_c,const ble_evt_t *p_ble_evt)
{
  ret_code_t err_code;
  if(p_ble_cus_c->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
  {
  NRF_LOG_DEBUG("Received HVX on link 0x%x, not associated to this instance. Ignore.",
                      p_ble_evt->evt.gattc_evt.conn_handle);
  return;
  }
     NRF_LOG_DEBUG("Received HVX on link 0x%x, tmp_handle 0x%x",
    p_ble_evt->evt.gattc_evt.params.hvx.handle,
    p_ble_cus_c->peer_tmp_db.temp_handle);
    
    if(p_ble_evt->evt.gattc_evt.params.hvx.handle == p_ble_cus_c->peer_tmp_db.temp_handle)
    {
      ble_cus_c_evt_t ble_cus_c_evt;
      uint32_t        index = 0;

      ble_cus_c_evt.evt_type    = BLE_CUS_C_NOTIFICATION;
      ble_cus_c_evt.conn_handle = p_ble_cus_c->conn_handle;
      ble_cus_c_evt.params.tmp.sleep_intervals_cnt = 0;

     //lint !e415 suppress Lint Warning 415: Likely access out of bond
     if(!(p_ble_evt->evt.gattc_evt.params.hvx.data[index++]) & FLAG_MASK_HR_16BIT)
     {
      // 8-bit value received.
      ble_cus_c_evt.params.tmp.tmp_value = p_ble_evt->evt.gattc_evt.params.hvx.data[index++];
     }else
     {
      ble_cus_c_evt.params.tmp.tmp_value = uint16_decode(&(p_ble_evt->evt.gattc_evt.params.hvx.data[index]));  
      index += sizeof(uint16_t);
      }
    if((p_ble_evt->evt.gattc_evt.params.hvx.data[0] & FLAG_MASK_HR_RR_INT))
    {
    
      uint32_t i;
      for(i = 0; i< 20; i++)
      {
        if(index >= p_ble_evt->evt.gattc_evt.params.hvx.len)
        {
        break;
        }
        ble_cus_c_evt.params.tmp.sleep_intervals[i] = uint16_decode(&(p_ble_evt->evt.gattc_evt.params.hvx.data[index]));
        index += sizeof(uint16_t);
      }
      ble_cus_c_evt.params.tmp.sleep_intervals_cnt = (uint8_t) i;
    }
    p_ble_cus_c->evt_handler(p_ble_cus_c,&ble_cus_c_evt);
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

static void on_diconnect(ble_cus_c_t *p_ble_cus_c, const ble_evt_t *p_ble_evt)
{
  
  if(p_ble_cus_c->conn_handle == p_ble_evt->evt.gap_evt.conn_handle){
  p_ble_cus_c->conn_handle  = BLE_CONN_HANDLE_INVALID;
  p_ble_cus_c->peer_tmp_db.temp_cccd_handle = BLE_GATT_HANDLE_INVALID;
  p_ble_cus_c->peer_tmp_db.temp_handle      = BLE_GATT_HANDLE_INVALID;

  ble_cus_c_evt_t evt;
  evt.evt_type = BLE_CUS_C_DISCONNECTED;
  p_ble_cus_c->evt_handler(p_ble_cus_c,&evt);
}
}
static void on_connect(ble_cus_c_t *p_ble_cus_c,const ble_evt_t *p_ble_evt)
{
  p_ble_cus_c->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
  ble_cus_c_evt_t evt;
  evt.evt_type    = BLE_CUS_C_CONNECTED;
  p_ble_cus_c->evt_handler(p_ble_cus_c,&evt);
}
void ble_cus_c_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context)
{
  ret_code_t err_code;
  ble_cus_c_t *p_ble_cus_c = (ble_cus_c_t *) p_context;
  if(p_ble_cus_c == NULL || p_ble_evt == NULL)
  {
    return;
  }
  switch(p_ble_evt->header.evt_id)
  {
    case BLE_GATTC_EVT_HVX:
        on_hvx(p_ble_cus_c,p_ble_evt);
    break;
    case BLE_GAP_EVT_DISCONNECTED:
        on_diconnect(p_ble_cus_c,p_ble_evt);
    break;
    case BLE_GAP_EVT_CONNECTED:
        on_connect(p_ble_cus_c,p_ble_evt);
    break;
    default:
    break;
  }
}
/**@brief Function for creating a message for writing to the CCCD.
 */
static uint32_t cccd_configure(ble_cus_c_t *p_ble_cus_c, bool is_notification_enable)
{
   NRF_LOG_DEBUG("Configuring CCCD. CCCD Handle = %d, Connection Handle = %d",
                  p_ble_cus_c->peer_tmp_db.temp_cccd_handle,
                  p_ble_cus_c->conn_handle);
   nrf_ble_gq_req_t value_c_req;
   uint8_t cccd[BLE_CCCD_VALUE_LEN];
   uint16_t cccd_val = is_notification_enable ? BLE_GATT_HVX_NOTIFICATION : 0;
   
   cccd[0]= LSB_16(cccd_val);
   cccd[1] = MSB_16(cccd_val);
   memset(&value_c_req,0,sizeof(value_c_req));
   value_c_req.type                = NRF_BLE_GQ_REQ_GATTC_WRITE;
   value_c_req.error_handler.cb    = gatt_error_handler;
   value_c_req.error_handler.p_ctx = p_ble_cus_c;
   
   value_c_req.params.gattc_write.handle   = p_ble_cus_c->peer_tmp_db.temp_cccd_handle;
   value_c_req.params.gattc_write.len      = BLE_CCCD_VALUE_LEN;
   value_c_req.params.gattc_write.p_value  = cccd;
   value_c_req.params.gattc_write.write_op = BLE_GATT_OP_WRITE_REQ;

   return nrf_ble_gq_item_add(p_ble_cus_c->p_gatt_queue,&value_c_req,p_ble_cus_c->conn_handle);

}
uint32_t ble_cus_c_notif_enable(ble_cus_c_t *p_ble_cus_c)
{
  if(p_ble_cus_c== NULL)
  { 
    return NRF_ERROR_NULL;
  }
  return cccd_configure(p_ble_cus_c,true);

}
void ble_cus_on_db_disc_evt(ble_cus_c_t *p_ble_cus_c, const ble_db_discovery_evt_t *p_evt)
{
  if(p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE &&
     p_evt->params.discovered_db.srv_uuid.uuid == BLE_CUS_C_SERVICE_UUID &&
     p_evt->params.discovered_db.srv_uuid.type == BLE_UUID_TYPE_BLE)
     {
      // Find the CCCD Handle of the characteristic.
      uint32_t i;
      ble_cus_c_evt_t evt;
      evt.evt_type  = BLE_CUS_C_DISCOVERY_COMPLETED;
      evt.conn_handle = p_evt->conn_handle;

      for(i =0; i<p_evt->params.discovered_db.char_count;i++)
      {
        if(p_evt->params.discovered_db.charateristics[i].characteristic.uuid.uuid == BLE_CUS_C_CHAR_UUID)
        {
          evt.params.peer_db.temp_cccd_handle = p_evt->params.discovered_db.charateristics[i].cccd_handle;
          evt.params.peer_db.temp_handle    = p_evt->params.discovered_db.charateristics[i].characteristic.handle_value;
          break;
        }
      }
      NRF_LOG_DEBUG("Service discovered at peer.");
      if(p_ble_cus_c->conn_handle != BLE_CONN_HANDLE_INVALID)
      {
        if(p_ble_cus_c->peer_tmp_db.temp_cccd_handle == BLE_GATT_HANDLE_INVALID &&
        p_ble_cus_c->peer_tmp_db.temp_handle         == BLE_GATT_HANDLE_INVALID)
        {
          p_ble_cus_c->peer_tmp_db = evt.params.peer_db;
        }

      }
      p_ble_cus_c->evt_handler(p_ble_cus_c,&evt);
     }
}
uint32_t ble_cus_c_handle_assign(ble_cus_c_t *p_ble_cus_c, uint16_t conn_handle, const tmp_db_t *p_peer_tmp_handles)
{
  VERIFY_PARAM_NOT_NULL(p_ble_cus_c);
  p_ble_cus_c->conn_handle = conn_handle;
  if(p_peer_tmp_handles != NULL)
  {
    p_ble_cus_c->peer_tmp_db = *p_peer_tmp_handles;
  }
  return nrf_ble_gq_conn_handle_register(p_ble_cus_c->p_gatt_queue,conn_handle);
}