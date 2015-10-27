/*
 * GccApplication3.c
 *
 * Created: 10-12-2014 15:41:23
 *  Author: SHUBH AGRAWAL
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#define F (1<<0)|(1<<2)
#define B (1<<1)|(1<<3)
#define R (1<<0)|(1<<3)
#define L (1<<1)|(1<<2)

int main(void)
{
    while(1)
    { DDRC=~0;
		DDRD=~0;
		PORTD=~0;
		PORTC=F;
		_delay_ms(5000);
		PORTC=B;
		_delay_ms(5000);
		PORTC=L;
		_delay_ms(5000);
		PORTC=R;
		_delay_ms(5000);
		
		
		
        //TODO:: Please write your application code 
    }
}