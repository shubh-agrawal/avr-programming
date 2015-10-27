
/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include "7seg.c"

/*----------------------------------------------------------------
-------------CONNECTION BETWEEN 74126 AND ATMEGA32---------------
-----------------------------------------------------------------*/
#define CONTROL_DDR	 	 DDRD
#define CONTROL_PORT 	 PORTD
#define Led_1     		  0
#define Led_2             1
#define CONTROL_MASK     0X03

/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/
void Init126_Ports(void);

/*----------------------------------------------------------------
-----------------MAIN FUNCTION------------------------------------
-----------------------------------------------------------------*/
void main()
{
unsigned int i=56,a=0;
Init126_Ports();
Init_Ports();
do
{
CONTROL_PORT|=_BV(Led_1); //switching ON first 7 segment to hold LSB
Display((i%10&0x0f));
//delay_ms(500);
CONTROL_PORT&=~_BV(Led_1); //switching OFF first 7 segment to hold LSB

CONTROL_PORT|=_BV(Led_2); //switching ON first 7 segment to hold LSB
a=i/10;
Display((a%10&0x0f));
//delay_ms(500);
CONTROL_PORT&=~_BV(Led_2); //switching OFF first 7 segment to hold LSB*/

}
while(1);
}


void Init126_Ports(void)
{
CONTROL_DDR=CONTROL_MASK; //setting ports for output
CONTROL_PORT&=~(_BV(Led_1)|_BV(Led_2)); //switching off 7 segment at starting
}