#include "ble_gps.h"
uint32_t ble_gps_init(ble_gps_t *p_gps, ble_gps_init_t *p_gps_init)
{
  if(p_gps == NULL || p_gps_init == NULL) return NRF_ERROR_NULL;

  ret_code_t err_code;
  ble_uuid_t  ble_uuid;
  ble_uuid128_t base_uuid = BLE_GPS_BASE_UUID;
  
  p_gps->conn_handle =  BLE_CONN_HANDLE_INVALID;
  

  //add GPS Service UUID
  /*
  err_code = sd_ble_uuid_vs_add(&base_uuid,&p_gps->uuid_type);
  VERIFY_SUCCESS(err_code);
  
  ble_uuid.type   = p_gps->uuid_type;
  ble_uuid.uuid   = BLE_GPS_SERVICE_UUID;*/
  BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_GPS_SERVICE_UUID);
  // Add the custom service
  err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_gps->service_handler);
  if(err_code != NRF_SUCCESS) return err_code;
  return err_code;



    

}