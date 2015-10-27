int en1=10;
int en2=11;
int in1=8;
int in2=9;
int in3=12;
int in4=13;
int a;int b;
void setup(){
  pinMode (A0,INPUT);
  pinMode (A1,INPUT);
  pinMode (en1,OUTPUT);
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
  if ((81<a)&&(85>a)&&(81<b)&&(85>b))
		{
		digitalWrite(in1,HIGH);
                digitalWrite(in2,HIGH);
                digitalWrite(in3,HIGH);
                digitalWrite(in4,HIGH);	
		analogWrite(en1,255);
analogWrite(en2,255);
}
		else if ((65<a)&&(81>a)&&(81<b)&&(85>b))
		{
			digitalWrite(in1,HIGH);
                        digitalWrite(in2,LOW);
                        digitalWrite(in3,HIGH);
                        digitalWrite(in4,LOW);
	analogWrite(en1,(int)((255.0/(16))*(81-a)));
        analogWrite(en2,(int)((255.0/(16))*(81-a)));
		}
		else if ((85<a)&&(100>a)&&(81<b)&&(85>b))
		{
			digitalWrite(in1,LOW);
                        digitalWrite(in2,HIGH);
                        digitalWrite(in3,LOW);
                        digitalWrite(in4,HIGH);
                        analogWrite(en1,(int)((255.0/(15))*(a-85)));
                        analogWrite(en2,(int)((255.0/(15))*(a-85)));
		
		
		}
  else if ((81<a)&&(85>a)&&(85<b)&&(100>b)){
                        digitalWrite(in1,HIGH);
                        digitalWrite(in2,LOW);
                        digitalWrite(in3,HIGH);
                        digitalWrite(in4,HIGH);
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
  }             }
