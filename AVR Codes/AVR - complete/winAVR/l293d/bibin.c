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
#define L293D_Mask   0x03
/*----------------------------------------------------------------
-------------CONNECTION BETWEEN INPUT AND ATMEGA32---------------
-----------------------------------------------------------------*/
#define Input_DDR	 DDRD
#define Input_PIN 	 PIND
#define IPin_1         6
#define IPin_2		  5
#define Input_Mask   0x60

/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/
void Init_Ports(void);
void forward(void);
void backward(void);
void brake(void);
void stop(void);


void main()
{
unsigned int a,b;
Init_Ports();
do
{
a=((Input_PIN&_BV(IPin_1))>>(IPin_1));
b=((Input_PIN&_BV(IPin_2))>>(IPin_2));
if(a==1&&b==1) brake();
if(a==0&&b==0) stop();
if(a==0&&b==1) forward();
if(a==1&&b==0) backward();
}
while(1);



}

/*----------------------------------------------------------------
-----------------FUNCTIONS TO INITIALIZE PORTS--------------------
-----------------------------------------------------------------*/
void Init_Ports(void)
{
L293D_DDR|=(_BV(Pin_1 )|_BV(Pin_2)); //setting pins for output
L293D_PORT&=~(_BV(Pin_1 )|_BV(Pin_2));//starting motor is Off
Input_DDR&=~(_BV(5)|_BV(6));//making as input pins
}


void forward(void)
{
L293D_PORT|=_BV(Pin_1 );
L293D_PORT&=~_BV(Pin_2);
}


void backward(void)
{
L293D_PORT|=_BV(Pin_2);
L293D_PORT&=~_BV(Pin_1 );
}


void brake(void)
{
L293D_PORT|=(_BV(Pin_2)|_BV(Pin_1 ));
}


void stop(void)
{
L293D_PORT&=~(_BV(Pin_1 )|_BV(Pin_2));
}

