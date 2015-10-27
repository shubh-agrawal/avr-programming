/*
 * blinkLED.c
 *
 * Created: 09-12-2014 23:52:01
 *  Author: SHUBH AGRAWAL
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL    //to input frequency//
#include <util/delay.h>    //library for time analysis//

int main(void)
{
    while(1)
    {DDRB=~(0);      /*assigning output command to all pins*/
		PORTB=~(0);   /*assigning high output to all pins*/
		_delay_ms(1000);
		PORTB=0;            //off the LEDs //
		_delay_ms(1000) ; 
        //TODO:: Please write your application code 
    }
}