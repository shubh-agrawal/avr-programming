/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include "two7seg.c"

/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/
void Init_ADC(void);
int Read_ADC(void);

void main()
{
Init_ADC();
do
{
Ouptut_Display(Read_ADC());

}
while(1);
}


void Init_ADC(void)
{

    
	ADMUX|=(_BV(ADLAR) | _BV(REFS1)| _BV(REFS0)) ;
	// RFS1 and RFS0 are for Internal Reference voltage of 2.56V  AND 8 BIT CONVERSION
	ADMUX&=~(_BV(MUX0)|_BV(MUX1)|_BV(MUX2)|_BV(MUX3)|_BV(MUX4)); //SELECTING CHANNEL0
    ADCSRA|=(_BV(ADEN) | _BV(ADPS2) | _BV(ADPS0)) ; //normal conversion without interrupt 
	ADCSRA&=~(_BV(ADSC)|_BV(ADATE)|_BV(ADIF)|_BV(ADIE)|_BV(ADPS1));//clock/32 speed
      
}

int Read_ADC(void)
{
ADCSRA|=_BV(ADSC); //start conversion
while(!((ADCSRA&_BV(ADIF))>>ADIF));
return ADCH;
}
