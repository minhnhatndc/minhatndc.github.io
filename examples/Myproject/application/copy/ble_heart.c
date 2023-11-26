#include "ble_heart.h"
static uint32_t custom_value_char_add(ble_heart_t *p_hrs, ble_heart_init_t *p_hrs_init);
/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_heart_t *p_hrs, ble_evt_t const *p_ble_evt)
{
  p_hrs->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
  ble_heart_evt_t evt;
  evt.evt_type =    BLE_HEART_EVT_CONNECTED;
  p_hrs->evt_handler(p_hrs,&evt);
}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
 static void on_disconnect(ble_heart_t *p_hrs, ble_evt_t const *p_ble_evt)
 {
 UNUSED_PARAMETER(p_ble_evt);
 p_hrs->conn_handle = BLE_CONN_HANDLE_INVALID;
 }

/**@brief Function for handling the Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_heart_t *p_hrs, ble_evt_t const * p_ble_evt)
 {
  ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

  if(p_evt_write->handle == p_hrs->heart_value_handles.value_handle)
    {
      //Do something
    }
     // Check if the Custom value CCCD is written to and that the value is the appropriate length, i.e 2 bytes.
    if ((p_evt_write->handle == p_hrs->heart_value_handles.cccd_handle) && (p_evt_write->len == 2))
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
          p_hrs->evt_handler(p_hrs,&evt);
        }
    }
 }

void ble_heart_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context)
{
   ble_heart_t *p_hrs = (ble_heart_t *)p_context;
   if(p_hrs == NULL || p_ble_evt == NULL)
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


/**
uint32_t ble_heart_init(ble_heart_t *p_hrs, ble_heart_init_t *p_hrs_init)
 {
    ret_code_t err_code;
    if(p_hrs == NULL || p_hrs_init == NULL)  
      {
        return NRF_ERROR_NULL;
      }
    ble_uuid_t ble_uuid;
      // Initialize service structure
    p_hrs->conn_handle = BLE_CONN_HANDLE_INVALID;
    p_hrs->evt_handler = p_hrs_init->evt_handler;
      //Add Custom Service UUID
    /*ble_uuid128_t base_uuid =  BLE_HEART_BASE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_hrs->uuid_type);
    
    ble_uuid.type = p_hrs->uuid_type;
    ble_uuid.uuid = BLE_HEART_SERVICE_UUID;
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_HEART_RATE_SERVICE);
    //add the Custom Service decleration to the BLE Stack's GATT table.
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_hrs->service_handle);
    if(err_code != NRF_SUCCESS);
      {
        return err_code;
      }
      return custom_value_char_add(p_hrs,p_hrs_init);
 
 }
 **/
uint32_t ble_heart_init(ble_heart_t *p_hrs, ble_heart_init_t *p_hrs_init)
{
  if(p_hrs == NULL || p_hrs_init == NULL) return NRF_ERROR_NULL;

  ret_code_t err_code;
  ble_uuid_t ble_uuid;
  ble_add_char_params_t add_char_params;

  //init Service Structure
  p_hrs->evt_handler = p_hrs_init->evt_handler;
  p_hrs->conn_handle = BLE_CONN_HANDLE_INVALID;
  
  // Add Service
  BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_HEART_RATE_SERVICE);
  err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_hrs->service_handle);
  if(err_code != NRF_SUCCESS) return err_code;

  //Add Characteristics
  memset(&add_char_params,0, sizeof(add_char_params));
  add_char_params.uuid = BLE_UUID_HEART_RATE_MEASUREMENT_CHAR;
  add_char_params.max_len = sizeof(uint16_t);
  add_char_params.init_len = sizeof(uint16_t);
  add_char_params.char_props.read = 1;
  add_char_params.read_access = p_hrs_init->cccd_read_sec;
  err_code= characteristic_add(p_hrs->service_handle, &add_char_params, &p_hrs->heart_value_handles);
  if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
}

 /**@brief Function for adding the Custom Value characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t custom_value_char_add(ble_heart_t *p_hrs, ble_heart_init_t *p_hrs_init)
{
  ret_code_t err_code;
  ble_gatts_char_md_t           char_md;/**@brief GATT Characteristic metadata. */
  ble_gatts_attr_md_t           cccd_md;/**@brief Attribute metadata. Read/Write permission */
  ble_gatts_attr_t              attr_char_value;/**@brief GATT Attribute. ATT UUID */ 
  ble_uuid_t                    ble_uuid;
  ble_gatts_attr_md_t           attr_md;

  memset(&char_md,0,sizeof(char_md));
  char_md.char_props.read     = 1;
  char_md.char_props.write    = 1;
  char_md.char_props.notify   = 1;
  char_md.p_cccd_md           =&cccd_md;
  char_md.p_char_user_desc    = NULL;/**< Pointer to a UTF-8 encoded string (non-NULL terminated), NULL if the descriptor is not required. */
  char_md.p_char_pf           = NULL;/**< Pointer to a presentation format structure or NULL if the CPF descriptor is not required. */
  char_md.p_user_desc_md      = NULL;/**< Attribute metadata for the User Description descriptor, or NULL for default values. */
  char_md.p_cccd_md           = NULL;/**< Attribute metadata for the Client Characteristic Configuration Descriptor, or NULL for default values. */
  char_md.p_sccd_md           = NULL;/**< Attribute metadata for the Server Characteristic Configuration Descriptor, or NULL for default values. */
/*
o we want to be able to both write and read to our Custom Value characteristic, but we do not want to enable the notify property until later.
*/ 
  memset(&attr_md,0,sizeof(attr_md));

  attr_md.read_perm     =   p_hrs_init->heart_value_char_attr_md.read_perm;
  attr_md.write_perm    =   p_hrs_init->heart_value_char_attr_md.write_perm;
  //  Read  operation on Cccd should be possible without authentication.
  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
  attr_md.vloc          =   BLE_GATTS_VLOC_STACK;//we want the characteristic to be stored in the SoftDevice RAM section and not in the Application RAM section.
  attr_md.rd_auth       =   0;
  attr_md.wr_auth       =   0;
  attr_md.vlen          =   0;

  ble_uuid.type         = p_hrs->uuid_type;
  ble_uuid.uuid         = BLE_HEART_VALUE_CHAR_UUID;

  memset(&attr_char_value,0,sizeof(attr_char_value));
  attr_char_value.p_uuid =  &ble_uuid;
  attr_char_value.p_attr_md = &attr_md;
  attr_char_value.init_len  = sizeof(uint8_t);
  attr_char_value.init_offs = 0;
  attr_char_value.max_len   = sizeof(uint8_t);

  err_code = sd_ble_gatts_characteristic_add(p_hrs->service_handle,
                                             &char_md,
                                             &attr_char_value,
                                             &p_hrs->heart_value_handles);
  if(err_code != NRF_SUCCESS)
    {
      return  err_code;
    }
    return NRF_SUCCESS;


    }

uint32_t ble_heart_custom_value_update(ble_heart_t *p_hrs, uint8_t heart_value)
{
   if(p_hrs == NULL) return NRF_ERROR_NULL;
   ret_code_t err_code;
   ble_gatts_value_t gatts_value;

   memset(&gatts_value,0,sizeof(gatts_value));
   gatts_value.len = sizeof(uint8_t);
   gatts_value.offset = 0;
   gatts_value.p_value = &heart_value;
   
   //Update data base 
   err_code= sd_ble_gatts_value_set(p_hrs->conn_handle,p_hrs->heart_value_handles.value_handle,&gatts_value);
   if(err_code != NRF_SUCCESS) return err_code;

   // Send value if connected and notifying.
  if((p_hrs->conn_handle != BLE_CONN_HANDLE_INVALID))
    {
      ble_gatts_hvx_params_t hvx_params;
      memset(&hvx_params,0,sizeof(hvx_params));

      hvx_params.handle = p_hrs->heart_value_handles.value_handle;
      hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
      hvx_params.offset = 0;
      hvx_params.p_len  =&gatts_value.len;
      hvx_params.p_data = gatts_value.p_value;

      err_code = sd_ble_gatts_hvx(p_hrs->conn_handle,&hvx_params);

    
    
    }else{
      err_code = NRF_ERROR_INVALID_STATE;
    } 
    return  err_code;

    
}