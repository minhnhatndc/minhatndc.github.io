#include "app_uart_ringbuff.h"
RingBuffer_type Buffer;
RingBuffer_type *RingBuffer;
volatile uint16_t timeout;
// Init Uart RingBuffer
void app_uart_ringbuffer_init(void)
{
    RingBuffer->Head = 0;
    RingBuffer->Tail = 0;
    RingBuffer = &Buffer;

}
// Put data to Ring buffer
void app_uart_ringbuffer_put(uint8_t data){
    RingBuffer->Buffer[RingBuffer->Head]= data;
    RingBuffer->Head++;
    if(RingBuffer->Head == BUFFER_SIZE)
        {
            RingBuffer->Head = 0;
        }
}
// Check data is avalable in RingBuffer
// return 0: Data is not avalable in Buffer
// return 1: Data is avalable in Buffer
data_type app_uart_ringbuff_data_check(void)
{
    data_type state = DATA_IS_NOT_AVALABLE;
    uint16_t check = ((BUFFER_SIZE + RingBuffer->Head - RingBuffer->Tail))%BUFFER_SIZE;
    if(check == 0)
        {
            return state;
        }else{
            state = DATA_IS_AVALABLE;
            return state;
        }

}
  // Get data form Buffer
uint8_t app_uart_ringbuffer_get(void)
{
    uint8_t data = RingBuffer->Buffer[RingBuffer->Tail];
    RingBuffer->Tail++;
    if(RingBuffer->Tail == BUFFER_SIZE)
        {
            RingBuffer->Tail = 0;
        }
    return data;
}
// Reset RingBuffer
void app_uart_ringbuffer_reset(void)
{
    memset(RingBuffer->Buffer,'\0', BUFFER_SIZE);
    RingBuffer->Head = 0;
    RingBuffer->Tail = 0;
}
/* Peek for the data in the Rx Bffer without incrementing the tail count
* Returns the character
* USAGE: if (app_uart_ringbuffer_peek() == 'M') do something
*ret: 1 true, 0 false
*/
int app_uart_ringbuffer_peek(void)
{
    if(RingBuffer->Tail == RingBuffer->Head)
        {
            return -1;
        }else{
            return RingBuffer->Buffer[RingBuffer->Tail];
        }
}
/* Wait until a paricular string is detected in the Rx Buffer
* Return 1 on success and -1 otherwise
* USAGE: while (!(app_uart_ringbuffer_wait_for("some string")));
*/
int app_uart_ringbuffer_wait_for(char *string)
{   int len = strlen(string);
    int i = 0;
    loop:
    //timeout = TIME_OUT;
    while((app_uart_ringbuff_data_check()!=1));// && timeout);// let's wait for the data to show up
    //if( timeout == 0) return 0;
    while(app_uart_ringbuffer_peek() != string[i])
        {
            if(RingBuffer->Tail != RingBuffer->Head)
                {
                    RingBuffer->Tail++;
                }else{
                    return 0;
                }
        }
    while(app_uart_ringbuffer_peek() == string[i])// if we got the first letter of the string
        {   // now we will peek for the other letters too
            i++;
            RingBuffer->Tail++;
            if(i == len) return 1;
           // timeout= TIME_OUT;
            while(app_uart_ringbuff_data_check()!=1);//&&timeout);
           // if(timeout == 0) return 0;
        }
    if( i != len)
        {
            i = 0;
            goto loop;
        }
    if(i == len)
        {
            return 1;
        }else return 0;
}
/* Copies the entered number of characters (blocking mode) from the Rx buffer into the buffer, after some particular string is detected
* Returns 1 on success and -1 otherwise
* USAGE: while (!(app_uart_ringbuffer_get_after("some string", 6, buffer)));
* must be used after app_uart_ringbuffer_wait_for function
* get the entered number of characters after the entered string
*/
int app_uart_ringbuffer_get_after(char *string, uint8_t numberofchar, char *buffertosave )
{
    for( int i = 0;i < numberofchar; i++)
        {
           // timeout= TIME_OUT;
            while(app_uart_ringbuff_data_check()!=1);//&&timeout);
            //if(timeout == 0) return 0;
            buffertosave[i] = app_uart_ringbuffer_get();
        }
    return 1;
}

/* Copies the required data from a buffer
 * @startString: the string after which the data need to be copied
 * @endString: the string before which the data need to be copied
 * @USAGE:: app_uart_ringbuffer_GetDataFormBuffer("name=", "&", buffertocopyfrom, buffertocopyinto);
 */
void app_uart_ringbuffer_GetDataFormBuffer(char *startstring, char *endstring, char *buffercopyfrom, char *buffercopyinto)
{
    int startstringlength = strlen(startstring);
    int endstringlength = strlen(endstring);
    int idx = 0;
    int i = 0;
    int startposition = 0;
    int endposition = 0 ;

    loop1:
        //timeout = TIME_OUT;
        while(startstring[i] != buffercopyfrom[idx]) idx++;
        if(startstring[i] == buffercopyfrom[idx])
            {
                while(startstring[i] == buffercopyfrom[idx])
                    {
                        idx++;
                        i++;
                    }
            }
        if( i = startstringlength) startposition = idx;
        else {
            i = 0;
            goto loop1;
        }
        i = 0;
        loop2:
            while(endstring[i] != buffercopyfrom[idx]) idx++;
            if(endstring[i] == buffercopyfrom[idx])
                {
                    while( endstring[i]== buffercopyfrom[idx])
                        {
                            i++;
                            idx++;
                        }
                }
            if(i = endstringlength)
                {
                    endposition = idx- endstringlength;

                }else{
                    i = 0;
                    goto loop2;
                }
    i = 0;
    idx = 0;
    for(int j = startposition; j <endposition; j++)
        {
            buffercopyinto[i]= buffercopyfrom[j];
            i++;
        }
}
/* Copy the data from the Rx buffer into the bufferr, Upto and including the entered string
* This copying will take place in the blocking mode, so you won't be able to perform any other operations
* Returns 1 on success and -1 otherwise
* USAGE: while (!(app_uart_ringbuffer_copy_upto("some string", buffer)));
*/
/* copies the data from the incoming buffer into our buffer
 * Must be used if you are sure that the data is being received
 * it will copy irrespective of, if the end string is there or not
 * if the end string gets copied, it returns 1 or else 0
 * Use it either after (IsDataAvailable) or after (Wait_for) functions
 */
int app_uart_ringbuffer_copy_upto(char *string, char *buffertocopy)
{
        int len = strlen(string);
        int i = 0;
        int idx = 0;
        loop:
        while(app_uart_ringbuffer_peek() != string[i])
            {
                buffertocopy[idx] = RingBuffer->Buffer[RingBuffer->Tail];
                idx++;
                RingBuffer->Tail++;
                while(!app_uart_ringbuff_data_check());
            }
        while (app_uart_ringbuffer_peek() == string[i])
            {   i++;
                buffertocopy[idx++] = app_uart_ringbuffer_get();  
                //timeout = TIME_OUT;
                while(app_uart_ringbuff_data_check()!=1);//&&timeout);
                //if(timeout==0) return 0;
            }
    if( i != len)
        {
            i = 0;
            goto loop;
        }
    if(i == len)
        {
            return 1;
        }else return 0;
}
/* checks, if the entered string is present in the giver buffer ?
 */
static int check_for (char *str, char *buffertolookinto)
{
    int stringlength = strlen(str);
    int bufferlength = strlen(buffertolookinto);
    int idx = 0;
    int i = 0;
    loop:
        while(str[i] != buffertolookinto[idx])
            {
                idx++;
                if(idx > bufferlength) return 0;
            }
        if(str[i] == buffertolookinto[idx])
            {
                while(str[i]== buffertolookinto[idx])
                    {
                        i++;
                        idx++;
                    }
            }
        if( i == stringlength) return 1;
        else{
                i = 0;
                if(idx >= bufferlength) return 0;
                goto loop; 
            }
    if(i ==  stringlength) return 1;
    else return 0;
}