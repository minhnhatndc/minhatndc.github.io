#include "app_ble_test.h"

uint32_t ble_heart_init(ble_heart_t *p_hrs, ble_heart_init_t const *p_heart_init)
{
    ret_code_t err_code;
    ble_uuid_t ble_uuid;
    ble_add_char_params_t add_char_params;

    if( p_hrs == NULL || p_heart_init == NULL)
        {
            return NRF_ERROR_NULL;
        }
    // Init service structure
    p_hrs->conn_handle  = BLE_CONN_HANDLE_INVALID;
    p_hrs->data_handler = p_heart_init->data_handler;

    //Add custom Service UUID
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_HEART_RATE_SERVICE);
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_hrs->service_handle);
    if(err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    // Add Characteristic
    // Add Heart_rate_characteristic
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid        = BLE_UUID_HEART_RATE_MEASUREMENT_CHAR;
    add_char_params.uuid_type   = p_hrs->uuid_type;
    add_char_params.max_len     = BLE_MAX_DATA_LEN;
    add_char_params.init_len    = sizeof(uint8_t);
    add_char_params.is_var_len  = true;
    add_char_params.char_props.notify = 1;
    add_char_params.char_props.read     =1;
    add_char_params.read_access = SEC_OPEN;
    
    err_code = characteristic_add(p_hrs->service_handle, &add_char_params,&p_hrs->tx_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    return err_code;
    
    


}


