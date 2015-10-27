
//****************************************************************************
// Note: we used PS/2 mouse interaction code originally developed 
// for a Minesweeper Program by Chee Ming, Chaw and Elaine Siu for 476 in 2003 
// 
// They developed the following functions in this source file:
// 	mouse_send
// 	mouse_read
// 	poll_mouse
// 	reset_mouse
// The remaining functions we developed. 
//****************************************************************************

#include <Mega32.h>
#include <stdio.h> // sprintf
#include <delay.h> // delay_ms                    
#include <stdlib.h> 


//timeout values for each task
#define t1 100    // heart beat timer
#define t2 2000   //debug
#define t3 200     // for sampling mouse

//I like these 
#define begin {
#define end   }                                                      


#define DATA_IN  PINA.0 //data line from mouse
#define CLK_IN   PINA.1 //clock line from mouse
#define DATA_OUT PORTA.0 //data line from mouse
#define LOW      0
#define HIGH     1            

#define MOUSE_SPEED 2
#define CURSOR_X_MAX 127
#define CURSOR_X_MIN 0
#define CURSOR_Y_MAX 99
#define CURSOR_Y_MIN 0                          

#define CMD_UPDATE_CURSOR                0xf1

register unsigned char data @4; 
                                                                          
#asm    
        .equ PORTA=0x1b
        .equ DDRA=0x1a        

        .MACRO DATALOW
        sbi DDRA,0    ;DDRA.0=1
        cbi PORTA,0   ;PORTA.0=0
        .ENDM
        
        .MACRO RELDATA
        cbi DDRA,0    ;DDRA.0=0
        sbi PORTA,0   ;PORTA.0=1
        .ENDM
        
        .MACRO CLKLOW
        sbi DDRA,1    ;DDRA.1=1
        cbi PORTA,1   ;PORTA.1=0
        .ENDM
        
        .MACRO RELCLK
        cbi DDRA,1    ;DDRA.1=0
        sbi PORTA,1   ;PORTA.1=1
        .ENDM

#endasm
                 

#define MAXROW 10
#define MAXCOL 15

//the three task subroutines
   
void mouse_send(char data);         // Send 1 byte of data to mouse.   
unsigned char mouse_read(void);     // Read 1 byte of data from mouse  
void initialize(void); //all the usual mcu stuff                     

          
unsigned int time1;	//timeout counters        
unsigned int time2;         
unsigned int time3;                      
char str[80];
unsigned char mouse_x,mouse_y,mouse_status;             


int cursor_x, cursor_y;                           //current cursor position
unsigned char last_cursor_x,last_cursor_y;
             
#define TOOL_POINT	0
#define TOOL_LINE	1
#define TOOL_SPRAY	2
#define TOOL_ERASER	3
#define TOOL_FILL	4
#define TOOL_RECT	5
#define TOOL_OVAL	6
#define TOOL_CLEAR	7 //not an active tool!


unsigned char cur_tool;
unsigned char switch_tool;
unsigned char button_dragging;
unsigned char button_up,button_down;



         
//**********************************************************

//timer 0 overflow ISR
interrupt [TIM0_COMP] void timer0_overflow(void)
begin       
  //Decrement the 2 times if they are not already zero
  if (time1>0)  --time1;                                
  if (time2>0)  --time2;
end       


interrupt [TIM1_COMPA] void t1_cmpA(void)  
begin    
	//Decrement the time if not already zero
   if (time3>0)	--time3;
end

//**********************************************************     
// Send a byte of data to mouse. It consist of 1 start bit, 8 data bits, 1 parity bit, 1 stop bit. 
// After the mouse recieved the data correctly, the mouse will send back an ACK bit.
// "data" is the data to be sent. parity bit is odd parity of the 8 bits data.   
// Data is read by mouse at rising edge of CLK.
void mouse_send(char data)
begin 
  unsigned char Bit,parity,i;
  #asm("RELDATA");        
  #asm("RELCLK");
  delay_us(300);
  #asm("CLKLOW");               //Pull CLK Low
  delay_us(300);                // need to wait for at least 100us
  #asm("DATALOW");              // Pull DATA Low when holding CLK Low
  delay_us(100);
  #asm("RELCLK");                //Release CLK and continue to hold Data Low. This is also the Start bit.
  delay_us(40);
  while(CLK_IN!=LOW) { }        // wait for CLK to go low 
  i=0; Bit=0b00000001;                                                     
  parity=1;                     // odd parity = 1 ^ bit0 ^ bit1 ^ ... ^ bit7
     
  while(i<=8)
    begin
        
      if(i==8)                  // If i=8 send parity bit otherwise, send the next bit of data.
      { if(parity)              // DATA_OUT=(i==8? parity : (data & Bit) );
          { #asm("RELDATA"); }          
        else 
          { #asm("DATALOW"); }
       }
      else
      { if(data & Bit)
          { #asm("RELDATA"); }
        else
          { #asm("DATALOW"); }
      }
      while(CLK_IN!=HIGH) {}                    // wait for CLK to go high. mouse read data at rising edge.
      while(CLK_IN!=LOW)  {}                    // wait for CLK to go low. 
      parity=parity ^ DATA_OUT;                 // update parity bit.
      Bit=Bit<<1;                               // Prepare mask
      i++;
    end
  #asm("RELDATA");                              // Release Data line. This is the stop bit. 
  delay_us(50);                                 // give time for transient to settle.
  while(DATA_IN!=LOW) {}                        // wait for Data line to go low               
  while(CLK_IN!=LOW)  {}                        // wait for CLK to go low. Start of ACK from mouse.
  while(DATA_IN==LOW || CLK_IN==LOW) {}         // End of ACK from mouse.               
  #asm("CLKLOW");                               // Inhibit the mouse from transmitting data.

end                                                           
//**********************************************************
// This function read a byte of data from the mouse and return the byte
unsigned char mouse_read(void)
begin
  unsigned char i,t[10];  

  #asm("RELCLK");         //release the CLK 
  #asm("RELDATA");        //release DATA line.
  delay_us(200);          // wait for at least 100us
  while(CLK_IN==HIGH)  {} // wait for falling edge. we read data at falling edge of CLK
  i=0;  
  delay_us(5);
  
  while(CLK_IN==LOW)   {} // wait for CLK to go high.
  while(i<=8)
    begin
      while(CLK_IN==HIGH) {} // wait for falling edge of CLK   
        t[i]=DATA_IN;        // store each bit
        i++;       
      while(CLK_IN==LOW) {}
    end   
  while(CLK_IN==LOW) {}  
  data=128*t[7]+64*t[6]+32*t[5]+16*t[4]+8*t[3]+4*t[2]+2*t[1]+t[0]; //combine the collected bits into a byte        

  #asm("CLKLOW");          //pull CLK low to prevent mouse from sending data until being asked
  return data;
  
end                   
                 
//******************************************                  
//Update the cursor's variables with new location
void update_cursor(void)
begin          
     
	last_cursor_x = cursor_x;
	last_cursor_y = cursor_y;

	if (mouse_y!=0)           //calculate vertical position according to its sign and value                    
		if ((mouse_status & 0b00100000)!=0) { cursor_y=cursor_y+(256-mouse_y); } 
		else { cursor_y=cursor_y-mouse_y; }     
	if (mouse_x!=0)           //calculate horizontal position according to its sign and value                    
		if ((mouse_status & 0b00010000)!=0) { cursor_x=cursor_x-(256-mouse_x); } 
		else { cursor_x=cursor_x+mouse_x; }                                                   
       
    	if (cursor_x>CURSOR_X_MAX) cursor_x=CURSOR_X_MAX;    // limit cursor to within the screen
   	if (cursor_x<CURSOR_X_MIN) cursor_x=CURSOR_X_MIN;    // 100 x 128 pixels screen
   	if (cursor_y>CURSOR_Y_MAX) cursor_y=CURSOR_Y_MAX;
   	if (cursor_y<CURSOR_Y_MIN) cursor_y=CURSOR_Y_MIN;

	//determine the state of the mouse button to be sent to tv:
    	button_up = 0;
	//if selecting tool do not send mouse button state to tv
    	if(cursor_x >= 10) 
	begin	
   	   if( (mouse_status & 0b00000001) != 0) //left button down
    		begin     
    	  		if (button_down || button_dragging)
    			begin
    				button_down = 0;
    				button_dragging = 1;
    				button_up = 0;
    			end
    	  		else               
    			begin
    				button_down = 1;
    				button_up = 0; 
    				button_dragging = 0;
    			end
    		end	
    		else
    		begin
			if(button_down || button_dragging) 
    			begin
    				button_down = 0;
    				button_dragging = 0;
    			    	button_up = 1;
    			end
    		end 
 	end
    
    	//button is held, resrict mouse position so user cannot draw on toolbar
	if( button_dragging == 1 && (mouse_status & 0b00000001) != 0) 
	begin
		if (cursor_x < 10)
			cursor_x = 10;
		if(cursor_y > 80 && cursor_x < 25)
		begin
			if(-mouse_y > -mouse_x)
    				cursor_y = 80;
    	    		else
    				cursor_x = 25;
		end
	end
    
	//change the current tool:
	switch_tool = 0;
    	if( (mouse_status & 0b00000001) != 0 )
    	begin
    		if( cursor_x < 10 && cursor_y < 80)
    		begin
			//select tool to be used based on mouse click position:
    			if(cursor_y < 10)
    				cur_tool = 0;
    			else if(cursor_y > 10 && cursor_y < 20)
    				cur_tool = 1;   
    			else if(cursor_y > 20 && cursor_y < 30)
    				cur_tool = 2;   
    			else if(cursor_y > 30 && cursor_y < 40)
    				cur_tool = 3;
    			else if(cursor_y > 40 && cursor_y < 50)
    				cur_tool = 4;
    			else if(cursor_y > 50 && cursor_y < 60)
    				cur_tool = 5;
    			else if(cursor_y > 60 && cursor_y < 70)
    				cur_tool = 6;
    			else if(cursor_y > 70 && cursor_y < 80)
    				cur_tool = 7;
    			switch_tool = 1;
    		end
    	end            
end                                                               
 


//*******************************************                                 
// This routine poll the mouse's status and movement data.
void poll_mouse(void)
begin  
    mouse_send(0xeb);                     //Request data from mouse
    mouse_read();                         //Read the acknowledge byte
    mouse_status=mouse_read();            //Read mouse status
    mouse_x=mouse_read();                 //Read mouse horizontal movement
    mouse_y=mouse_read();                 //Read mouse vertical movement
end

//**********************************************
// This function is called to reset the mouse and put it into remote mode.
// In remote mode, mouse only send data upon request from the microcontroller.
// This function is called when manual reset of the mouse is required. This is for
// overcoming interference problem from some unknown EM field.
void reset_mouse(void)
begin
  mouse_send(0xff);     // reset mouse
  mouse_read();         // read mouse acknowledge (0xFA)
  mouse_read();         // read some blank bytes.  
  mouse_read();     
  mouse_send(0xf0);     // Set mouse to remote mode.
  mouse_read();         // read mouse acknowledge (0xFA)           
  delay_ms(100);
end             
//**********************************************
     

//*********************************************
// Send mouse information to tv screen:
// including cursor locations, button status and tool change
void update_TV(void)
begin
	unsigned char bstatus;
  	putchar(CMD_UPDATE_CURSOR);
    	putchar(cursor_x);
    	putchar(cursor_y);
	if(button_down==1)
		bstatus = 0b01;  // 01-initial button down
	else if(button_dragging==1) 
   		bstatus = 0b10;  //10-button drag
 	else if(button_up==1) 
   		bstatus = 0b11;  //11-button release
  	else
   		bstatus=0b00;    //nothing clicked
   		
    	putchar( (bstatus & 3) | ((switch_tool & 1) << 2) | ((cur_tool & 7) << 3) );
    	putchar(last_cursor_x);
    	putchar(last_cursor_y);
    	putchar(0xFF);
     
     switch_tool = 0;
end
//**********************************************

//Main 
void main(void)
begin  
  initialize();
       
  //main task scheduler loop 
  while(1) 
  begin      
    	//Regularly poll mouse and send info to tv
    	if(time3 == 0)
    	begin 
    		time3=t3;
      		poll_mouse();      // Poll mouse
      		update_cursor();   //update cursor location
	 	update_TV();       // update screen
      		delay_ms(15);  
	end  
	if(time1==0)                      // heart beat LED
	begin
          time1=t1;                                   // reset timer
          PORTD.7=PORTD.7^1;                          // toggle heart beat LED
	end
	if (PIND.6==0)
		reset_mouse();                  // Manually reset mouse
      
    end   // end while
end      //end main  


#define lineTime 1018   

//********************************************************** 
//Initialize
void initialize(void)
begin      
  #asm("cli");

  //init timer 1 to send mouse info at regular interval
  OCR1A = lineTime; 	//One NTSC line
  TCCR1B = 9; 		//full speed; clear-on-match
  TCCR1A = 0x00;	//turn off pwm and oc lines
  TIMSK = 0x12;		//enable interrupt T1 cmp 
  
  OCR0 = 250;  	//set the compare re to 250 time ticks
  //prescalar to 64 and turn on clear-on-match
  TCCR0=0b00001011;	
  
  //init the task timers
  time1=t1;    // Heart beat timer
  time2=t2;
  time3=t3;    // debounce timer

  //init ports                                                               
  DDRA = 0b11111100;    // PA0 DATA IN, PA1 CLOCK IN     
  DDRD.6=0;             // Use for mouse reset
  PORTD.6=1;            // enable pullup resistor
  DDRD.7=1;             // used for heart beat indicator  
  DDRD.3=1;
  
  //init UART:
  UCSRB = 0x10 + 0x08 ;
  UBRRL = 16; //57600 bps      
  UBRRH = 0;                         
   
  DDRA.0=1; 
  PORTA.0=1;
  delay_ms(500); 
  DDRA.0=0;
    
   DDRA.1=1; 
  PORTA.1=1;
  delay_ms(500); 
  DDRA.1=0;
  
  // init mouse variables
  cursor_x=5;
  cursor_y=5;          
  #asm("RELCLK");
  #asm("RELDATA");  
  
  //init mouse state  
  reset_mouse();    
  
  #asm("sei")
end 