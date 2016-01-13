#include <avr/io.h>

#include <util/delay.h>

#include "myutils.h"

#ifndef _LCD_H
#define _LCD_H



/*_________________________________________________________________________________________*/

/************************************************
	LCD CONNECTIONS
*************************************************/

#define LCD_DATA D		//Port AVR's PD3-PD6 are connected to LCD's DB4-DB7
#define LCD_DATA_POS 3

#define LCD_E D			//Enable/strobe signal (E)-> PD7
#define LCD_E_POS	PD7	//Position of enable in above port

#define LCD_RS B		//Register Select signal (RS)-> PB2
#define LCD_RS_POS PB2

#define LCD_RW B		//Read/Write signal (R/W) ->PB0
#define LCD_RW_POS PB0


/***********************************************

LCD Type Selection
Uncomment Just one of them

************************************************/

//#define LCD_TYPE_202	//For 20 Chars by 2 lines

//#define LCD_TYPE_204	//For 20 Chars by 4 lines

#define LCD_TYPE_162	//For 16 Chars by 2 lines

//#define LCD_TYPE_164	//For 16 Chars by 4 lines


//************************************************

	


//************************************************

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010
#define LS_NONE	 0B00000000



/***************************************************
			F U N C T I O N S
****************************************************/



void LCDInit(uint8_t style);

void LCDWriteString(const char *msg);
void LCDWriteFString(const char *msg);

void LCDWriteInt(int val,unsigned int field_length);
void LCDGotoXY(uint8_t x,uint8_t y);

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();





/***************************************************
			F U N C T I O N S     E N D
****************************************************/


/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome() LCDCmd(0b00000010);

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteFStringXY(x,y,msg) {\
LCDGotoXY(x,y);\
LCDWriteFString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}
/***************************************************/




/*_________________________________________________________________________________________*/
#endif