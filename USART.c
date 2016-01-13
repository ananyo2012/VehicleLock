#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "usart.h"

void USARTInit(uint16_t ubrrvalue)
{
	//Setup q
	UQFront=UQEnd=-1;

	//Set Baud rate
	UBRRH=(unsigned char)(ubrrvalue>>8);
	UBRRL=(unsigned char)ubrrvalue;

	/*Set Frame Format
	
	Asynchronous mode
	No Parity
	1 StopBit
	char size 8

	*/

	UCSRC=(1<<URSEL)|(3<<UCSZ0);

	/*Enable Interrupts
	RXCIE- Receive complete
	UDRIE- Data register empty

	Enable The recevier and transmitter

	*/

	UCSRB=(1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	sei();

}

//The USART ISR
ISR(USART_RXC_VECT)
{
	//Read the data
	char data=UDR;

	//Now add it to q

	if(((UQEnd==RECEIVE_BUFF_SIZE-1) && UQFront==0) || ((UQEnd+1)==UQFront))
	{
		//Q Full
		UQFront++;
		if(UQFront==RECEIVE_BUFF_SIZE) UQFront=0;
	}
	

	if(UQEnd==RECEIVE_BUFF_SIZE-1)
		UQEnd=0;
	else
		UQEnd++;


	URBuff[UQEnd]=data;

	if(UQFront==-1) UQFront=0;

}

char UReadData()
{
	char data;
	
	//Check if q is empty
	if(UQFront==-1)
		return 0;
	
	data=URBuff[UQFront];
	
	if(UQFront==UQEnd)
	{
	//If single data is left
	//So empty q
	UQFront=UQEnd=-1;
	}
	else
	{
		UQFront++;

		if(UQFront==RECEIVE_BUFF_SIZE)
		UQFront=0;
	}

	return data;
}

void UWriteData(char data)
{
	//Wait For Transmitter to become ready
	while(!(UCSRA & (1<<UDRE)));

	//Now write
	UDR=data;
}

uint8_t UDataAvailable()
{
	if(UQFront==-1) return 0;
	if(UQFront<UQEnd)
		return(UQEnd-UQFront+1);
	else if(UQFront>UQEnd)
		return (RECEIVE_BUFF_SIZE-UQFront+UQEnd+1);
	else
		return 1;
}

void UWriteString(const char *str)
{
	while((*str)!='\0')
	{
		UWriteData(*str);
		str++;
	}
}

void UReadBuffer(void *buff,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		((char*)buff)[i]=UReadData();
	}
}
void UFlushBuffer()
{
	while(UDataAvailable()>0)
	{
		UReadData();
	}
}
