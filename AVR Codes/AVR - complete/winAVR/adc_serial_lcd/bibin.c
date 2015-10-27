/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/
#include "lcd.c"
#include "serial.c"
#include "adc.c"

/*----------------------------------------------------------------
-----------------MAIN FUNCTION------------------------------------
-----------------------------------------------------------------*/
  
void main()
{
unsigned int i,j,a,b,k;
unsigned char str[14]={'T','E','M','P','E','R','A','T','U','R','E',':',' ',' '};//at starting some backspace occurs
unsigned char del[2]={0x08,0X08}; //for deleting previous reading
//serial port initiliasation
InitUART( 25 ); //1Mhz 2400 8n1
//TransmitByte();

//Lcd startups
Init_Ports();
Init_Lcd();

//ADC startups
Init_ADC();
//Read_ADC(void)




//strating the main 


//sending the string
for(i=0;i<14;i++)
{
Lcd_Send(str[i]);
TransmitByte(str[i]);
}
b=0;

do
{
a=Read_ADC();
if(a!=b)
{
//first delete the previous values for uart
	for(i=0;i<2;i++)
	{
	TransmitByte(del[i]);
	}
	
//for LCD we require initialiatization
	Init_Lcd();
	for(i=0;i<12;i++)
	Lcd_Send(str[i]);
	

	
	
j=a%10;

k=a/10;
k=k%10;
Lcd_Send((k+0x30));
TransmitByte((k+0x30));

Lcd_Send((j+0x30)); //since both will display ASCII values, we convert decimal to ASCII
TransmitByte((j+0x30));

b=a; //for next value 
//delay sometime (1s) otherwise LCD display will run
	delay(1000);
}

}
while(1);


}
