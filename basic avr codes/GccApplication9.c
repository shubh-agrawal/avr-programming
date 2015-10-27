/*
 * GccApplication9.c
 *
 * Created: 12-12-2014 21:28:02
 *  Author: SHUBH AGRAWAL
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
volatile int cnt=0;
int main(void)
{
	float dc;
	DDRD=0; 
	DDRC=255;
	PORTC=0;      //input is taken as interrupt
	DDRB=255;
	PORTD|=(1<<PD3);  //a pull up resistor must be added to detect a rising edge//if not added
	GICR|=(1<<INT1);
	MCUCR|=(0<<ISC11)|(1<<ISC10);
	TCCR0|=(1<<WGMO1)|(1<<WGM11)|(1<<COM01)|(0<<COM00)|(1<<COM02)|(1<<COM00)|1<<CS02|1<<CS00;
	sei();
    while(1)
    {
OCR0=50;
		
        //TODO:: Please write your application code 
    }
}
ISR(INT1_vect){
	cnt++;
	if (cnt==122){
		PORTC=~PORTC;
		cnt=0;
	}
}