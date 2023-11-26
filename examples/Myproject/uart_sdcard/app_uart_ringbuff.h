#ifndef APP_UART_RINGBUFF_H
#define APP_UART_RINGBUFF_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
/*
#include "app_uart.h"
#include "nrf_delay.h"
#include "nrf52.h"

*/
#define BUFFER_SIZE 1024U
#define TIME_OUT 5000 // time count
extern volatile uint16_t timeout;

typedef enum{
    DATA_IS_NOT_AVALABLE = 0,
    DATA_IS_AVALABLE = 1
}data_type;

typedef struct{
    volatile uint8_t Head;
    volatile uint8_t Tail;
    uint8_t Buffer[BUFFER_SIZE];
}RingBuffer_type;

/*
    void nrf52_uart_init();
*/

// Init Uart RingBuffer
void app_uart_ringbuffer_init(void);
// Put data to Ring buffer
void app_uart_ringbuffer_put(uint8_t data);
// Check data is avalable in RingBuffer
  // return 0: Data is not avalable in Buffer
  // return 1: Data is avalable in Buffer
data_type app_uart_ringbuff_data_check(void);
  // Get data form Buffer
uint8_t app_uart_ringbuffer_get(void);
// Reset RingBuffer
void app_uart_ringbuffer_reset(void);
/* Wait until a paricular string is detected in the Rx Buffer
* Return 1 on success and -1 otherwise
* USAGE: while (!(app_uart_ringbuffer_wait_for("some string")));
*/
int app_uart_ringbuffer_wait_for(char *string);
/* Copies the entered number of characters (blocking mode) from the Rx buffer into the buffer, after some particular string is detected
* Returns 1 on success and -1 otherwise
* USAGE: while (!(app_uart_ringbuffer_get_after("some string", 6, buffer)));
*/
int app_uart_ringbuffer_get_after(char *string, uint8_t numberofchar, char *buffertosave );
/* Peek for the data in the Rx Bffer without incrementing the tail count
* Returns the character
* USAGE: if (app_uart_ringbuffer_peek() == 'M') do something
*ret: 1 true, 0 false
*/
int app_uart_ringbuffer_peek(void);
/* Copies the required data from a buffer
 * @startString: the string after which the data need to be copied
 * @endString: the string before which the data need to be copied
 * @USAGE:: app_uart_ringbuffer_GetDataFormBuffer("name=", "&", buffertocopyfrom, buffertocopyinto);
 */
void app_uart_ringbuffer_GetDataFormBuffer(char *startstring, char *endstring, char *buffercopyfrom, char *buffercopyto);
/* Copy the data from the Rx buffer into the bufferr, Upto and including the entered string
* This copying will take place in the blocking mode, so you won't be able to perform any other operations
* Returns 1 on success and -1 otherwise
* USAGE: while (!(app_uart_ringbuffer_copy_upto("some string", buffer)));
*/
int app_uart_ringbuffer_copy_upto(char *string, char *buffertocopy);

#endif