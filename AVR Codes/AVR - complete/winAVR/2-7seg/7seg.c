/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include<avr/io.h>

/*----------------------------------------------------------------
-------------CONNECTION BETWEEN 7 segment AND ATMEGA32-----------
-----------------------------------------------------------------*/
#define DATA_DDR	 DDRC
#define DATA_PORT 	 PORTC
#define Pin_a     		0
#define Pin_b     		1
#define Pin_c     		2
#define Pin_d     		3
#define Pin_e     		4
#define Pin_f     		5
#define Pin_g     		6
#define Pin_Dec        		7
#define DATA_MASK     	      0XFF




/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/
void Init_Ports(void);
void Display(int a);
void delay_ms(unsigned char time_ms);

  
  
/*----------------------------------------------------------------
-----------------FUNCTIONS TO INITIALIZE PORTS--------------------
-----------------------------------------------------------------*/
  void Init_Ports(void)
  
  {
  DATA_DDR = DATA_MASK; //for setting data pin's for output
  }
  
/*----------------------------------------------------------------
-----------------FUNCTIONS TO DISPLAY VALUES----------------------
-----------------------------------------------------------------*/  
  void Display(int a)
  {
  switch(a)
  {
  case 0:  
			DATA_PORT|=_BV(Pin_g);
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_b)|_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_f));
			break;
			
  case 1:
			
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_f)|_BV(Pin_g));
			DATA_PORT&=~(_BV(Pin_b)|_BV(Pin_c));
			break;
			
  case 2:  
			
  
			DATA_PORT|=(_BV(Pin_c)|_BV(Pin_f));
			DATA_PORT&=~(_BV(Pin_b)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_a)|_BV(Pin_g));
			break;
			
	
  case 3:  
			DATA_PORT|=(_BV(Pin_e)|_BV(Pin_f));
			DATA_PORT&=~(_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_a)|_BV(Pin_b)|_BV(Pin_g));
			break;
			

  case 4:  
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_d)|_BV(Pin_e));
			DATA_PORT&=~(_BV(Pin_c)|_BV(Pin_b)|_BV(Pin_f)|_BV(Pin_g));
			break;
			
  case 5:  
			DATA_PORT|=(_BV(Pin_b)|_BV(Pin_e));
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_f)|_BV(Pin_g));
			break;
			
  case 6:  
			DATA_PORT|=(_BV(Pin_a)|_BV(Pin_b));
			DATA_PORT&=~(_BV(Pin_c)|_BV(Pin_d)|_BV(Pin_f)|_BV(Pin_g)|_BV(Pin_e));
			break;
			
  case 7:  
			DATA_PORT|=(_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_f)|_BV(Pin_g));
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_c)|_BV(Pin_b));
			break;
			
  case 8:  
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_d)|_BV(Pin_e)|_BV(Pin_c)|_BV(Pin_b)|_BV(Pin_f)|_BV(Pin_g));
			break;
		
  case 9:  
			DATA_PORT|=(_BV(Pin_d)|_BV(Pin_e));
			DATA_PORT&=~(_BV(Pin_a)|_BV(Pin_c)|_BV(Pin_b)|_BV(Pin_f)|_BV(Pin_g));
			break;
					
	}}

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



