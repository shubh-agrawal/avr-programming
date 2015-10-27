#include <mega32.h>
#include <stdio.h>                      
#include <stdlib.h> 
#include <math.h> 
#include <delay.h>   

//timeout values for each task
#define t1 500    // heart beat timer
#define t2 2000   //debug
#define t3 20     // for debounce  

//I like these 
#define begin {
#define end   }                                                      

#define DATA_IN  PINA.0
#define CLK_IN   PINA.1
#define DATA_OUT PORTA.0
#define LOW      0
#define HIGH     1            

#define TXC UCSRA.6      //Transmit complete
#define RCX UCSRA.7      //Receive complete

#define MOUSE_SPEED 2
#define CURSOR_X_MAX 127
#define CURSOR_X_MIN 0
#define CURSOR_Y_MAX 99
#define CURSOR_Y_MIN 0                          
#define TOTAL_MINES 25

#define CMD_CURSOR                0xf1
#define CMD_CLICK                 0xf2      
#define CMD_DRAW_ONE_ICON         0xf3
#define CMD_GAMES_START           0xf4
#define CMD_GAMES_STOP            0xf5
#define CMD_GAMES_REMAINING_MINES 0xf6
#define CMD_GAMES_RESTART         0xf7
#define CMD_GAMES_WIN             0xf8

#define ICON_COVERED 12


#define MAX_RAND 32767          

register unsigned char data @4; 

//State machine state names
#define NoClick 1 
#define MaybeClick 2
#define Clicked 3
#define MaybeNoClick 4
                                                                               
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
void debounce(void);  	// 
   
void mouse_send(char data);         // Send 1 byte of data to mouse.   
unsigned char mouse_read(void);     // Read 1 byte of data from mouse  
void send_remaining_mines(void);     // Send remaining mines number to uc1           
void send_icon(void);
void open_blanks(unsigned char row, unsigned char col);
void initialize(void); //all the usual mcu stuff                     

          
unsigned char reload;	//timer 0 reload to set 1 mSec
unsigned int time1;	//timeout counters        
unsigned int time2;         
unsigned int time3;      
//unsigned char data1;                  
char str[80];
unsigned char mouse_x,mouse_y,mouse_status;             

unsigned char ClickFlagL, ClickFlagR;			//message indicating a button Click 
unsigned char ClickStateL,ClickStateR;			//state machine  

unsigned char Board[MAXROW][MAXCOL];

int cursor_x, cursor_y;                           //current cursor position
unsigned char cursor_row,cursor_col,icon;         //current cursor location on board
unsigned char last_cursor_row,last_cursor_col,last_icon,win;
unsigned char exploded_row,exploded_col;          // location of exploded mine

unsigned char gameover,gamestart,winflag;  //games variables    
char remaining_mines;
         
//**********************************************************
//timer 0 overflow ISR
interrupt [TIM0_OVF] void timer0_overflow(void)
begin       
  //reload to force 1 mSec overflow
  TCNT0=reload;
  //Decrement the 3 times if they are not already zero
  if (time1>0)  --time1;                                
  if (time2>0)  --time2;
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
//**********************************************************   
// Initialize the Board array with c. usually used with c=0
void init_board(unsigned char c)
begin  
   unsigned char row=0,col=0;  
   
   for(row=0;row<MAXROW;row++)
     for(col=0;col<MAXCOL;col++)
          {Board[row][col]=c; }   // assign c to each cell
end                          
//****************************************    
// Return the number of mines in the neighborhood of Board[row][col].
unsigned char mine_count(unsigned char row, unsigned char col)
begin       
  char i,j;
  unsigned count=0;
         
  for(i=-1;i<=1;i++)    // count the 8 surronding neighbors of [row][col]
    for(j=-1;j<=1;j++)
       if(row+i>=0 && row+i<=MAXROW-1 && col+j>=0 && col+j<=MAXCOL-1 && (i!=0 || j!=0)) 
           if((Board[row+i][col+j] & 0b10000000)!=0) count++;  // if mine found here, increment count
  return count;
end
//*****************************************
// Generate n number of mines at random location in the board.
void generate_mine(unsigned char n)
begin
   unsigned char count=0,row,col;
   int temp1,temp2;
   
   temp2=MAXROW*MAXCOL;
   while(count<n)            //repeat the random mines gereration process until n number of mines are generated
   { 
     temp1=(float)rand()/MAX_RAND*temp2;  // generate a number that is within 0 and MAXROW*MAXCOL
     row=(unsigned char)temp1/MAXCOL;     // compute the row corresponds to this random number
     col=temp1-(row*MAXCOL);              // col
     if ((Board[row][col] & 0b10000000)==0)             // if not already a mine in this cell
       { Board[row][col]=Board[row][col] | 0b10000000;  // set bit 7 to indicate a mine
         count++;
       }
   }
end                  
//******************************************                  
//Update the cursor's variables with new location
void update_cursor(void)
begin          

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
    
    cursor_row= cursor_y-1<0 ? 0 :(cursor_y-1)>>3;      // compute and limit cursor within the board.
    cursor_col= cursor_x-8<0 ? 0 :(cursor_x-8)>>3;      // lower bound
    if (cursor_row>=MAXROW) cursor_row=MAXROW-1;        // upper bound
    if (cursor_col>=MAXCOL) cursor_col=MAXCOL-1;                            
end                                                               
//******************************************
// This routine update the current cursor location with the cursor indicator.
void update_icon(void)
begin
   unsigned char data,uncovered,marked,mine;
   
   data=Board[cursor_row][cursor_col] & 0b00000111;
   uncovered=Board[cursor_row][cursor_col] & 0b00001000;
   marked=Board[cursor_row][cursor_col] & 0b00010000;   
   mine=Board[last_cursor_row][last_cursor_col] & 0b10000000;
   
   if (uncovered==0)            // if cell is covered
      begin
        icon=24;                // icon is a covered cell with cursor indicator
      end
   else
      begin                     // if cell is uncovered
         if (data<=8 && data>=0)  // if it is a number
           begin
             icon=data+12;        // icon is the number with with cursor indicator 
           end           
         if (data==0) icon=25;    // if the cell is a blank, icon is blank with cursor indicator
         if (mine) icon=22;      // if there is a mine there, icon is the mine with cursor indicator
      end
      
   if (marked) icon=21;         // if the cell has been marked, icon is the flag with cursor indicator
   if (gameover && cursor_row==exploded_row && cursor_col==exploded_col && win==0) 
     begin
            icon=23;         //exploded mine with cursor indicator 
     end

end                     
//******************************************
// Restore the image at the last cursor location       
void restore_icon(void)
begin
   unsigned char data,uncovered,marked,mine;

   data=Board[last_cursor_row][last_cursor_col] & 0b00000111;
   uncovered=Board[last_cursor_row][last_cursor_col] & 0b00001000;
   marked=Board[last_cursor_row][last_cursor_col] & 0b00010000;   
   mine=Board[last_cursor_row][last_cursor_col] & 0b10000000;
   
   if (uncovered==0) icon=12;  // if it is covered, icon is a covered cell with no cursor indicator
   else
      begin
        if (data<=8 && data>=0)
           begin
             icon=data;        // if it is a number, icon is a number with no cursor indicator
           end                
        if (data==0) data=0;   // if it is a blank, icon is a blank with no cursor indicator
        if (mine) icon=10;     // if it is a mine, icon is a mine with no cursor indicator
      end 
   if (marked) icon=9;         // if it is marked, icon is a flag with no cursor indicator
   if (gameover && last_cursor_row==exploded_row && last_cursor_col==exploded_col && win==0) 
     begin
            icon=0x0b;        //ex[oded mine with no cursor indicator
     end

end
//************************************      
// Count the number of mines in each cell's neighbors.
void board_mine_count(void)
begin
   unsigned char row=0,col=0;  
   
   for(row=0;row<MAXROW;row++)
     for(col=0;col<MAXCOL;col++)
              Board[row][col]=Board[row][col] | (mine_count(row,col) & 0b00000111) ;
end                                
//******************************************
// To uncover a cell when being clicked
void uncover_cell(void)
begin                  
     unsigned char marked;
     
     marked=Board[cursor_row][cursor_col] & 0b00010000  ;

     if(marked==0) Board[cursor_row][cursor_col]=Board[cursor_row][cursor_col] | 0b00001000; //set bit 3
     if(marked==0 && (Board[cursor_row][cursor_col] & 0b10000000) ) gameover=1;
end   
//******************************************
// mark the cell at [row][col]
// if the cell is already mark, unmark it.
void mark_cell(void)
begin
  unsigned data;
  
      data=Board[cursor_row][cursor_col];         // number contained in this cell 
      if ((data & 0b00001000)==0)                 // if the cell is still covered
        begin
           Board[cursor_row][cursor_col]=Board[cursor_row][cursor_col] ^ 0b00010000; //toggle the uncover bit. 
           ClickFlagR=0;                                      
           
           if (Board[cursor_row][cursor_col] & 0b00010000) // if it is marked
             begin
               remaining_mines--;                   //reduce remaining mines
               send_remaining_mines();              // send it to uc1
             end
           else
             begin
               remaining_mines++;                  // otherwise, increase remaining mines
               send_remaining_mines();             // send it to uc1
             end          
           send_icon();                            // Update the current cursor location.
        end
end      
//******************************************
// send message to uc1 to draw an icon 
void send_icon(void)
begin             
        last_cursor_row=cursor_row;
        last_cursor_col=cursor_col;
        update_cursor();
        //if(cursor_row!=last_cursor_row || cursor_col!=last_cursor_col) //if cursor has moved.
          begin
            restore_icon();
            putchar(CMD_CURSOR);
            putchar(last_cursor_row);  // restore images in the last cursor location
            putchar(last_cursor_col);
            putchar(icon);    
            
            update_icon();           
            putchar(cursor_row);       // draw new cursor on new location 
            putchar(cursor_col);
            putchar(icon);                
            putchar(0xff);
            
          end
end                                
//*****************************************
// This routine check if all mines are marked correctly.
// It is being called when remaining_mines==0
unsigned char check_winning(void)
begin           
   unsigned char wrong,marked,mine,row,col;
   
   wrong=0;                    
   for(row=0;row<MAXROW;row++)               // check of each and every cell
      for(col=0;col<MAXCOL;col++)                                                   
         begin
            marked=Board[row][col] & 0b00010000;   
            mine=Board[row][col] & 0b10000000;
            if ( (marked && mine==0) || (marked==0 && mine!=0) ) wrong++;  // if wrong, increment.
         end
   return wrong;
end
//*****************************************
// This routine is called when player hit a mine. This routine will open up the whole board
// and show where the mine were exploded.
void open_board(void)
begin
  unsigned char r,c;
  unsigned char data,uncovered,marked,mine,temp;
   
  for(r=0;r<MAXROW;r++)
    for(c=0;c<MAXCOL;c++)
       begin                                   
          temp=Board[r][c]; 
          Board[r][c]=temp | 0b00001000;          // set the uncover bit. all cells are uncovered.
          data=temp      & 0b00000111;            // The number of mine in neighbors
          marked=temp    & 0b00010000;            // The marked flag
          mine=temp      & 0b10000000;            // the mine bit
   
              if (data<=8 && data>0) icon=data;    // if it is a number
              if (data==0) icon=0;                 // if it an empty spot
              if (mine) icon=10;                   // if it is a mine
              if (marked) icon=9;                  // if it is a flag

            putchar(CMD_DRAW_ONE_ICON);     // get uc1 to draw the icon
            putchar(r);  
            putchar(c);
            putchar(icon);    
            putchar(0xff);             // terminator 
            delay_ms(20);              // gives time for uc1 to read the data before sending another block.
       end
   if (win==0)
   begin
      putchar(CMD_DRAW_ONE_ICON);  // draw the exploded mine
      putchar(exploded_row);       
      putchar(exploded_col);
      putchar(0x0b);    
      putchar(0xff);               // terminator
   end
end
//*****************************************
//Send remaining number of mines to uc1
void send_remaining_mines(void)
begin
   putchar(CMD_GAMES_REMAINING_MINES);
   putchar(remaining_mines);
   putchar(0xff);                            // terminator
   delay_ms(20);
end
//*****************************************
// initialize all the variables used in the games.
void init_games()
begin
  //init games variable
  gameover=0;                   
  gamestart=0;             
  winflag=0;
  win=0;
  icon=0;          
  cursor_row=0;                                         
  cursor_col=0;
  mouse_x=0;
  mouse_y=0;
  mouse_status=0;                             
  last_cursor_row=0;
  last_cursor_col=0;
  last_icon=0;
  exploded_row=0;
  exploded_col=0;

  remaining_mines=TOTAL_MINES;       // Started with TOTAL_MINES number of mines
  init_board(0);                     // init Board array
  generate_mine(TOTAL_MINES);        // Generate random mines
  board_mine_count();                // count the number of mines for each cell 
  send_remaining_mines();            // send number of mines to uc1
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
//*******************************************
// This routine is called when player left clicked
// It uncover cell and check if a mine is hit. If a mine is uncovered, games will turn into gameover state
// When it uncovered an empty cell, it will call open_blanks() to uncover a series of connected blanks.
void left_click_task()
begin
       if (gamestart==0 && gameover==0 && win==0)  // The first left click start the game
          begin
            gamestart=1;   
            putchar(CMD_GAMES_START);              // ask uc1 to start timer
            putchar(0xff);        
            delay_ms(50);
          end
       uncover_cell();                             // uncover the cell at current cursor position
       send_icon();                                // Update the uncovered cell on TV.
       if ((Board[cursor_row][cursor_col] & 0x00000111)==0) open_blanks(cursor_row,cursor_col); //if cell is empty, call open_blanks
       ClickFlagL=0;                               // reset flag to avoid entering this function more than once in one click.
       if (gameover==1 && gamestart==1 && win==0)  // if game is over
         begin
            exploded_row=cursor_row;               // record the location of the mine hit.
            exploded_col=cursor_col;
            putchar(CMD_GAMES_STOP);               //Send command to uc1 to stop timer.
            putchar(0xff);  
            delay_ms(50);         
            gamestart=0;                                     
            open_board();                          // Open up the whole board.
         end                  
end
//********************************************    
// This routine is called when player right clicked
// It mark a cell with flag if the games is still running.
// It will restart the games and send message to uc1 to refresh the screen if the games has over.
void right_click_task()
begin
      mark_cell();            // mark a cell with flag
      ClickFlagR=0;           // reset the click flag
      if (gameover || (win && winflag))    //if game over or the games has be won
        begin            
          initialize();                    //restart the games
          init_games();     
          putchar(CMD_GAMES_RESTART);        // tell uc1 to restart
          putchar(0xff);                     // send terminator
          delay_ms(100);
          send_remaining_mines();          // send new remaining_mines number to uc1
        end                     
      if (remaining_mines==0 && check_winning()==0) win=1;  // if remaining_mines=0 then check if all mines have been marked correctly
end               
//**********************************************
// This is a recursive function to uncover up a series of blank covered cells.
// It is called when an empty cell is uncovered.
// It check for the 8 neighbors of the supplied location [row][col] and recusively looks for 
// neighbors of the cells that is empty and being uncovered.
void open_blanks(unsigned char row, unsigned char col)
begin                             
    char i,j,data;
    for(i=-1;i<=1;i++)    // Check for mines in neighbors
      for(j=-1;j<=1;j++)
         if(row+i>=0 && row+i<=MAXROW-1 && col+j>=0 && col+j<=MAXCOL-1 && (i!=0 || j!=0)) 
           begin
              data=(Board[row+i][col+j] & 0b10000000) || (Board[row+i][col+j] & 0b00010000);
              if(data!=0) return ;  // if found one mine in the neighbors, stop this recursive function.
           end 
// the above code checked for any mines in the neighbors. If there is no mine in the 8 neighbors,
// the following codes uncover the 8 neighbors and call this function recursively if each of the cell
// also has no mine in its 8 neigbors.       
    for(i=-1;i<=1;i++)    // open up all cells in neighbors
      for(j=-1;j<=1;j++)
         if(row+i>=0 && row+i<=MAXROW-1 && col+j>=0 && col+j<=MAXCOL-1 && (i!=0 || j!=0)) 
           begin
             if ((Board[row+i][col+j] & 0b00001000)==0)   // if cell is covered
               begin       
                 Board[row+i][col+j]=Board[row+i][col+j] | 0b00001000;   // uncover the cell
                 data=Board[row+i][col+j] & 0b00000111;                  // extract icon to be displayed here.
                 putchar(CMD_DRAW_ONE_ICON);        // ask uc1 to update the screen   
                 putchar(row+i);                 
                 putchar(col+j);
                 putchar(data);                
                 putchar(0xff);       
                 delay_ms(25); 
                 open_blanks(row+i,col+j);
               end
           end
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

//Main 
void main(void)
begin  
  initialize();                  // initialize hardware and variables
  init_games();                  // initialize games variables
  delay_ms(500);                 // give some delay.

            
  //main task scheduler loop 
  while(1) 
    begin       
      poll_mouse();                                    // Poll mouse
      if (time3==0) 	debounce();                    // debounce mouse clicks    
      if (mouse_y!=0 || mouse_x!=0) send_icon();       // if mouse has moved, update screen
      delay_ms(15);                                    // delay to give time for TV screen update
    
      if(time1==0)                                    // heart beat LED
        begin
          time1=t1;                                   // reset timer
          PORTD.7=PORTD.7^1;                          // toggle heart beat LED
        end
      
      if (ClickFlagR) right_click_task();            // handle right click task
      if (ClickFlagL)  left_click_task();            // handle left click task
      if (PIND.6==0) reset_mouse();                  // Manually reset mouse
      
      if (win && winflag==0)          // if player won, change games status to won and print "you win"
         begin
            gamestart=0;
            winflag=1;                // to indicate that this loop has been executed. so that it won't be executed next time
            putchar(CMD_GAMES_WIN);   // send command to uc1 to display "You won"
            putchar(0xff);
            delay_ms(20);
            open_board();             // Open up the board
            delay_ms(20);
          
         end
    end   // end while
end      //end main  
//********************************************************** 
// debounce the left and right clicks from mouse.
void debounce(void) 
begin
  time3=t3;     //reset the task timer   
   
   switch (ClickStateR)
  begin
     case NoClick: 
        if ((mouse_status & 0b00000010)!=0) ClickStateR=MaybeClick;
        else ClickStateR=NoClick;
        break;
     case MaybeClick:
        if ((mouse_status & 0b00000010)!=0) 
        begin
           ClickStateR=Clicked;   
           ClickFlagR=1;
        end
        else ClickStateR=NoClick;
        break;
     case Clicked:  
        if ((mouse_status & 0b00000010)!=0) ClickStateR=Clicked; 
        else ClickStateR=MaybeNoClick;    
        break;
     case MaybeNoClick:
        if ((mouse_status & 0b00000010)!=0) ClickStateR=Clicked; 
        else 
        begin
           ClickStateR=NoClick;
           ClickFlagR=0;
        end    
        break;
  end               
  
  switch (ClickStateL)
  begin
     case NoClick: 
        if ((mouse_status & 0b00000001)!=0) ClickStateL=MaybeClick;
        else ClickStateL=NoClick;
        break;
     case MaybeClick:
        if ((mouse_status & 0b00000001)!=0) 
        begin
           ClickStateL=Clicked;   
           ClickFlagL=1;
        end
        else ClickStateL=NoClick;
        break;
     case Clicked:  
        if ((mouse_status & 0b00000001)!=0) ClickStateL=Clicked; 
        else ClickStateL=MaybeNoClick;    
        break;
     case MaybeNoClick:
        if ((mouse_status & 0b00000001)!=0) ClickStateL=Clicked; 
        else 
        begin
           ClickStateL=NoClick;
           ClickFlagL=0;
        end    
        break;
  end               
end
//********************************************************** 
//Initialize
void initialize(void)
begin
//set up the ports
           
  //set up timer 0
  reload=256-250; 	//value for 1 Msec at 16 MHz 
  TCNT0=reload;
  TIMSK=1;		//turn on timer 0 overflow ISR (Interrupt service routine)
  TCCR0=3;		//prescalar to 64 [1/(16x10^6)]*64*250 =1ms.
  //init the task timers
  time1=t1;    // Heart beat timer
  time2=t2;
  time3=t3;    // debounce timer
  
  //init UART 
  UCSRB = 0x10 + 0x08 ;
  UBRRL = 16; //57600 bps      
  UBRRH = 0;                     
  
  //init clicks debouncing state machine variables
  ClickFlagL=0;
  ClickFlagR=0;
  ClickStateL=NoClick;
  ClickStateR=NoClick;
  
  //init ports                                                               
  DDRA = 0b11111100;    // PA0 DATA IN, PA1 CLOCK IN     
  DDRD.6=0;             // Use for mouse reset
  PORTD.6=1;            // enable pullup resistor
  DDRD.7=1;             // used for heart beat indicator
  
  // init mouse variables
  cursor_x=0;
  cursor_y=0;          
  cursor_row=0;
  cursor_col=0;
  #asm("RELCLK");
  #asm("RELDATA");  

  //init mouse state  
  reset_mouse();
  #asm
  	sei
  #endasm 
end 

