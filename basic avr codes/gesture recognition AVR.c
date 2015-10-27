/*
 * MotorPWMTimerADC.c
 *
 * Created: 11-Dec-14 8:07:21 PM
 *  Author: 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define F 1<<PC3|1<<PC4
#define B 1<<PC2|1<<PC5
#define BM1 1<<PC2|1<<PC3
#define BM2 1<<PC4|1<<PC5
//#define R 1<<PC2|BM2
//#define L 1<<PC4|BM1
//offsetmin=


int main(void)
{
	int i;
	int a[2];
	DDRA=0;
	PORTA=255;  //pull up resistor
	DDRC=255;
	DDRD=255;
	ADCSRA=1<<ADEN|0<<ADLAR|1<<ADPS0|1<<ADPS1|1<<ADPS2;
	TCCR1A=1<<WGM10|1<<WGM11|1<<COM1A1|1<<COM1B1;
	TCCR1B=1<<WGM12|1<<CS11|1<<CS10;
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
		if ((81<a[0])&&(85>a[0])&&(81<a[1])&&(85>a[1]))
		{
		PORTC=BM1|BM2;	
		}
		else if ((65<a[1])&&(81>a[1])&&(81<a[0])&&(85>a[0]))
		{
			PORTC=F;
	OCR1A=OCR1B=(255.0/(16))*(81-a[1]);
		}
		else if ((85<a[1])&&(100>a[1])&&(81<a[0])&&(85>a[0]))
		{
			PORTC=B;
			OCR1A=OCR1B=(255.0/(15))*(a[1]-85);
		}
		/*else if ((81<a)&&(85>a)&&(85<b)&&(100>b)){
			
			analogWrite(en1,(int)((255.0/(15))*(b-85)));
			analogWrite(en2,255);
		}
		else if ((81<a)&&(85>a)&&(65<b)&&(81>b)){
			digitalWrite(in1,HIGH);
			digitalWrite(in2,HIGH);
			digitalWrite(in3,HIGH);
			digitalWrite(in4,LOW);
			analogWrite(en2,(int)((255.0/(16))*(81-b)));
			analogWrite(en1,255);
		} */            
	}		
}