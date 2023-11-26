#include "ringuart.h"



/**
 * For Interrupt
 */
RingBuffer_t Buffer;
RingBuffer_t *RingBuffer; // Forr  RX Buffer

/**
 * Normal Variables
 */
uint8_t Test_Uart_Ring_Buf[MAX_BUFFER_SIZE];
uint8_t Test_Uart_Ring_Write_Index = 0;
uint8_t Test_Uart_Ring_Read_Index = 0;
uint8_t Test_RealBuf[MAX_BUFFER_SIZE];

void RingBufferInit(void){
  RingBuffer->Head = 0;
  RingBuffer->Tail = 0;
  RingBuffer = &Buffer;
  }

  void RingBufferPut( uint8_t data){
    RingBuffer->Buffer[RingBuffer->Head] = data;
    RingBuffer->Head++;
    if(RingBuffer->Head == MAX_BUFFER_SIZE) 
      {
       RingBuffer->Head =0;
      }
    }


  state_data DataCheck(void)
  {
    state_data state = data_unvalable;

    if(RingBuffer->Head== RingBuffer->Tail)
    {
      return state;
    }
   state = data_valable;
   return state; 
  }


  uint8_t RingBufferGet(void){
    uint8_t data;
    data = RingBuffer->Buffer[RingBuffer->Tail];
    RingBuffer->Tail++;
    if(RingBuffer->Tail == MAX_BUFFER_SIZE)
    {
      RingBuffer->Tail =0;
    }
    return data;
    }

void ResetRingBuffer(void)
{
memset(RingBuffer->Buffer,'\0',MAX_BUFFER_SIZE);
RingBuffer->Head = 0;
RingBuffer->Tail = 0;
}


/* Peek for the data in the Rx Bffer without incrementing the tail count
* Returns the character
* USAGE: if (Uart_peek () == 'M') do something
*/

int Uart_peek(){
  if(RingBuffer->Tail == RingBuffer->Head)
  {
    return -1;  
  }
  else {
  return RingBuffer->Buffer[RingBuffer->Tail];
  
  }

}
  /* Wait until a paricular string is detected in the Rx Buffer
* Return 1 on success and -1 otherwise
* USAGE: while (!(Wait_for("some string")));
*/
  int Wait_for( char *string)
  { 
    //timeout = TIME_OUT;
    int inx=0;
    int len = strlen(string);

    again:
    //while((DataCheck()!=1)&&(timeout));
      while(DataCheck() != 1); 
        //if (timeout == 0) return 0;
        while(Uart_peek()!= string[inx])
        {
         if(RingBuffer->Tail != RingBuffer->Head)
          {
            RingBuffer->Tail++;
          }else 
            { 
            return 0;
            }        
        }
      while( Uart_peek() == string[inx] )
      {
        inx++;
        RingBuffer->Tail++;
        if(inx == len ) return 1;
       // timeout = TIME_OUT;
        //while((!DataCheck()) && timeout);
        while(DataCheck() != 1); 
        //if(timeout == 0) return 0;

      }
    if(inx != len)
     {
      inx = 0;
      goto again;
     }
    if( inx = len)
     {
      return 1;
     }else return 0;
    

            
  }

  /* Copies the entered number of characters (blocking mode) from the Rx buffer into the buffer, after some particular string is detected
* Returns 1 on success and -1 otherwise
* USAGE: while (!(Get_after ("some string", 6, buffer)));
*/
/* must be used after wait_for function
 * get the entered number of characters after the entered string
 */
int Get_affer(char *string, uint8_t numberofchars, char *buffertosave)
{
  for(int i = 0; i< numberofchars; i++)
    {
      //timeout = TIME_OUT;
     // while((!DataCheck()) && timeout);
     // if (timeout == 0) return 0;
      while(DataCheck() != 1); 
      buffertosave[i] = RingBufferGet();

    }
  return 1;

}
/* Copies the required data from a buffer
 * @startString: the string after which the data need to be copied
 * @endString: the string before which the data need to be copied
 * @USAGE:: GetDataFromBuffer ("name=", "&", buffertocopyfrom, buffertocopyinto);
 */
void GetDataFromBuffer (char *startString, char *endString, char *buffertocopyfrom, char *buffertocopyinto)
{
  int StartStringLength = strlen(startString);
  int EndStringLength = strlen(endString);
  int i = 0;
  int inx = 0;
  int startposition = 0;
  int endposition = 0;
  loop1:
  while (startString[i] != buffertocopyfrom[inx]) inx++;
  if(startString[i] == buffertocopyfrom[inx])
    {
     while(startString[i] == buffertocopyfrom[inx])
      {
        i++;
        inx++;
      }
    }
   if(i == StartStringLength) startposition = inx;
   else
    {
    i=0;
    goto loop1;
    }
    i=0;
   loop2:
   while(endString[i] != buffertocopyfrom[inx]) inx++;
   if(endString[i] ==  buffertocopyfrom[inx])
    {
      while(endString[i] == buffertocopyfrom[inx])
        {
        i++;
        inx++;
        }
    }
    if( i == EndStringLength) endposition = inx;
    else
      {
      i=0;
      goto loop2;
      }
    i =0;
    inx = 0;
    for(int j = startposition; j< endposition; j++)
      {
      buffertocopyinto[inx] = buffertocopyfrom[i];
      inx++;
      }
    
}

/* Copy the data from the Rx buffer into the bufferr, Upto and including the entered string
* This copying will take place in the blocking mode, so you won't be able to perform any other operations
* Returns 1 on success and -1 otherwise
* USAGE: while (!(Copy_Upto ("some string", buffer)));
*/
/* copies the data from the incoming buffer into our buffer
 * Must be used if you are sure that the data is being received
 * it will copy irrespective of, if the end string is there or not
 * if the end string gets copied, it returns 1 or else 0
 * Use it either after (IsDataAvailable) or after (Wait_for) functions
 */

int Copy_upto (char *string, char *buffertocopyinto)
{
  int i = 0;
  int len = strlen(string);
  int idx= 0;
  loop:
  while(Uart_peek() != string[i])
    {
      buffertocopyinto[idx] = RingBuffer->Buffer[RingBuffer->Tail];
      RingBuffer->Tail++;
      idx++;
      while ( !DataCheck());
    }
   while(Uart_peek() == string[i])
    {
      i++;
      buffertocopyinto[idx++] = RingBufferGet();
      if( i = len) return 1;
      while (!DataCheck());
    }
   if(i != len)
    {
      i=0;
      goto  loop;
    }
   
   if( i == len)
    {
    return 1;
    }else return 0;

}