/** @file
 *
 * @defgroup ble_sdk_app_template_main main.c
 * @{
 * @ingroup ble_sdk_app_template
 * @brief Template project main file.
 *
 * This file contains a template for creating a new application. It has the code necessary to wakeup
 * from button, advertise, get a connection restart advertising on disconnect and if no new
 * connection created go back to system-off mode.
 * It can easily be used as a starting point for creating a new application, the comments identified
 * with 'YOUR_JOB' indicates where and how you can customize.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// Step 1: Add Log library
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
//Step 2: Add App Timer library
#include "app_timer.h"
//Step 3: Add BSP library
#include "bsp_btn_ble.h"
//Step 4: Power Management 
#include "nrf_pwr_mgmt.h"
//Step 4: Power Management 
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_sdh_soc.h"
//Step 5: Enable Softdevice for BLE app
#include "nrf_ble_qwr.h"
//Step 7: GATT initialization
#include "nrf_ble_gatt.h"
//Step 8: Advertisement init
#include "ble_advdata.h"
#include "ble_advertising.h"
//Step 10: Connection parameters
#include "ble_conn_params.h"

#include "ble_conn_state.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "ble_srv_common.h"
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "ble.h"
#include "ble_app_temp.h"
//========= Define ==========================
#define APP_BLE_CONN_CFG_TAG 1
#define APP_BLE_OBSERVER_PRIO 3
//step 5
NRF_BLE_QWR_DEF(m_qwr); // connection to many devices QWRS, and one device QWR
static uint16_t m_conn_handle = BLE_CONN_HANDLE_INVALID;
//Step 6
#define DEVICE_NAME "TEST"
#define MIN_CONN_INTERVAL MSEC_TO_UNITS(100,UNIT_1_25_MS)
#define MAX_CONN_INTERVAL MSEC_TO_UNITS(250, UNIT_1_25_MS)
#define SLAVE_LATENCY 0
#define CONN_SUP_TIMEOUT MSEC_TO_UNITS(2000,UNIT_10_MS)
/*
#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(500, UNIT_1_25_MS) < Minimum  acceptable connection interval (0.5 seconds). 
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(4000, UNIT_10_MS)  < Connection supervisory timeout (4 seconds). 
#define NON_CONNECTABLE_ADV_INTERVAL    MSEC_TO_UNITS(100, UNIT_0_625_MS) < The advertising interval for non-connectable advertisement (100 ms). 
That's not going to work, the connection supervision timeout needs to be longer than the minimum connection interval, at least a few seconds. 
The connection interval defines how often the devices communicate. 
Every time they communicate successfully, the connection supervision timer is reset. 
If the connection supervision timer reaches the timeout without a successful connection event occurring, the connection is lost.
So the connection supervision timeout needs to be long enough that a few connection events can fail without causing the connection to be lost.
*/
//Step 7: GATT initialization
NRF_BLE_GATT_DEF(m_gatt);
//Step 8: Advertisement init
BLE_ADVERTISING_DEF(m_advertising);
#define APP_ADV_INTERVAL 100
#define APP_ADV_DURATION 0
#define APP_BLE_CONN_CFG_TAG 1
#define  APP_BLE_OBSERVER_PRIO 3
//Step 10: Connection parameters
#define FIRST_CONN_PARAM_UPDATE_DELAY APP_TIMER_TICKS(1000)
#define NEXT_CONN_PARAM_UPDATE_DELAY APP_TIMER_TICKS(30000)
#define MAX_CONN_PARAM_UPDATE_COUNT 3

static ble_uuid_t m_adv_uuids[] =                                               /**< Universally unique service identifiers. */
{
    {BLE_TEMP_SERVICE_UUID, BLE_UUID_TYPE_BLE}
};
//===========================================
//Step 1: Setting nRF Logger for BLE app
static void log_init(void)
{
  ret_code_t err_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(err_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
}
//===========================================
//Step 2: Application Timer 
void timer_init()
{ 
  ret_code_t err_code;
  err_code = app_timer_init();
  APP_ERROR_CHECK(err_code);

}
//===========================================
//Step 3 : BSP init
static void leds_init()
{
  ret_code_t err_code = bsp_init(BSP_INIT_LEDS, NULL);
  APP_ERROR_CHECK(err_code);
}
//===========================================
//Step 4: Power Management 
static void power_management_init()
{
  ret_code_t err_code;
  err_code = nrf_pwr_mgmt_init();
  APP_ERROR_CHECK(err_code);

}

static void idle_state_handle(void)
{
  if(NRF_LOG_PROCESS()== false)
    {
      nrf_pwr_mgmt_run(); // put the process into sleep mode
    }
}
//===============================================================
//Step 5: Enable Softdevice for BLE app
//nrf_sdh.ble.h
static void ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context)
{
  ret_code_t err_code = NRF_SUCCESS;
  switch(p_ble_evt->header.evt_id){
      case (BLE_GAP_EVT_DISCONNECTED): // define in ble_gap.h
          NRF_LOG_INFO("Devices is not connected");

      break;
      case (BLE_GAP_EVT_CONNECTED):
          NRF_LOG_INFO("Devices is connected");

          err_code = bsp_indication_set(BSP_INDICATE_CONNECTED);
          APP_ERROR_CHECK(err_code);

          // connect save conection handle
          m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
          err_code = nrf_ble_qwr_conn_handle_assign(&m_qwr, m_conn_handle);
          APP_ERROR_CHECK(err_code);
      break;

      case (BLE_GAP_EVT_PHY_UPDATE_REQUEST): // send update request
          NRF_LOG_INFO("PHY update request");

          ble_gap_phys_t const phys = {
            .rx_phys = BLE_GAP_PHY_AUTO,
            .tx_phys = BLE_GAP_PHY_AUTO,
          
          };
          err_code = sd_ble_gap_phy_update(p_ble_evt->evt.gap_evt.conn_handle,&phys);
          APP_ERROR_CHECK(err_code);

          
      break;
  
  
  }
  
}
static void ble_stack_init() // enable solfdevice
{ 
  ret_code_t err_code;
  //send request to enable sdv
  err_code = nrf_sdh_enable_request();
  APP_ERROR_CHECK(err_code);
  // intialize to ram
  uint32_t ram_start = 0;
  err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
  APP_ERROR_CHECK(err_code);
  //enable
  err_code = nrf_sdh_ble_enable(&ram_start);
  APP_ERROR_CHECK(err_code);

  //Resister BLE to pass the evt to evt hanlder for one obsever if have more them s vao obsevers
  NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO,ble_evt_handler,NULL);



}
//===========================================
//Step 6: GAP Initialization
void gap_params_init()
{
  ret_code_t err_code;

  ble_gap_conn_params_t gap_conn_params;
  ble_gap_conn_sec_mode_t sec_mode;
  
  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

  //set name
  err_code = sd_ble_gap_device_name_set(&sec_mode, (const uint8_t *) DEVICE_NAME, strlen(DEVICE_NAME));
  APP_ERROR_CHECK(err_code);
  /*
    set device appereance

  */
  memset(&gap_conn_params,0, sizeof(gap_conn_params));

  gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
  gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
  gap_conn_params.slave_latency = SLAVE_LATENCY;
  gap_conn_params.conn_sup_timeout = CONN_SUP_TIMEOUT;

  err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
  APP_ERROR_CHECK(err_code);




}
//===========================================
//Step 7: GATT initialization
void gatt_init()
{
  ret_code_t err_code;
  err_code = nrf_ble_gatt_init(&m_gatt,NULL);
  APP_ERROR_CHECK(err_code);

}
//===========================================
//Step 8: Advertisement init
void on_adv_evt(ble_adv_evt_t ble_adv_evt)
{
  ret_code_t err_code;
  switch(ble_adv_evt)
    {
      case BLE_ADV_EVT_FAST:
        NRF_LOG_INFO("Fast advertising...");
        err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
        APP_ERROR_CHECK(err_code);
        break;

      case BLE_ADV_EVT_IDLE:

         err_code = bsp_indication_set(BSP_INDICATE_IDLE);
         APP_ERROR_CHECK(err_code);
         break;
       default:
          //nothing
       break;
    
    }

}
void advertising_init()
{
  ret_code_t err_code;
  ble_advertising_init_t init;

  memset(&init,0, sizeof(init));

  init.advdata.name_type = BLE_ADVDATA_FULL_NAME;
  init.advdata.include_appearance = true;
  init.advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
  init.config.ble_adv_fast_interval = APP_ADV_INTERVAL;
  init.config.ble_adv_fast_timeout = APP_ADV_DURATION;
  init.advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
  init.advdata.uuids_complete.p_uuids = m_adv_uuids;

  init.evt_handler = on_adv_evt;
  init.config.ble_adv_fast_enabled = true;

  err_code = ble_advertising_init(&m_advertising,&init);
  APP_ERROR_CHECK(err_code);

  ble_advertising_conn_cfg_tag_set(&m_advertising,APP_BLE_CONN_CFG_TAG);


}
//===========================================
//Step 9: Service initializing
void nrf_qwr_error_handler(uint32_t nrf_error)
{
  APP_ERROR_CHECK(nrf_error);

}
void services_init()
{
  ret_code_t err_code;
  nrf_ble_qwr_init_t qwr_init = {0};

  qwr_init.error_handler = nrf_qwr_error_handler;

  err_code = nrf_ble_qwr_init(&m_qwr,&qwr_init);
  APP_ERROR_CHECK(err_code);

  
  
}
//==========================================
//Step 10: Connection parameters
void on_conn_params_evt(ble_conn_params_evt_t * p_event)
{
  ret_code_t err_code;
  if(p_event->evt_type == BLE_CONN_PARAMS_EVT_FAILED)
    {
      err_code = sd_ble_gap_disconnect(m_conn_handle,BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
      APP_ERROR_CHECK(err_code);
    }
   if(p_event->evt_type == BLE_CONN_PARAMS_EVT_SUCCEEDED)
    {
      
    }
}
void conn_params_error_handler(uint32_t nrf_error)
{
  APP_ERROR_CHECK(nrf_error);

}
void conn_params_init()
{
  ret_code_t err_code;

  ble_conn_params_init_t cp_init;
  memset(&cp_init,0,sizeof(cp_init));

  cp_init.p_conn_params = NULL;
  cp_init.first_conn_params_update_delay = FIRST_CONN_PARAM_UPDATE_DELAY;
  cp_init.next_conn_params_update_delay = NEXT_CONN_PARAM_UPDATE_DELAY;
  cp_init.max_conn_params_update_count = MAX_CONN_PARAM_UPDATE_COUNT;
  cp_init.start_on_notify_cccd_handle = BLE_GATT_HANDLE_INVALID;
  cp_init.disconnect_on_fail = false;
  cp_init.evt_handler = on_conn_params_evt;
  cp_init.error_handler = conn_params_error_handler;

  err_code = ble_conn_params_init(&cp_init);
  APP_ERROR_CHECK(err_code);

}
//===========================================
// Step 11: Start advertisement
void advertisement_start()
{
  ret_code_t err_code = ble_advertising_start(&m_advertising, BLE_ADV_MODE_FAST);
  APP_ERROR_CHECK(err_code);

}
//===========================================
/**@brief Function for application main entry.
 */
int main(void)
{   //Step 1: Logger
    log_init();
    //Step 2: Application Timer
    timer_init();
    //Step 3: BSP
    leds_init();
    //Step 4: Power Management 
    power_management_init();
    //Step 5: Enable Softdevice for BLE app
    ble_stack_init();
    //Step 6: GAP Initialization
    gap_params_init();
    //Step 7: GATT initialization
    gatt_init();
    //Step 8: Advertisement init
    advertising_init();

    //Step 9: Service initializing
    services_init();
    //Step 10: Connection parameters
    conn_params_init();
    //Step 11: Advertisement start
    NRF_LOG_INFO("Start advertising");

    advertisement_start();

    // Enter main loop.
    for (;;)
    {
        idle_state_handle();
    }
}


/**
 * @}
 */
