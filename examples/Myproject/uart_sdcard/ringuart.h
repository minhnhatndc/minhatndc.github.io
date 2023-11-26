#ifndef  RING_UART_H
#define  RING_UART_H
#include "stdio.h"
#include "app_uart.h"
#include "nrf_uart.h"
#include "string.h"

#define MAX_BUFFER_SIZE 1024U
//#define TIME_OUT 256

typedef  enum{
  data_unvalable = 0,
  data_valable = 1,
  } state_data;

 typedef  struct {
  volatile uint8_t Head;
  volatile uint8_t Tail;
  uint8_t Buffer[MAX_BUFFER_SIZE];
  } RingBuffer_t;


  // Init RingBuffer
  void RingBufferInit(void);
  // Put data to RingBuffer
  void RingBufferPut( uint8_t data);
  // Check data is avalable in RingBuffer
  // return 0: Data is not avalable in Buffer
  // return 1: Data is avalable in Buffer
  state_data DataCheck(void);
  // Get data form Buffer
  uint8_t RingBufferGet(void);
  //Reset Buffer
  void ResetRingBuffer(void);
 /* Wait until a paricular string is detected in the Rx Buffer
* Return 1 on success and -1 otherwise
* USAGE: while (!(Wait_for("some string")));
*/
  int Wait_for( char *string);
  /* Copies the entered number of characters (blocking mode) from the Rx buffer into the buffer, after some particular string is detected
* Returns 1 on success and -1 otherwise
* USAGE: while (!(Get_after ("some string", 6, buffer)));
*/
int Get_affer(char *string, uint8_t numberofchars, char *buffertosave);
/* Peek for the data in the Rx Bffer without incrementing the tail count
* Returns the character
* USAGE: if (Uart_peek () == 'M') do something
*/
int Uart_peek();

/* Copies the required data from a buffer
 * @startString: the string after which the data need to be copied
 * @endString: the string before which the data need to be copied
 * @USAGE:: GetDataFromBuffer ("name=", "&", buffertocopyfrom, buffertocopyinto);
 */
void GetDataFromBuffer (char *startString, char *endString, char *buffertocopyfrom, char *buffertocopyinto);
/* Copy the data from the Rx buffer into the bufferr, Upto and including the entered string
* This copying will take place in the blocking mode, so you won't be able to perform any other operations
* Returns 1 on success and -1 otherwise
* USAGE: while (!(Copy_Upto ("some string", buffer)));
*/
int Copy_upto (char *string, char *buffertocopyinto);


#endif
