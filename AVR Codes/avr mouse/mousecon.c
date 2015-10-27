//mousecon.c

#include <Mega163.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
                              
#define t1 1
#define t2 10
#define LCD_width 16
#define Aref 2.51        
#define ready 0        
#define almost_ready 1
#define but_press 2
#define but_release1 3
#define but_release2 4

#asm
    .equ __lcd_port=0x15 ;portc
#endasm

#include <lcd.h> // LCD driver routines

char lcd_buffer2[17];
char xout, yout;	//x and y voltage/coordinate readings from ADC
char xsend, ysend;      //Outputs to serial
char xInt, yInt;	//x and y coordinates for calibration purposes
int Ain, bytessent; 	//raw A to D number
unsigned char time1, time2, reload, test0, butinfo;
unsigned char datapack[3];
unsigned int button0, button1, mousekill, but_state; 
unsigned char enable, writeonce;
unsigned char posEdge;

void initialize(void);
void task1(void);	//Detect button pushes/mouse clicks
void task2(void);   	//ADC for the mouse position

//timer 0 overflow ISR       
interrupt [TIM0_OVF] void timer0_overflow(void)
{       
  //reload to force 1 mSec overflow
  TCNT0=reload;
  
  //Decrement the three times if they are not already zero     
  if (time1>0) --time1;  
  if (time2>0) --time2;
}    

//Read the value of the ADC  
interrupt [ADC_INT] void adc_done(void)
{ 
   Ain = ADCH;
}
                                          
//The external interrupt is used to let Windows set up the serial mouse driver
//and let Windows initalize our project for serial mouse communcation
interrupt [EXT_INT0] void external_int0(void)
{
	//Looks for first positive edge
	if (posEdge == 0)
	{                                             
	  posEdge = 1;
	  return;
	}
 	
	//Looks for 2nd positive edge
	else if(posEdge == 1)
	{                                 
	  UDR = 0x4D;  //Send an ASCII 'M' to let Windows know this is a serial mouse
	  writeonce++;
	}                   
	              
	//After 15 groups of two positive edges, disable the external interrupts and start sending
	//mouse coordinate data
	if(writeonce == 15)
	{
	  enable = 1;  //Flag to start sending mouse coordinates
	  GIMSK = 0;   //Disable the external interrupts
	} 
}

void main(void)
{ 
  initialize();   
  lcd_init(LCD_width);      	//initialize the display
  lcd_clear();       		//clear the display
  lcd_gotoxy(0,0);              //format a message        
  lcd_putsf("Voltagex = ");     //Display the 'x' voltage/coordinate on the LCD
  lcd_gotoxy(0,1);
  lcd_putsf("Voltagey = ");     //Display the 'y' voltage/coordinate on the LCD
                                    
  while(1)
  {
    if((enable == 1) && (time1 == 0)) task1(); 
    if((enable == 1) && (time2 == 0) && (mousekill != 1)) task2();
  }
}
             
void task1(void)
{
  time1 = t1;
  
  //Debounce State machine for the button pushes
  switch(but_state)
  {   
    //No button push State
    case(ready):     
      if(~PINB != 0)
      {                 
      	  butinfo = PINB;
          but_state = almost_ready;
      } 	
      else
      {           
          test0 = 0;
       	  but_state = ready;
      } 	                        
    break;                        
    
    //Maybe-button push detected
    case(almost_ready):
       if(PINB == butinfo)
          but_state = but_press;
       else
          but_state = ready;
    break;
    
    //Button push definately detected
    case(but_press):             
       if(PINB == butinfo)
       {                   
       	 if(PINB == 0xfe)  //Left mouse click
       	   button0 = 1;           
	 
	 else if (PINB == 0xef)  //Right mouse click
	   button1 = 1; 
	   
	 if(PINB == 0xfb)  //Button to disable the mouse
	 {
	   if(test0 == 0)
	   {
	   	mousekill = (~mousekill)&0x1;
		test0 = 1;
   	   }             
	 }
	 
	 but_state = but_press;
       }  
       else 
         but_state = but_release1;                       
     break;
     
     //Maybe Button is released		                              
     case(but_release1):
       if(PINB == butinfo)
      	 but_state = but_press;
     else
      	 but_state = but_release2;
     break;
		
     //Last check if button is released		
     case(but_release2):      
       if(PINB == butinfo)
     	but_state = but_release1;
       else
       {
         but_state = ready;
         button0 = 0;
         button1 = 0;
         butinfo = 0;          
         test0 = 0;
       }
   }   
}       

void task2(void)
{
  time2 = t2;  
  ADMUX = 0b11100000; 
  //get reading on x voltage/coordinate
  #asm
  	sleep
  #endasm

  xout = Ain;                 
	
  if(xInt == 0)  //If this is first reading on x, calibrate
    xInt = xout;		

  //get reading on y voltage/coordinate
  ADMUX = 0b11100001;
  #asm
    	sleep
  #endasm
	 
  yout = Ain;   
  if(yInt == 0)  //If this is first reading on y, calibrate
    yInt = yout;
  
  //Write x and y voltage/coordinate to LCD	  
  sprintf(lcd_buffer2,"%-i",xout); 
  lcd_gotoxy(11,0);     
  lcd_puts(lcd_buffer2);       	
  sprintf(lcd_buffer2,"%-i",yout); 
  lcd_gotoxy(11,1);     
  lcd_puts(lcd_buffer2);      
 	
  if(bytessent == 0)
  {  //ready to send first byte
  	
     xsend = xout-xInt;
     ysend = yout-yInt;
  
     //Buffer to let mouse pointer sit still when no movement is detected	   
     if((xsend <= 3) || (xsend >= -3))
     	xsend = 0;
 	   	
     if((ysend <= 3) || (ysend >= -3))
      ysend = 0;
 	   	
     //1st byte    bit7,6  left push          right push       vert bit 7,6      hori bit 7,6 
     datapack[0] = 0xc0|((button0&0x1)<<5)|((button1&0x1)<<4)|((ysend>>4)&0xc)|((xsend>>6)&0x3);
     UDR = datapack[0];
     bytessent++;
  }
  else if(bytessent == 1)
  {  //one byte was sent and UDR buffer is empty 
     //2nd byte    bit7,6 hori bit 0 - 5
     datapack[1] = 0x80|(xsend&0x3f);       
     UDR = datapack[1];
     bytessent++;
  }
  else if(bytessent == 2)
  {
     //3rd byte    bit7,6  vert 0 - 5
     datapack[2] = 0x80|(ysend&0x3f);     
     UDR = datapack[2];
     bytessent++;
     bytessent = 0;
  }  	  
}

void initialize(void)
{ 
  //Initialize UART Communcaitons
  UCSRB = 0x08;
  UBRR = 207;   //1200 bps communcations
  
  //set up the ports                                    
  DDRD=0x00;    //PORT D is an input for external interrupts
  DDRA=0x00;	//Analog ADC
  DDRB=0x00;	//PORT B is an input for the button presses.
   
  //set up timer 0     
  reload=256-63; //value for 1 Msec  
  TCNT0=reload;	 //preload timer 1 so that is interrupts after 1 mSec.
  TCCR0=3;	 //prescalar to 64
  TIMSK=1;	 //turn on timer 0 overflow ISR  
  GIMSK=0x40;    //Turns on external interrupts    
  bytessent = 0; 
  button0 = 0;
  button1 = 0;
  mousekill = 0;
  test0 = 0;
  but_state = ready;
  //init the task timers
  time1=t1;
  time2=t2;
  //init the A to D converter 
  //channel zero/ left adj /int Aref
  //!!!DISCONNECT Aref jumper!!!!
  //Sets Voltage reference to internal voltage reference and right adjusts ADC result
  ADMUX = 0b11100000;
 
  //enable ADC and set prescaler to 1/64*8MHz=125,000
  //and set int enable
  ADCSR = 0x80 + 0x05 + 0x08; 
  MCUCR = 0b01010011; //enable sleep and choose ADC mode    
  UDR = 0x00;  
  //External interrupt enable to trigger on the rising edge. 
             
  //Mouse initialization variable
  enable = 0;              
  posEdge = 0;
  PORTB = 0xff;  //Turn on internal pullups for buttons                      
  writeonce = 0;
  xInt = 0;
  yInt = 0;

  //crank up the ISRs
  #asm
  	sei
  #endasm          
 
}  