/*
 * GccApplication5.c
 *
 * Created: 11-12-2014 15:16:23
 *  Author: SHUBH AGRAWAL
 */ 


#include <avr/io.h>

int main(void)
{   DDRA=0;
	DDRB=255;
	PORTB=0;
	int a;
	
	ADMUX|=(1<<REFS0);     //internally shorting AREF and AVCC//analog signal taken on pin0//
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);  //enabling ADC and setting division factor//
	
    while(1)
    {
		ADCSRA|=(1<<ADSC);
	    while((ADCSRA & (1<<ADSC)) !=0);  //start the conversion using adsc and take the adc value only when conversion gets completed i.e adsc gets 0.
	    
	    a=ADC;
		if (a<=409)
		PORTB=(1<<PBO);
		else if ((a>409)&&(a<613))
		PORTB=(1<<PB0)|(1<<PB1);
        //TODO:: Please write your application code 
    }
}