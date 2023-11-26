#include "ble_custom_dev.h"
uint32_t ble_cus_init(ble_cus_t *p_cus, ble_cus_init_t *p_init){
    ret_code_t err_code;
    ble_uuid_t ble_uuid;
    ble_add_char_params_t add_char_params;

    if(p_cus == NULL || p_init == NULL)
    {
      return NRF_ERROR_NULL;
    }
    //init service struct
    p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;


    // ADD service uuid
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_CUS_SERVICE_UUID);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid, &p_cus->service_handle);
    if(err_code != NRF_SUCCESS)
    {
      return err_code;
    }
    //add characteristic
    memset(&add_char_params,0,sizeof(add_char_params));
    add_char_params.uuid = BLE_TMP_CHAR_UUID;
    add_char_params.uuid_type = p_cus->uuid_type;
    add_char_params.max_len = MAX_DATA_LEN;
    add_char_params.init_len = sizeof(uint8_t);
    add_char_params.char_props.notify =1;
    add_char_params.cccd_write_access = SEC_OPEN;
    err_code = characteristic_add(p_cus->service_handle, &add_char_params,&p_cus->temp_value_handle);
    if(err_code != NRF_SUCCESS) return err_code;

    return NRF_SUCCESS;
}
