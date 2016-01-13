#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "lcd.h"
#include "sim300.h"

int main(void)
{
	LCDInit(LS_BLINK|LS_ULINE);

	LCDClear();
	LCDWriteStringXY(2,0,"Engine Lock");
	LCDWriteStringXY(4,1,"Project");
	_delay_ms(6000);

	DDRC=0x00;
	DDRB=0xFF;
	PORTC|=(1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3)|(1<<PORTC4)|(1<<PORTC5);

	int i,pressed=0;
	char s[35];

	for(i=1;i<=3;i++)
	{
		strcpy(s,"");

		LCDClear();
		LCDWriteString("Enter Password:");
		LCDGotoXY(0,1);

		while(1)
		{
			if((PINC&(1<<PINC1))==0)
			{
				if(pressed==0)
				{
					strcat(s,"1");
					LCDWriteStringXY((strlen(s)-1),1,"*");
					pressed=1;
				}
			}
			else if((PINC&(1<<PINC2))==0)
			{
				if (pressed==0)
				{
					strcat(s,"2");
					LCDWriteStringXY((strlen(s)-1),1,"*");
					pressed=1;
				}
			}
			else if((PINC&(1<<PINC4))==0)
			{
				if (pressed==0)
				{
					strcat(s,"3");
					LCDWriteStringXY((strlen(s)-1),1,"*");
					pressed=1;
				}
			}
			else  if((PINC&(1<<PINC5))==0)
			{
				if (pressed==0)
				{
					strcat(s,"4");
					LCDWriteStringXY((strlen(s)-1),1,"*");
					pressed=1;
				}
			}
			else if((PINC&(1<<PINC3))==0)
			{
				break;
			}
			else
			pressed=0;
		}
		if(strcmp(s,"1234")==0)
		{
			LCDClear();
			LCDWriteStringXY(2,0,"Lock Opened!");
			PORTB=0b00000010;
			while(1);
		}
		else
		{
			LCDClear();
			LCDWriteString("Wrong Password!");
			if(i<3)
			{
				LCDWriteStringXY(3,1,"Try Again!");
			}
			_delay_ms(2000);
		}
	}

	LCDClear();
	LCDWriteStringXY(4,0,"Exceeded");
	LCDWriteStringXY(2,1,"3 attempts!");
	_delay_ms(6000);

	LCDClear();
	LCDWriteString("Initializing ...");

	int8_t r=SIM300Init();
	_delay_ms(1000);

	switch(r)
	{
		case SIM300_OK:
		LCDWriteStringXY(0,1,"OK !");
		break;
		case SIM300_TIMEOUT:
		LCDWriteStringXY(0,1,"No response");
		while(1);
		case SIM300_INVALID_RESPONSE:
		LCDWriteStringXY(0,1,"Inv response");
		while(1);
		case SIM300_FAIL:
		LCDWriteStringXY(0,1,"Fail");
		while(1);
		default:
		LCDWriteStringXY(0,1,"Unknown Error");
		while(1);
	}
	_delay_ms(2000);

	LCDClear();

	char imei[16];
	r=SIM300GetIMEI(imei);

	if(r==SIM300_TIMEOUT)
	{
		LCDWriteString("Comm Error !");
		while(1);
	}

	LCDWriteString("Device IMEI:");
	LCDWriteStringXY(0,1,imei);
	_delay_ms(2000);

	LCDClear();

	char man_id[48];
	r=SIM300GetManufacturer(man_id);

	if(r==SIM300_TIMEOUT)
	{
		LCDWriteString("Comm Error !");
		while(1);
	}

	LCDWriteString("Manufacturer:");
	LCDWriteStringXY(0,1,man_id);
	_delay_ms(2000);

	LCDClear();
	LCDWriteString("Checking SIMCard");
	_delay_ms(1000);

	r=SIM300IsSIMInserted();

	if(r==SIM300_SIM_NOT_PRESENT)
	{
		LCDWriteStringXY(0,1,"SIM Not Present");
		while(1);
	}
	else if(r==SIM300_TIMEOUT)
	{
		LCDWriteStringXY(0,1,"Comm Error !");
		while(1);
	}
	else if(r==SIM300_SIM_PRESENT)
	{
		LCDWriteStringXY(0,1,"SIM Card Present");
		_delay_ms(2000);
	}

	LCDClear();
	LCDWriteString("SearchingNetwork");

	int tries=0;
	while (1)
	{
		r=SIM300GetNetStat();
		if(r==SIM300_NW_SEARCHING)
		{
			_delay_ms(50);
			tries++;
			if(tries==600)
			break;
		}
		else
		break;
	}

	if(r==SIM300_NW_REGISTERED_HOME)
	{
		LCDWriteStringXY(0,1,"Network Found");
		_delay_ms(1500);
	}
	else
	{
		LCDWriteStringXY(0,1,"Cant Connt to NW!");
		while(1);
	}

	LCDClear();

	char pname[32];
	r=SIM300GetProviderName(pname);
	if(r==0)
	{
		LCDWriteString("Comm Error !");
		while(1);
	}

	LCDWriteString(pname);
	_delay_ms(2000);


	LCDClear();
	LCDWriteString("Sending Message");
	_delay_ms(1000);

	uint8_t ref;
	r=SIM300SendMsg("+918900253322","Unauthorized Access!",&ref);
	if(r==SIM300_OK)
	{
		LCDWriteStringXY(0,1,"Success");
		LCDWriteIntXY(9,1,ref,3);
	}
	else if(r==SIM300_TIMEOUT)
	{
		LCDWriteStringXY(0,1,"Time out !");
	}
	else
	{
		LCDWriteStringXY(0,1,"Fail  !");
	}

	while(1);
}
