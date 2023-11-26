#ifndef BLE_HRART_H
#define BLE_HEART_H
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"

#endif
// Step 2 - Creating a Custom Base UUID
//Step 3 - Initializing the Service and advertising our 128-bit UUID.
// Step 4 - Adding a Custom Value Characteristic to the Custom Service.
//Step 5 - Handling events from the SoftDevice.
//Step 6 - Handling the Write event from the SoftDevice.
// Step 7 - Propagating Custom Service events to the application
/*
Until now we've only handled the events that are propagated by the SoftDevice, 
but in some cases it makes sense to propagate events to the application.
In order to do this 
we need to add an event handler to our Custom Service Init structure 
and Custom Service structure.
*/
//Step 8 - Notifying the Custom Value Characteristic