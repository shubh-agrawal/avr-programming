/*
 * timer2.c
 *
 * Created: 10-12-2014 11:25:34
 *  Author: shubh
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)


{
	long int cnt=0;
	TCCR0|=(1<<CS00)|(1<<CS02); //for prescaling factor 1024
	DDRB=~0;
    while(1)
    {
		if (TCNT0==255)
		{
			cnt++;
			TCNT0=0;
		}
		if (cnt==61) //this is the total number of counts dat it takes for 1 second to compltete
		{
			PORTB=~0;
		}
		if (cnt==122) //this the next cnts for next 1 second to compltete
		{
			PORTB=0;
			cnt=0;
			
		}					
			
        //TODO:: Please write your application code 
    }
}