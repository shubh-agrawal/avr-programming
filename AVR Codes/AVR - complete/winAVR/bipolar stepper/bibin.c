/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include<avr/io.h>


/*----------------------------------------------------------------
-------------CONNECTION BETWEEN L293D AND ATMEGA32---------------
-----------------------------------------------------------------*/
#define L293D_DDR	 DDRC
#define L293D_PORT 	 PORTC
#define Pin_1         0
#define Pin_2		  1
#define Pin_3         2
#define Pin_4		  3
#define L293D_Mask   0x0f


/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/
void Init_Ports(void);
void delay_ms(unsigned char time_ms);

void main()
{
int i;
int steps[]={15,13,12,14};
Init_Ports();
i=0;
do
{
L293D_PORT=steps[i];
i++;
if(i>4) i=0;
delay_ms(50);
}
while(1);
}



/*----------------------------------------------------------------
-----------------FUNCTIONS TO INITIALIZE PORTS--------------------
-----------------------------------------------------------------*/
void Init_Ports(void)
{
L293D_DDR|=(_BV(Pin_1 )|_BV(Pin_2)|_BV(Pin_3 )|_BV(Pin_4)); //setting pins for output
L293D_PORT&=~(_BV(Pin_1 )|_BV(Pin_2)|_BV(Pin_3 )|_BV(Pin_4));//starting motor is Off
}
/*----------------------------------------------------------------
--------FUNCTION TO GENERATE DELAY IN MILLISECONDS----------------
-----------------------------------------------------------------*/
void delay_ms(unsigned char time_ms)
{
	unsigned short delay_count = F_CPU / 400;

	unsigned short cnt;
	asm volatile ("\n"
                  "L_dl1%=:\n\t"
                  "mov %A0, %A2\n\t"
                  "mov %B0, %B2\n"
                  "L_dl2%=:\n\t"
                  "sbiw %A0, 1\n\t"
                  "brne L_dl2%=\n\t"
                  "dec %1\n\t" "brne L_dl1%=\n\t":"=&w" (cnt)
                  :"r"(time_ms), "r"((unsigned short) (delay_count))
	);
}

