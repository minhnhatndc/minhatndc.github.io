#include "advertise_data_ble.h"
#include "sdk_common.h"
#include "ble_srv_common.h"

#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#define ADVERTISE_CUSTOM_SERVICE_UUID_BASE {0x02, 0x00,0x12, 0xAC, 0x42, 0x02, 0x62, 0xB9, \
                                            0xEE, 0x11, 0x53, 0x7E, 0xB0, 0xC9, 0x2C, 0xF0 }