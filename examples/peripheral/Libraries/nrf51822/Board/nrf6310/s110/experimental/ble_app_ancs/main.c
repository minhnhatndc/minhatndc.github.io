/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 */

/** @file
 *
 * @defgroup ble_sdk_apple_notification_main main.c
 * @{
 * @ingroup ble_sdk_app_apple_notification
 * @brief Apple Notification Client Sample Application main file.  - Disclaimer: This module (Apple Notification Center Service) can and will be changed at any time by either Apple or Nordic Semiconductor ASA.
 *
 * This file contains the source code for a sample application using the Apple Notification Profile 
 * Client. This application uses the @ref srvlib_conn_params module.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "ble_ancs_c.h"
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "ble_hci.h"
#include "ble_gap.h"
#include "ble_advdata.h"
#include "ble_error_log.h"
#include "nrf_gpio.h"
#include "ble_srv_common.h"
#include "ble_conn_params.h"
#include "nrf_gpiote.h"
#include "nrf51_bitfields.h"
#include "ble_bondmngr.h"
#include "app_gpiote.h"
#include "app_button.h"
#include "app_timer.h"
#include "ble_radio_notification.h"
#include "ble_flash.h"
#include "ble_debug_assert_handler.h"
#include "pstorage.h"
#include "nrf_soc.h"
#include "nRF6350.h"
#include "boards.h"
#include "softdevice_handler.h"

#define ERROR_PIN                       8                                                    /**< Pin that is active high when there is an error in this example */

#define MAX_CHARACTERS_PER_LINE         16                                                   /**< Maximum characters that are visible in one line on nRF6350 display */
#define DISPLAY_BUFFER_SIZE             ANCS_ATTRIBUTE_DATA_MAX                              /**< Size of LCD display buffer */

#define ADVERTISING_LED_PIN_NO          LED_0                                                /**< Is on when device is advertising. */
#define CONNECTED_LED_PIN_NO            LED_1                                                /**< Is on when device has connected. */
#define ASSERT_LED_PIN_NO               LED_7                                                /**< Is on when application has asserted. */


#define WAKEUP_BUTTON_PIN               BUTTON_0                                             /**< Button used to wake up the application. */
#define BONDMNGR_DELETE_BUTTON_PIN_NO   BUTTON_1                                             /**< Button used for deleting all bonded masters/services during startup. */
#define DISPLAY_MESSAGE_BUTTON_PIN      BUTTON_5                                             /**< Button used to display message contents */
#define SCROLL_ONE_BUTTON_PIN           BUTTON_6                                             /**< Button used to scroll one character */

#define DEVICE_NAME                     "ANCC"                                               /**< Name of device. Will be included in the advertising data. */
#define APP_ADV_INTERVAL                40                                                   /**< The advertising interval (in units of 0.625 ms. This value corresponds to 25 ms). */
#define APP_ADV_INTERVAL_SLOW           3200                                                 /**< Slow advertising interval (in units of 0.625 ms. This value corresponds to 2 seconds). */
#define APP_ADV_TIMEOUT_IN_SECONDS      180                                                  /**< The advertising timeout in units of seconds. */
#define ADV_INTERVAL_FAST_PERIOD        30                                                   /**< The duration of the fast advertising period (in seconds). */

#define APP_TIMER_PRESCALER             0                                                    /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_MAX_TIMERS            2                                                    /**< Maximum number of simultaneously created timers. */
#define APP_TIMER_OP_QUEUE_SIZE         4                                                    /**< Size of timer operation queues. */

#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(500, UNIT_1_25_MS)                     /**< Minimum acceptable connection interval (0.5 seconds). */
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(1000, UNIT_1_25_MS)                    /**< Maximum acceptable connection interval (1 second). */
#define SLAVE_LATENCY                   0                                                    /**< Slave latency. */
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(4000, UNIT_10_MS)                      /**< Connection supervisory timeout (4 seconds). */

#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(20 * 1000, APP_TIMER_PRESCALER)      /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (20 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(5 * 1000, APP_TIMER_PRESCALER)       /**< Time between each call to sd_ble_gap_conn_param_update after the first (5 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT    3                                                    /**< Number of attempts before giving up the connection parameter negotiation. */

#define MESSAGE_BUFFER_SIZE             18                                                   /**< Size of buffer holding optional messages in notifications. */

#define APP_GPIOTE_MAX_USERS            1                                                    /**< Maximum number of users of the GPIOTE handler. */

#define BUTTON_DETECTION_DELAY          APP_TIMER_TICKS(50, APP_TIMER_PRESCALER)             /**< Delay from a GPIOTE event until a button is reported as pushed (in number of timer ticks). */

#define SEC_PARAM_TIMEOUT               30                                                   /**< Timeout for Pairing Request or Security Request (in seconds). */
#define SEC_PARAM_BOND                  1                                                    /**< Perform bonding. */
#define SEC_PARAM_MITM                  0                                                    /**< Man In The Middle protection not required. */
#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                                 /**< No I/O capabilities. */
#define SEC_PARAM_OOB                   0                                                    /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE          7                                                    /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE          16                                                   /**< Maximum encryption key size. */

#define ANCS_FLASH_PAGE                 (BLE_FLASH_PAGE_END - 4)                             /**< Flash page used for Apple Notification Client. */

#define DEAD_BEEF                       0xDEADBEEF                                           /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

typedef enum
{
    BLE_NO_ADVERTISING,                                                                      /**< No advertising running. */
    BLE_SLOW_ADVERTISING,                                                                    /**< Slow advertising running. */
    BLE_FAST_ADVERTISING                                                                     /**< Fast advertising running. */
} ble_advertising_mode_t;


static const char *lit_catid[] =
{
    "Other",
    "IncomingCall",
    "MissedCall",
    "VoiceMail",
    "Social",
    "Schedule",
    "Email",
    "News",
    "HealthAndFitness",
    "BusinessAndFinance",
    "Location",
    "Entertainment"
};

static const char *lit_eventid[] =
{
    "Added",
    "Modified",
    "Removed"
};

static ble_ancs_c_t                     m_ancs_c;                                            /**< Structure used to identify the Apple Notification Service Client. */
static uint8_t                          m_apple_message_buffer[MESSAGE_BUFFER_SIZE];         /**< Message buffer for optional notify messages. */

static ble_gap_adv_params_t             m_adv_params;                                        /**< Parameters to be passed to the stack when starting advertising. */
static ble_advertising_mode_t           m_advertising_mode;                                  /**< Variable to keep track of when we are advertising. */

static ble_gap_sec_params_t             m_sec_params;                                        /**< Security requirements for this application. */

static char                             display_title[DISPLAY_BUFFER_SIZE];
static char                             display_message[DISPLAY_BUFFER_SIZE];
static uint32_t                         display_offset = 0;
static uint8_t                          m_ancs_uuid_type;

/**@brief Function for error handling, which is called when an error has occurred. 
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze 
 *          how your product is supposed to react in case of error.
 *
 * @param[in] error_code  Error code supplied to the handler.
 * @param[in] line_num    Line number where the handler is called.
 * @param[in] p_file_name Pointer to the file name. 
 */
void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    nrf_gpio_pin_set(ASSERT_LED_PIN_NO);

    // This call can be used for debug purposes during development of an application.
    // @note CAUTION: Activating this code will write the stack to flash on an error.
    //                This function should NOT be used in a final product.
    //                It is intended STRICTLY for development/debugging purposes.
    //                The flash write will happen EVEN if the radio is active, thus interrupting
    //                any communication.
    //                Use with care. Un-comment the line below to use.
    ble_debug_assert_handler(error_code, line_num, p_file_name);

    // On assert, the system can only recover on reset.
    //NVIC_SystemReset();
}


/**@brief Callback function for asserts in the SoftDevice.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze 
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in]   line_num   Line number of the failing ASSERT call.
 * @param[in]   file_name  File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}


/**@brief Function for setup of apple notifications in master.
 *
 * @details This function will be called when a successful connection has been established.
 */
static void apple_notification_setup(void)
{
    uint32_t err_code;

    err_code = ble_ancs_c_enable_notif_notification_source(&m_ancs_c);
    APP_ERROR_CHECK(err_code);

    err_code = ble_ancs_c_enable_notif_data_source(&m_ancs_c);
    APP_ERROR_CHECK(err_code);
}

/**@brief Display an iOS notification
 *
 */
void evt_ios_notification(ble_ancs_c_evt_ios_notification_t *p_notice)
{
    bool success;
    char buffer[DISPLAY_BUFFER_SIZE];
    
    success = nrf6350_lcd_write_string(lit_catid[p_notice->category_id], 
        strlen(lit_catid[p_notice->category_id]), LCD_UPPER_LINE, 0);
    APP_ERROR_CHECK_BOOL(success);
    
    sprintf(buffer, "%s %02x%02x%02x%02x",
        lit_eventid[p_notice->event_id], 
        p_notice->notification_uid[0], p_notice->notification_uid[1], 
        p_notice->notification_uid[2], p_notice->notification_uid[3]);

    success = nrf6350_lcd_write_string(buffer, strlen(buffer), LCD_LOWER_LINE, 0);
    APP_ERROR_CHECK_BOOL(success);
}

/**@brief Display iOS notification message contents
 *
 */
static void display_ios_message(void)
{
    bool success;

    success = nrf6350_lcd_write_string(display_title, strlen(display_title), LCD_UPPER_LINE, 0);
    APP_ERROR_CHECK_BOOL(success);
    success = nrf6350_lcd_write_string(display_message, strlen(display_message), LCD_LOWER_LINE, 0);
    APP_ERROR_CHECK_BOOL(success);

    display_offset = 0;
}

/**@brief Scroll message contents
 *
 */
 static void scroll_one(void)
{
    bool success;

    display_offset++;

    success = nrf6350_lcd_write_string(display_message + display_offset,
                             strlen(display_message) - display_offset, LCD_LOWER_LINE, 0);
    APP_ERROR_CHECK_BOOL(success);
}

/**@brief Copy notification attribute data to buffer
 *
 */
static void evt_notif_attribute(ble_ancs_c_evt_notif_attribute_t *p_attr)
{
    if (p_attr->attribute_id == BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_TITLE)
    {
        memcpy(display_title, p_attr->data, p_attr->attribute_len);
    }
    else if (p_attr->attribute_id == BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_MESSAGE)
    {
        memcpy(display_message, p_attr->data, p_attr->attribute_len);
    }
}


/**@brief Function for handling the Apple Notification Service Client.
 *
 * @details This function will be called for all events in the Apple Notification Client which
 *          are passed to the application.
 *
 * @param[in]   p_evt   Event received from the Apple Notification Service Client.
 */
static void on_ancs_c_evt(ble_ancs_c_evt_t * p_evt)
{
    uint32_t err_code = NRF_SUCCESS;

    switch (p_evt->evt_type)
    {
        case BLE_ANCS_C_EVT_DISCOVER_COMPLETE:
            err_code = sd_ble_gap_authenticate(m_ancs_c.conn_handle, &m_sec_params);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_ANCS_C_EVT_IOS_NOTIFICATION:
            evt_ios_notification(&p_evt->data.notification);
            break;

        case BLE_ANCS_C_EVT_NOTIF_ATTRIBUTE:
            evt_notif_attribute(&p_evt->data.attribute);
            break;

        default:
            //No implementation needed
            break;
    }
}


/**@brief Function for handling the Bond Manager.
 *
 * @details This function will be called for all events in the Bond Manager which
 *          are passed to the application.
 *
 * @param[in]   p_evt   Event received from the Bond Manager.
 */
static void on_bond_mgmr_evt(ble_bondmngr_evt_t * p_evt)
{
    ble_ancs_c_on_bondmgmr_evt(&m_ancs_c, p_evt);
}


/**@brief Function for the LEDs initialization.
 *
 * @details Initializes all LEDs used by this application.
 */
static void leds_init(void)
{
    nrf_gpio_cfg_output(ADVERTISING_LED_PIN_NO);
    nrf_gpio_cfg_output(CONNECTED_LED_PIN_NO);
    nrf_gpio_cfg_output(ASSERT_LED_PIN_NO);
}


/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
static void timers_init(void)
{
    // Initialize timer module.
    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_MAX_TIMERS, APP_TIMER_OP_QUEUE_SIZE, false);
}


/**@brief Function for the GAP initialization.
 *
 * @details This function shall be used to setup all the necessary GAP (Generic Access Profile)
 *          parameters of the device. It also sets the permissions and appearance.
 */
static void gap_params_init(void)
{
    uint32_t                err_code;
    ble_gap_conn_params_t   gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    
    err_code = sd_ble_gap_device_name_set(&sec_mode, 
                                          (const uint8_t *)DEVICE_NAME, 
                                          strlen(DEVICE_NAME));
    APP_ERROR_CHECK(err_code);

    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing the Advertising functionality.
 *
 * @details Encodes the required advertising data and passes it to the stack.
 *          Also builds a structure to be passed to the stack when starting advertising.
 */
static void advertising_init(void)
{
    uint32_t      err_code;
    ble_advdata_t advdata;
    uint8_t       flags = BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE;
    ble_uuid_t    ancs_uuid;
    
    ancs_uuid.uuid = ((ble_ancs_base_uuid128.uuid128[12]) | (ble_ancs_base_uuid128.uuid128[13] << 8));
    ancs_uuid.type = m_ancs_uuid_type;    
    
    // Build and set advertising data.
    memset(&advdata, 0, sizeof(advdata));
    
    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.include_appearance      = true;
    advdata.flags.size              = sizeof(flags);
    advdata.flags.p_data            = &flags;
    advdata.uuids_complete.uuid_cnt = 0;
    advdata.uuids_complete.p_uuids  = NULL;
    advdata.uuids_solicited.uuid_cnt = 1;
    advdata.uuids_solicited.p_uuids  = &ancs_uuid;    
    
    err_code = ble_advdata_set(&advdata, NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for starting advertising.
 */
static void advertising_start(void)
{
    uint32_t err_code;

    if (m_advertising_mode == BLE_NO_ADVERTISING)
    {
        m_advertising_mode = BLE_FAST_ADVERTISING;
    }
    else
    {
        m_advertising_mode = BLE_SLOW_ADVERTISING;
    }

    // Initialize advertising parameters (used when starting advertising).
    memset(&m_adv_params, 0, sizeof(m_adv_params));
    
    m_adv_params.type        = BLE_GAP_ADV_TYPE_ADV_IND;
    m_adv_params.p_peer_addr = NULL;                           // Undirected advertisement.
    m_adv_params.fp          = BLE_GAP_ADV_FP_ANY;

    if (m_advertising_mode == BLE_FAST_ADVERTISING)
    {
        m_adv_params.interval = APP_ADV_INTERVAL;
        m_adv_params.timeout  = ADV_INTERVAL_FAST_PERIOD;
    }
    else
    {
        m_adv_params.interval = APP_ADV_INTERVAL_SLOW;
        m_adv_params.timeout  = APP_ADV_TIMEOUT_IN_SECONDS;
    }

    err_code = sd_ble_gap_adv_start(&m_adv_params);
    APP_ERROR_CHECK(err_code);
    
    nrf_gpio_pin_set(ADVERTISING_LED_PIN_NO);
}


/**@brief Function for handling the Apple Notification Service Client errors.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
static void apple_notification_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}


/**@brief Function for handling a Connection Parameters error.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
static void conn_params_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}


/**@brief Function for initializing the Connection Parameters module.
 */
static void conn_params_init(void)
{
    uint32_t               err_code;
    ble_conn_params_init_t cp_init;

    memset(&cp_init, 0, sizeof(cp_init));

    cp_init.p_conn_params                  = NULL;
    cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
    cp_init.next_conn_params_update_delay  = NEXT_CONN_PARAMS_UPDATE_DELAY;
    cp_init.max_conn_params_update_count   = MAX_CONN_PARAMS_UPDATE_COUNT;
    cp_init.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
    cp_init.disconnect_on_fail             = true;
    cp_init.evt_handler                    = NULL;
    cp_init.error_handler                  = conn_params_error_handler;

    err_code = ble_conn_params_init(&cp_init);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing security parameters.
 */
static void sec_params_init(void)
{
    m_sec_params.timeout      = SEC_PARAM_TIMEOUT;
    m_sec_params.bond         = SEC_PARAM_BOND;
    m_sec_params.mitm         = SEC_PARAM_MITM;
    m_sec_params.io_caps      = SEC_PARAM_IO_CAPABILITIES;
    m_sec_params.oob          = SEC_PARAM_OOB;  
    m_sec_params.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
    m_sec_params.max_key_size = SEC_PARAM_MAX_KEY_SIZE;
}


/**@brief Function for handling a Bond Manager error.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
static void bond_manager_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}


/**@brief Function for initializing the Bond Manager.
 */
static void bond_manager_init(void)
{
    uint32_t            err_code;
    ble_bondmngr_init_t bond_init_data;
    bool                bonds_delete;

    err_code = pstorage_init();
    APP_ERROR_CHECK(err_code);
    
    // Clear all bonded masters if the Bonds Delete button is pushed.
    err_code = app_button_is_pushed(BONDMNGR_DELETE_BUTTON_PIN_NO, &bonds_delete);
    APP_ERROR_CHECK(err_code);

    // Initialize the Bond Manager.
    bond_init_data.evt_handler             = on_bond_mgmr_evt;
    bond_init_data.error_handler           = bond_manager_error_handler;
    bond_init_data.bonds_delete            = bonds_delete;
    
    err_code = ble_bondmngr_init(&bond_init_data);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 */
static void on_ble_evt(ble_evt_t * p_ble_evt)
{
    uint32_t        err_code = NRF_SUCCESS;
    static uint16_t m_conn_handle = BLE_CONN_HANDLE_INVALID;
    
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            nrf_gpio_pin_set(CONNECTED_LED_PIN_NO);
            nrf_gpio_pin_clear(ADVERTISING_LED_PIN_NO);
            err_code = app_button_enable();
            m_advertising_mode = BLE_NO_ADVERTISING;
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

            break;
        
        case BLE_GAP_EVT_AUTH_STATUS:
            apple_notification_setup();
            break;
            
        case BLE_GAP_EVT_DISCONNECTED:
            nrf_gpio_pin_clear(CONNECTED_LED_PIN_NO);

            m_conn_handle = BLE_CONN_HANDLE_INVALID;

            // Stop detecting button presses when not connected.
            err_code = app_button_disable();
            APP_ERROR_CHECK(err_code);

            // Since we are not in a connection and have not start to advertise either, store bonds.
            err_code = ble_bondmngr_bonded_centrals_store();
            APP_ERROR_CHECK(err_code);

            err_code = ble_ans_c_service_store();
            APP_ERROR_CHECK(err_code);

            advertising_start();
            break;
            
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
            err_code = sd_ble_gap_sec_params_reply(m_conn_handle, 
                                                   BLE_GAP_SEC_STATUS_SUCCESS, 
                                                   &m_sec_params);
            break;

        case BLE_GAP_EVT_TIMEOUT:
            if (p_ble_evt->evt.gap_evt.params.timeout.src == BLE_GAP_TIMEOUT_SRC_ADVERTISEMENT)
            { 
                if (m_advertising_mode == BLE_FAST_ADVERTISING)
                {
                    advertising_start();
                }
                else
                {
                    nrf_gpio_pin_clear(ADVERTISING_LED_PIN_NO);
                    m_advertising_mode = BLE_NO_ADVERTISING;

                    // Go to system-off mode (function will not return; wakeup will cause a reset).
                    nrf_gpio_cfg_sense_input(WAKEUP_BUTTON_PIN, 
                                             BUTTON_PULL, 
                                             NRF_GPIO_PIN_SENSE_LOW);
                    
                    nrf_gpio_cfg_sense_input(BONDMNGR_DELETE_BUTTON_PIN_NO, 
                                             BUTTON_PULL, 
                                             NRF_GPIO_PIN_SENSE_LOW);
                    
                    err_code = sd_power_system_off();
                }
            }
            break;
            
        case BLE_GATTC_EVT_TIMEOUT:
        case BLE_GATTS_EVT_TIMEOUT:
            // Disconnect on GATT Server and Client timeout events.
            err_code = sd_ble_gap_disconnect(m_conn_handle, 
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            break;

        default:
            //No implementation needed
            break;
    }

    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling button events.
 *
 * @param[in]   pin_no   The pin number of the button pressed.
 */
static void button_event_handler(uint8_t pin_no, uint8_t button_action)
{
    if (button_action == APP_BUTTON_PUSH)
    {
        switch (pin_no)
        {
            case DISPLAY_MESSAGE_BUTTON_PIN:
              display_ios_message();
              break;

            case SCROLL_ONE_BUTTON_PIN:
              scroll_one();
              break;
                
            default:
                APP_ERROR_HANDLER(pin_no);
                break;
        }
    }
}


/**@brief Function for initializing the GPIOTE handler module.
 */
static void gpiote_init(void)
{
    APP_GPIOTE_INIT(APP_GPIOTE_MAX_USERS);
}


/**@brief Function for initializing the button handler module.
 */
static void buttons_init(void)
{
    static app_button_cfg_t buttons[] =
    {
        {WAKEUP_BUTTON_PIN,             false, NRF_GPIO_PIN_NOPULL, NULL},
        {BONDMNGR_DELETE_BUTTON_PIN_NO, false, NRF_GPIO_PIN_NOPULL, NULL},
        {DISPLAY_MESSAGE_BUTTON_PIN,    false, NRF_GPIO_PIN_NOPULL, button_event_handler},
        {SCROLL_ONE_BUTTON_PIN,         false, NRF_GPIO_PIN_NOPULL, button_event_handler}
    };
    
    APP_BUTTON_INIT(buttons, sizeof(buttons) / sizeof(buttons[0]), BUTTON_DETECTION_DELAY, false);
}


/**@brief Function for dispatching a BLE stack event to all modules with a BLE stack event handler.
 *
 * @details This function is called from the BLE Stack event interrupt handler after a BLE stack
 *          event has been received.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
    ble_bondmngr_on_ble_evt(p_ble_evt);
    ble_conn_params_on_ble_evt(p_ble_evt);
    ble_ancs_c_on_ble_evt(&m_ancs_c, p_ble_evt);
    on_ble_evt(p_ble_evt);
}


/**@brief Function for dispatching a system event to interested modules.
 *
 * @details This function is called from the System event interrupt handler after a system
 *          event has been received.
 *
 * @param[in]   sys_evt   System stack event.
 */
static void sys_evt_dispatch(uint32_t sys_evt)
{
    pstorage_sys_event_handler(sys_evt);
}


/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
static void ble_stack_init(void)
{
    uint32_t err_code;
    
    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, false);
    

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    APP_ERROR_CHECK(err_code);
    
    // Register with the SoftDevice handler module for System events.
    err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing the Radio Notification event handler.
 */
static void radio_notification_init(void)
{
    uint32_t err_code;

    err_code = ble_radio_notification_init(NRF_APP_PRIORITY_HIGH,
                                           NRF_RADIO_NOTIFICATION_DISTANCE_4560US,
                                           ble_flash_on_radio_active_evt);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for the Power manager.
 */
static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
}

static void service_add(void)
{
    ble_ancs_c_init_t ancs_init_obj;
    ble_uuid_t        service_uuid;
    uint32_t          err_code;
    bool              services_delete;

    err_code = sd_ble_uuid_vs_add(&ble_ancs_base_uuid128, &m_ancs_uuid_type);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ble_uuid_vs_add(&ble_ancs_cp_base_uuid128, &service_uuid.type);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ble_uuid_vs_add(&ble_ancs_ns_base_uuid128, &service_uuid.type);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ble_uuid_vs_add(&ble_ancs_ds_base_uuid128, &service_uuid.type);
    APP_ERROR_CHECK(err_code);

    memset(&ancs_init_obj, 0, sizeof(ancs_init_obj));
    memset(m_apple_message_buffer, 0, MESSAGE_BUFFER_SIZE);

    ancs_init_obj.evt_handler         = on_ancs_c_evt;
    ancs_init_obj.message_buffer_size = MESSAGE_BUFFER_SIZE;
    ancs_init_obj.p_message_buffer    = m_apple_message_buffer;
    ancs_init_obj.error_handler       = apple_notification_error_handler;

    err_code = ble_ancs_c_init(&m_ancs_c, &ancs_init_obj);
    APP_ERROR_CHECK(err_code);
    
    // Clear all discovered and stored services if the  "delete all bonds" button is pushed.
    err_code = app_button_is_pushed(BONDMNGR_DELETE_BUTTON_PIN_NO, &services_delete);
    APP_ERROR_CHECK(err_code);

    if (services_delete)
    {
        err_code = ble_ans_c_service_delete();
        APP_ERROR_CHECK(err_code);
    }

    err_code = ble_ans_c_service_load(&m_ancs_c);
    APP_ERROR_CHECK(err_code);    
}

/** @brief Function for configuring ERROR_PIN as output for showing errors.
 */
static void gpio_config(void)
{
    // Configure ERROR_PIN as output to show errors.
    nrf_gpio_cfg_output(ERROR_PIN);
    nrf_gpio_pin_clear(ERROR_PIN);
}

/**@brief Function for application main entry.
 */
int main(void)
{
    gpio_config();

    bool success = nrf6350_lcd_init();
    APP_ERROR_CHECK_BOOL(success);
    success = nrf6350_lcd_write_string("    BLE ANCS    ", MAX_CHARACTERS_PER_LINE, LCD_UPPER_LINE, 0);
    APP_ERROR_CHECK_BOOL(success);

    // Initialize.
    leds_init();
    timers_init();
    gpiote_init();
    buttons_init();
    ble_stack_init();    
    bond_manager_init();
    gap_params_init();
    service_add();    
    advertising_init();
    conn_params_init();
    sec_params_init();
    radio_notification_init();
    
    // Start execution.
    advertising_start();

    // Enter main loop.
    for (;;)
    {
        power_manage();
    }

}




/** 
 * @}
 */

