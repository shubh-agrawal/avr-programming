#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>

#define BIT(b) (1<<(b))
#define CLEARBIT(x,b) x&=~b;
#define SETBIT(x,b) x|=b;
#define CHECKBIT(x,b) (x)&(b)


float motor[6]={90,90,90,90,90,90},pwm[6][2];




void angle()
{
int i,j,temp;

for(i=0;i<6;i++)
	{
	pwm[i][0]=0.75+(motor[i]/180.0)*0.50;
	pwm[i][1]=i;
	}


for(i=0;i<5;i++)
    {  
    for(j=0;j<5-i;j++)
       {
       if(pwm[j+1][0]<pwm[j][0])
           {
           temp=pwm[j][0];
           pwm[j][0]=pwm[j+1][0];
           pwm[j+1][0]=temp;
           }
       }
    }


PORTC=0xFF;

_delay_ms(pwm[0][0]);
CLEARBIT(PORTC,BIT(pwm[0][1]));
	
for(i=1;i<6;i++)
	{
	_delay_ms(pwm[i][0]-pwm[i-1][0]);
	CLEARBIT(PORTC,BIT(pwm[i][1]));
	}
_delay_ms(20-pwm[5][0]);
PORTC=0xFF;

}



int main()
{
DDRA=0x00;
DDRC=0xFF;
DDRD=0xFF;
DDRB=0x00;







}
