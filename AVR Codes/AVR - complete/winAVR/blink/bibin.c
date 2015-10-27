#include<avr/io.h>
void delay_ms(unsigned char time_ms);
main()
{
DDRC=0xff;
DDRA=0xff;
DDRB=0xff;
DDRD=0xff;

while(1)
{
	PORTC=0X00;
	PORTA=0X00;
	PORTB=0X00;
	PORTD=0X00;
	delay_ms(200);
	PORTA=0Xff;
	PORTB=0Xff;
	PORTC=0Xff;
	PORTD=0Xff;
	delay_ms(200);
	}
	return(0);
}

void delay_ms(unsigned char time_ms)
{
	unsigned short delay_count = F_CPU / 4000;

	unsigned short cnt;
	asm volatile ("\n"
                  "L_dl1%=:\n\t"
                  "mov %A0, %A2\n\t"
                  "mov %B0, %B2\n"
                  "L_dl2%=:\n\t"
                  "sbiw %A0, 1\n\t"
                  "brne L_dl2%=\n\t"
                  "dec %1\n\t" "brne L_dl1%=\n\t":"=&w" (cnt)
                  :"r"(time_ms), "r"((unsigned short) (delay_count))
	);
}