int en1=10;
int en2=11;
int in1=8;
int in2=9;
int in3=12;
int in4=13;
int a;int b;
void forward(
void setup(){
  pinMode (A0,INPUT);
  pinMode (A1,INPUT);
  pinMode (en1.OUTPUT);
  pinMode (en2,OUTPUT);
  pinMode (in1,OUTPUT);
  pinMode (in2,OUTPUT);
  pinMode (in3,OUTPUT);
  pinMode (in4,OUTPUT);
}
void loop(){
  int a=analogRead(A0);
  a=map(a,0,1023,0,255);
  int b=analogRead(A0);
  b=map(b,0,1023,0,255);
  if ((xlow<a)&&(xhigh>a)&&(ylow<b)&&(yhigh>b))
		{
		digitalWrite(in1,HIGH);
                digitalWrite(in2,HIGH);
                digitalWrite(in3,HIGH);
                digitalWrite(in4,HIGH);	
		}
		else if ((flow<a)&&(fhigh>a)&&(ylow<b)&&(yhigh>b))
		{
			digitalWrite(in1,HIGH);
                        digitalWrite(in2,);
                        digitalWrite(in1,HIGH);
                        digitalWrite(in1,HIGH);
	OCR1A=OCR1B=(255.0/(fhigh-flow))*(a[0]-60);
		}
		else if ((blow<a[0])&&(bhigh>a[0])&&(ylow<a[1])&&(yhigh>a[1]))
		{
			PORTC=B;
			OCR1A=OCR1B=(255.0/(bhigh-blow))*(40-a[0]);
		}
  
