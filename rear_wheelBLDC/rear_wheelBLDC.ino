#define SPEED 78
#define speed_pin 12

int status_flag=0;
String received_data="";
/****************************************************************/
void command(String r_data)
{
  if ( r_data == "*start#")
  {
    analogWrite( speed_pin , SPEED );
    Serial.println("start running");
    status_flag=1;
  }
  else if ( r_data == "*stop#" )
  {
    analogWrite( speed_pin , 0 );
    Serial.println("stop running");
    status_flag=0;
  }
  else
  {
    Serial.println("not a recognized command");
    
  }
}
/********************************************************************/
void setup() 
{
  
  Serial.begin(9600);
  Serial1.begin(9600); 
  pinMode( speed_pin ,OUTPUT);
} 

void loop() 
{
  
  while(Serial1.available()>0)
  {
    delayMicroseconds(2000);
    while(!Serial1.available());
    char data=Serial1.read();
    received_data+=data;
  } 
    if (received_data.length()>0)
    {
      Serial.println(received_data);
      command(received_data);
      received_data="";
    }
    
  
    
  
}


