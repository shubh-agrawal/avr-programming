/*
 * GccApplication1.c
 *
 * Created: 09-12-2014 23:44:18
 *  Author: sidj
 */ 


#include <avr/io.h>
#define F_CPU 160000000UL
#include <util/delay.h>


int main(void)
{
	DDRA=0;
	DDRB=255;
	PORTB=(1<<PB3);
	int a;
	
	ADMUX|=(1<<REFS0);     //internally shorting AREF and AVCC//analog signal taken on pin0//
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);  //enabling ADC and setting division factor//
	TCCR0|=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS00);     //setting on fast PWM mode and no prescaling//
	
    while(1)
    {
		ADCSRA|=(1<<ADSC);                         //you have to start conversion after entering into while loop and must wait for adsc to get 0 as it defines whether the conversion is completed .
		while((ADCSRA & (1<<ADSC)) !=0);
		 
		a=ADC;
		
		if (a<=409)                  //for analog voltage less than 2volts// 
		{
		//TCNT0=0;
		OCR0=64;
		}
		else if((a>410)&&(a<=613)){        //analog voltage between 2 to 3 volts//
		//TCNT0=0;
		OCR0=128;			
		}			
		else if((a>613)&&(a<=818))    //analog voltage between 3 to 4 volts// 
		{
		//TCNT0=0;
		OCR0=192;
		}
		
		else if(a>818) //else between 4-5 volts//
		{
		//TCNT0=0;
		OCR0=254;
		}				
		
    }
} 