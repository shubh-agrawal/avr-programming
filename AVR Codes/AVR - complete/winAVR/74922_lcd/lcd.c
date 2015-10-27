/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include<avr/io.h>


/*----------------------------------------------------------------
-------------CONNECTION BETWEEN LCD AND ATMEGA32-----------------
-----------------------------------------------------------------*/
#define DATA_DDR	 DDRA
#define DATA_PORT 	 PORTA


#define CONTROL_DDR	 	 DDRD
#define CONTROL_PORT 	 PORTD
#define Enable_Pin		  6
#define RegSelect_Pin     4
#define ReadWrite_Pin     5
#define CONTROL_MASK     0X70


/*----------------------------------------------------------------
-------------CONTROL BITS OF LCD --------------------------------
-----------------------------------------------------------------*/

#define Set_Enable  				CONTROL_PORT|=_BV(Enable_Pin)
#define Clear_Enable 				CONTROL_PORT&=~_BV(Enable_Pin)
#define Write_Lcd			    	CONTROL_PORT&=~_BV(ReadWrite_Pin)
#define Read_Lcd			   		CONTROL_PORT|=_BV(ReadWrite_Pin)
#define Select_InstructionRegister 	CONTROL_PORT&=~_BV(RegSelect_Pin)
#define Select_DataRegister	    	CONTROL_PORT|=_BV(RegSelect_Pin)
#define Data_Lcd(a)					DATA_PORT=a
#define delay(a)					delay_ms(a)



/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/
void Init_Ports(void);
void Init_Lcd(void);
void delay_ms(unsigned char time_ms);
void Lcd_Send(unsigned char a);





/*----------------------------------------------------------------
-----------------SEND A CHARACTER TO LCD-------------------------
-----------------------------------------------------------------*/
void Lcd_Send(unsigned char a)
{
Select_DataRegister;
Write_Lcd;
Data_Lcd(a);
Set_Enable;
delay(30);
Clear_Enable;
delay(30);
}

 	
	



/*----------------------------------------------------------------
-----------------FUNCTIONS TO INITIALIZE PORTS--------------------
-----------------------------------------------------------------*/
void Init_Ports(void)
{
DATA_DDR=0XFF; //Setting data port for output
CONTROL_DDR=CONTROL_MASK;//setting selected pins of control port for output
CONTROL_PORT&=~(_BV(Enable_Pin)|_BV(RegSelect_Pin )|_BV(ReadWrite_Pin)); //setting values to 0 at starting
}




/*----------------------------------------------------------------
------------FUNCTION TO INITIATE LCD -----------------------------
-----------------------------------------------------------------*/
void Init_Lcd(void)
{
char init[10];
 int i;
 init[0] = 0x01; 
 init[1] = 0x38;
 init[2] = 0x0c;
 init[3] = 0x06;
 init[4] = 0x80;
Select_InstructionRegister;
Write_Lcd;
	for(i=0;i<5;i++)
	{
	Data_Lcd(init[i]);
	Set_Enable;
	delay(30);
	Clear_Enable;
	delay(30);
	}
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
