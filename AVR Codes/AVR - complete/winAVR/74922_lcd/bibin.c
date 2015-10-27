/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include "lcd.c"


/*----------------------------------------------------------------
-------------CONNECTION BETWEEN 74922 AND ATMEGA32---------------
-----------------------------------------------------------------*/
#define IC_DDR	     DDRC
#define IC_PORT 	 PORTC
#define IC_PIN 		 PINC
#define Pin_A         0
#define Pin_B		  1
#define Pin_C         2
#define Pin_D		  3
#define Pin_DA        4
#define Pin_OE		  5
#define IC_Mask  	 0x10 //OE for output remaining for input
#define Output_DDR    DDRD
#define Output_PORT   PORTD

#define Output_Enable IC_PORT&=~_BV(Pin_OE) //for enabling the IC


/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/
void Init_Ports922(void);

void main()
{
unsigned int i;
Init_Ports();
Output_Enable;
//lcd initializationsa
	Init_Ports();
	Init_Lcd();

do
{
i=IC_PIN&0X0F;
if(i<10) i+=0x30; //in case of decimal values
if(i>9) i+=55 ;//for showing alphabets
Lcd_Send(i);
while(!((IC_PIN&_BV(Pin_DA))>>Pin_DA));

}
while(1);
}



/*----------------------------------------------------------------
-----------------FUNCTIONS TO INITIALIZE PORTS--------------------
-----------------------------------------------------------------*/
void Init_Ports922(void)
{
IC_DDR=IC_Mask; //setting OE pins for output,remaining for input
Output_DDR=0XFF;
}