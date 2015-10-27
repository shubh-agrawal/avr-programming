  #define F_CPU 16000000               //CHECK!!!!!!!!!!!!!!!!!

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<inttypes.h>

#define BIT(b) (1<<(b))
#define CLEARBIT(x,b) x&=~b;
#define SETBIT(x,b) x|=b;
#define CHECKBIT(x,b) (x)&(b)



void move_front();
void move_back();
void move_right();
void move_left();
void move_front_half();

                  

void main()
{

DDRC=0xFF;
int i;


/*
PORTB=0xFF;
_delay_ms (500);
PORTB=0x00;
_delay_ms (500);


float t=1.65,r,l=1.68,m;
float t_=0.65,r_,l_=1.70,m_;
float t2=0.65,r2,l2=0.15,m2;

r=20-t;
r_=20-t_;
r2=20-t2;
int k=0,k_=0,ul=39,ul_=27;
int k2=0,ul2=23;
m=20-l-t;
m_=20-l_-t_;
m2=20-l2-t2;

    while(k<ul)
	{
	 PORTC=0xFF;
     _delay_ms(t);
	 PORTC=0x00;
	
	
   PORTD=0xFF;
     _delay_ms(l);
	 PORTD=0x00;
	_delay_ms(m);
	
	k++;
   
    }
	
	

while(k_<ul_)
	{
	 PORTC=0xFF;
     _delay_ms(t_);
	 PORTC=0x00;
	
	
   PORTD=0xFF;
     _delay_ms(l_);
	 PORTD=0x00;
	 
	_delay_ms(m_);
	
	k_++;
   
    
}

while(k2<ul2)
	{
	 PORTC=0xFF;
     _delay_ms(t2);
	 PORTC=0x00;
	
	
   PORTD=0xFF;
     _delay_ms(l2);
	 PORTD=0x00;
	_delay_ms(m2);
	
	k2++;
   
    }*/
  
   	while(1)
  {
  move_front_half();
 
  }
	
	
	}
void move_front_half()
		 {
		
		 int k=0;
         int upperlimit=20;
		  
		 /*upperlimit=time for legs to take that position/20ms
		                                              
		
		 */ 
	      int r=0;
		 while(r<upperlimit)    /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 02 legs stand in air 
								  in 75 deg pos & 13 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(0.15);
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(2.0);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(3.0);
		   CLEARBIT(PORTC,BIT(3));

		   SETBIT(PORTC,BIT(4));_delay_ms(1.527);      //75 deg position
		   CLEARBIT(PORTC,BIT(4));                    
           SETBIT(PORTC,BIT(5));_delay_ms(0.12);      //30 deg position  
		   CLEARBIT(PORTC,BIT(5));
           SETBIT(PORTC,BIT(6));_delay_ms(1.68);
		   CLEARBIT(PORTC,BIT(6));
		   SETBIT(PORTC,BIT(7));_delay_ms(2.5);
		   CLEARBIT(PORTC,BIT(7));
            _delay_ms(7.873);
		   
           
		   
		   r++;

		   }
		     while(k<10)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 02 legs get down to 75
								   deg pos & 13 legs to 30 deg pos on ground*/
		   
		    
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(3.0);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.15);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.65);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(3.0);
			 CLEARBIT(PORTC,BIT(3));
              
		   SETBIT(PORTC,BIT(4));_delay_ms(0.15);      //75 deg position
		   CLEARBIT(PORTC,BIT(4));                    
           SETBIT(PORTC,BIT(5));_delay_ms(0.12);      //30 deg position  
		   CLEARBIT(PORTC,BIT(5));
           SETBIT(PORTC,BIT(6));_delay_ms(1.70);
		   CLEARBIT(PORTC,BIT(6));
		   SETBIT(PORTC,BIT(7));_delay_ms(2.5);
		   CLEARBIT(PORTC,BIT(7));
		   
		   _delay_ms(8.73);
		  
		   

		  
			 k++;
			 }
	 int upperlimit_=20;                   
		                                              
		int r_=0;
		int k_=0;										  
		    
			  
		 while(r_<upperlimit_)         /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 13 legs stand in air 
								  in 75 deg pos & 02 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {  
		   
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(3.0);   //0 deg pos
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(2.5);    //90 deg pos
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(0.65);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(3));

         
		   SETBIT(PORTC,BIT(4));_delay_ms(2.5);      //30 deg position
		   CLEARBIT(PORTC,BIT(4));                    
           SETBIT(PORTC,BIT(5));_delay_ms(2.00);      //75 deg position  
		   CLEARBIT(PORTC,BIT(5));
           SETBIT(PORTC,BIT(6));_delay_ms(0.15);
		   CLEARBIT(PORTC,BIT(6));
		   SETBIT(PORTC,BIT(7));_delay_ms(1.527);
		   CLEARBIT(PORTC,BIT(7));
           _delay_ms(3.55);
            
		  
          
		   r_++;
		   }

          

		   while(k_<10)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 13 legs get down to 75
								   deg pos & 02 legs to 30 deg pos on ground*/
		   
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(3.0);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.15);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.65);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(3.0);
			 CLEARBIT(PORTC,BIT(3));
               
			 SETBIT(PORTC,BIT(5));_delay_ms(1.58);      //75 deg position  
		     CLEARBIT(PORTC,BIT(5));
			
			 SETBIT(PORTC,BIT(7));_delay_ms(0.15);
		     CLEARBIT(PORTC,BIT(7));
		   
           _delay_ms(11.47);
             
		  
          
			 k_++;
			 }
			 
		   return 0;
		   }


         void move_front()
		 {
		
		 int k=0;
         int upperlimit=20;
		  
		 /*upperlimit=time for legs to take that position/20ms
		                                              
		
		 */ 
	      int r=0;
		 while(r<upperlimit)    /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 02 legs stand in air 
								  in 75 deg pos & 13 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(3));

		   SETBIT(PORTC,BIT(4));_delay_ms(4.0);      //75 deg position
		   CLEARBIT(PORTC,BIT(4));                    
           SETBIT(PORTC,BIT(5));_delay_ms(0.5);      //30 deg position  
		   CLEARBIT(PORTC,BIT(5));
           SETBIT(PORTC,BIT(6));_delay_ms(4.0);
		   CLEARBIT(PORTC,BIT(6));
		   SETBIT(PORTC,BIT(7));_delay_ms(4.0);
		   CLEARBIT(PORTC,BIT(7));
            _delay_ms(11.00);
		   
           
		   r++;

		   }

         

		   while(k<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 02 legs get down to 75
								   deg pos & 13 legs to 30 deg pos on ground*/
		   
		    
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));
              
		   
		   SETBIT(PORTC,BIT(4));_delay_ms(1.25);      //75 deg position
		   CLEARBIT(PORTC,BIT(4));                    
           SETBIT(PORTC,BIT(5));_delay_ms(1.00);      //30 deg position  
		   CLEARBIT(PORTC,BIT(5));
           SETBIT(PORTC,BIT(6));_delay_ms(1.25);
		   CLEARBIT(PORTC,BIT(6));
		   SETBIT(PORTC,BIT(7));_delay_ms(1.00);
		   CLEARBIT(PORTC,BIT(7));
            _delay_ms(12.50);
            
		   

		  
			 k++;
			 }
	
	         
            	
			
			
				  


		  
         int upperlimit_=3;                   
		                                              
		int r_=0;
		int k_=0;										  
		    
			  
		 while(r_<upperlimit_)         /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 13 legs stand in air 
								  in 75 deg pos & 02 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {  
		   
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(0.75);   //0 deg pos
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(1.50);    //90 deg pos
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(3));

         
		   SETBIT(PORTC,BIT(4));_delay_ms(1.00);      //30 deg position
		   CLEARBIT(PORTC,BIT(4));                    
           SETBIT(PORTC,BIT(5));_delay_ms(1.25);      //75 deg position  
		   CLEARBIT(PORTC,BIT(5));
           SETBIT(PORTC,BIT(6));_delay_ms(1.00);
		   CLEARBIT(PORTC,BIT(6));
		   SETBIT(PORTC,BIT(7));_delay_ms(1.25);
		   CLEARBIT(PORTC,BIT(7));
           _delay_ms(11.00);
            
		  
          
		   r_++;
		   }

          

		   while(k_<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 13 legs get down to 75
								   deg pos & 02 legs to 30 deg pos on ground*/
		   
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));

			  
		   SETBIT(PORTC,BIT(4));_delay_ms(1.00);      //30 deg position
		   CLEARBIT(PORTC,BIT(4));                    
           SETBIT(PORTC,BIT(5));_delay_ms(1.25);      //75 deg position  
		   CLEARBIT(PORTC,BIT(5));
           SETBIT(PORTC,BIT(6));_delay_ms(1.00);
		   CLEARBIT(PORTC,BIT(6));
		   SETBIT(PORTC,BIT(7));_delay_ms(1.25);
		   CLEARBIT(PORTC,BIT(7));
           _delay_ms(12.50);
             
		  
          
			 k_++;
			 }
			 
			 
	
	         return;
            }	
		
			
		  void move_back()
		 {
		
		 int k=0;
         int upperlimit=3;
		  
		 /*upperlimit=time for legs to take that position/20ms
		                                              
		
		 */   
	      int r=0;
		 while(r<upperlimit)    /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 02 legs stand in air 
								  in 75 deg pos & 13 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(3));

		   if(((CHECKBIT(PINA,BIT(2)))>0))     //right
           {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }

           else                                       //back
		   {
		   SETBIT(PORTD,BIT(0));_delay_ms(1.00);      //30 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.25);      //75 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(3));
            _delay_ms(11.00);
            }
		   
           
		   r++;

		   }

          

		   while(k<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 02 legs get down to 75
								   deg pos & 13 legs to 30 deg pos on ground*/
		   
		    
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));
              
		   if(((CHECKBIT(PINA,BIT(2)))>0))             //RIGHT 
		  {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }

           else
		   {
		   SETBIT(PORTD,BIT(0));_delay_ms(1.00);      //30 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.25);      //75 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(3));
            _delay_ms(12.50);
            }
		   

		  
			 k++;
			 }
	
	         
            	
			
			
				  


		  
         int upperlimit_=3;                   
		                                              
		int r_=0;
		int k_=0;										  
		    
			  
		 while(r_<upperlimit_)         /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 13 legs stand in air 
								  in 75 deg pos & 02 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {  
		   
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(0.75);   //0 deg pos
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(1.50);    //90 deg pos
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(3));

         if(((CHECKBIT(PINA,BIT(2)))>0))     //right
           {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }
            else                                           //back
			{
		   SETBIT(PORTD,BIT(0));_delay_ms(1.25);      //75 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.00);      //30 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(3));
           _delay_ms(11.00);
             } 
		  
          
		   r_++;
		   }

          

		   while(k_<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 13 legs get down to 75
								   deg pos & 02 legs to 30 deg pos on ground*/
		   
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));

			  if(((CHECKBIT(PINA,BIT(2)))>0))     //right
           {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }

		    else                                       //back
			{
		   SETBIT(PORTD,BIT(0));_delay_ms(1.00);      //75 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.25);      //30 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(3));
           _delay_ms(12.50);
             } 
		  
          
			 k_++;
			 }
	
	         return;
            }	
		
        void move_right()
		 {
		
		 int k=0;
         int upperlimit=3;
		  
		 /*upperlimit=time for legs to take that position/20ms
		                                              
		
		 */   
	      int r=0;
		 while(r<upperlimit)    /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 02 legs stand in air 
								  in 75 deg pos & 13 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(3));

		   if(((CHECKBIT(PINA,BIT(0)))>0))     //front
           {
		   move_front();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }

           else                                       //right
		   {
		   SETBIT(PORTD,BIT(0));_delay_ms(1.25);      //30 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.00);      //30 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(3));
            _delay_ms(11.00);
            }
		   
           
		   r++;

		   }

          

		   while(k<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 02 legs get down to 75
								   deg pos & 13 legs to 30 deg pos on ground*/
		   
		    
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));
              
		   if(((CHECKBIT(PINA,BIT(0)))>0))             //front 
		  {
		   move_front();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }

           else                                      //right
		   {
		   SETBIT(PORTD,BIT(0));_delay_ms(1.25);      //30 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.00);      //30 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(3));
            _delay_ms(12.50);
            }
		   

		  
			 k++;
			 }
	
	         
            	
			
			
				  


		  
         int upperlimit_=3;                   
		                                              
		int r_=0;
		int k_=0;										  
		    
			  
		 while(r_<upperlimit_)         /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 13 legs stand in air 
								  in 75 deg pos & 02 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {  
		   
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(0.75);   //0 deg pos
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(1.50);    //90 deg pos
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(3));

         if(((CHECKBIT(PINA,BIT(0)))>0))     //front
           {
		   move_front();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }
            else                                           //right
			{
		   SETBIT(PORTD,BIT(0));_delay_ms(1.00);      //75 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.25);      //75 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(3));
           _delay_ms(11.00);
             } 
		  
          
		   r_++;
		   }

          

		   while(k_<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 13 legs get down to 75
								   deg pos & 02 legs to 30 deg pos on ground*/
		   
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));

			  if(((CHECKBIT(PINA,BIT(0)))>0))     //front
           {
		   move_front();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(3)))>0))  //left

		   {
		   move_left();
		   }

		    else                                       //right
			{
		   SETBIT(PORTD,BIT(0));_delay_ms(1.00);      //75 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.25);      //75 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(3));
           _delay_ms(12.50);
             } 
		  
          
			 k_++;
			 }
	
	         return;
            }	



void move_left()
		 {
		
		 int k=0;
         int upperlimit=3;
		  
		 /*upperlimit=time for legs to take that position/20ms
		                                              
		
		 */   
	      int r=0;
		 while(r<upperlimit)    /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 02 legs stand in air 
								  in 75 deg pos & 13 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(3));

		   if(((CHECKBIT(PINA,BIT(2)))>0))     //right
           {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }

           else                                       //left
		   {
		   SETBIT(PORTD,BIT(0));_delay_ms(1.25);      //75 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.00);      //75 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(3));
            _delay_ms(11.00);
            }
		   
           
		   r++;

		   }

          

		   while(k<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 02 legs get down to 75
								   deg pos & 13 legs to 30 deg pos on ground*/
		   
		    
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));
              
		   if(((CHECKBIT(PINA,BIT(2)))>0))             //RIGHT 
		  {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }

           else
		   {
		   SETBIT(PORTD,BIT(0));_delay_ms(1.25);      //75 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.00);      //75 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(3));
            _delay_ms(12.50);
            }
		   

		  
			 k++;
			 }
	
	         
            	
			
			
				  


		  
         int upperlimit_=3;                   
		                                              
		int r_=0;
		int k_=0;										  
		    
			  
		 while(r_<upperlimit_)         /*TO BE DETERMINED EXPERIMENTALLY while 
		                          loop stops when 13 legs stand in air 
								  in 75 deg pos & 02 legs keep pushin 
								  ground from 75 deg till 30 deg pos*/
		   {  
		   
		   
		   SETBIT(PORTC,BIT(0));_delay_ms(0.75);   //0 deg pos
		   CLEARBIT(PORTC,BIT(0));
		   SETBIT(PORTC,BIT(1));_delay_ms(1.50);    //90 deg pos
		   CLEARBIT(PORTC,BIT(1));
		   SETBIT(PORTC,BIT(2));_delay_ms(0.75);
		   CLEARBIT(PORTC,BIT(2));
		   SETBIT(PORTC,BIT(3));_delay_ms(1.50);
		   CLEARBIT(PORTC,BIT(3));

         if(((CHECKBIT(PINA,BIT(2)))>0))     //right
           {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }
            else                                           //left
			{
		   SETBIT(PORTD,BIT(0));_delay_ms(1.00);      //30 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.25);      //30 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(3));
           _delay_ms(11.00);
             } 
		  
          
		   r_++;
		   }

          

		   while(k_<2)             /*TO BE DETERMINED EXPERIMENTALLY while
		                           loop stops when 13 legs get down to 75
								   deg pos & 02 legs to 30 deg pos on ground*/
		   
		     {
			 SETBIT(PORTC,BIT(0));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(0));
			 SETBIT(PORTC,BIT(1));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(1));
			 SETBIT(PORTC,BIT(2));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(2));
			 SETBIT(PORTC,BIT(3));_delay_ms(0.75);
			 CLEARBIT(PORTC,BIT(3));

			  if(((CHECKBIT(PINA,BIT(2)))>0))     //right
           {
		   move_right();
		   }
		  
		  else if(((CHECKBIT(PINA,BIT(1)))>0))  //back

		   {
		   move_back();
		   }
		  
		   else if(((CHECKBIT(PINA,BIT(0)))>0))  //front

		   {
		   move_front();
		   }

		    else                                       //left
			{
		   SETBIT(PORTD,BIT(0));_delay_ms(1.00);      //30 deg position
		   CLEARBIT(PORTD,BIT(0));                    
           SETBIT(PORTD,BIT(1));_delay_ms(1.25);      //30 deg position  
		   CLEARBIT(PORTD,BIT(1));
           SETBIT(PORTD,BIT(2));_delay_ms(1.00);
		   CLEARBIT(PORTD,BIT(2));
		   SETBIT(PORTD,BIT(3));_delay_ms(1.25);
		   CLEARBIT(PORTD,BIT(3));
           _delay_ms(12.50);
             } 
		  
          
			 k_++;
			 }
	
	         return;
            }	



