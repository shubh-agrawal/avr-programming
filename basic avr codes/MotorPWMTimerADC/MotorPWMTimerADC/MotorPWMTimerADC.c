/*
 * MotorPWMTimerADC.c
 *
 * Created: 11-Dec-14 8:07:21 PM
 *  Author: Shashwat Gupta
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int i;
	int a[2];
	DDRA=0;
	DDRC=255;
	PORTC=1<<PC2|1<<PC4;
	DDRD=255;
	ADCSRA=1<<ADEN|1<<ADPS0|1<<ADPS1|1<<ADPS2;
	TCCR1A=1<<WGM10|1<<WGM11|1<<COM1A1|1<<COM1B1;
	TCCR1B=1<<WGM12|1<<CS11|1<<CS10;//|1<<CS12;
	TCNT1=0;
	OCR1A=0;
	OCR1B=0;
	while(1)
	{
		ADMUX=1<<REFS0;
		for(i=0;i<2;ADMUX++,i++)
		{
			ADCSRA|=1<<ADSC;
			while(ADCSRA&(1<<ADSC));
			a[i]=ADC;
		}		
		OCR1A=a[0];
		OCR1B=a[1];
	}		
}