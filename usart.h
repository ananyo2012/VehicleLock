#include <inttypes.h>

#ifndef USART_H
#define USART_H
/****************************************************************************************************/

//Macros
#define RECEIVE_BUFF_SIZE 64
#define USART_RXC_VECT USART_RXC_vect	//This change from mcu to mcu. This is for mega8, mega16, mega32

#define F_CPU 16000000UL

#define UBRR_VALUE(baud) ((F_CPU/(baud<<4))-1)


//Varriables
volatile char URBuff[RECEIVE_BUFF_SIZE];	//USART Receive Buffer
volatile int8_t UQFront;
volatile int8_t UQEnd;

//Functions
void USARTInit(uint16_t ubrrvalue);

uint8_t UDataAvailable();

char UReadData();
void UWriteData(char data);

void UWriteString(const char *str);

void UReadBuffer(void *buff,uint16_t len);
void UFlushBuffer();




/****************************************************************************************************/


#endif


