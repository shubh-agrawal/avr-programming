#include <math.h>
#include <Wire.h>
#define PI 3.143
const int G_SENS=131;          //a division factor that directly gives omega calculated
const int MPU=0x68;                  //address of the IMU sensor
const float dt=0.0001;              //derivative time interval
float y_old_theta=0,y_theta=0;       float y_sum_theta=0;float y_diff;
int en1=10;
int en2=11;
int in1=8;
int in2=9;
int in3=12;
int in4=13,vel;
const float Kp=40,Ki=10,Kd=1;

int PID()                     //PID control loop
{
  vel=Kp*(y_theta)+Ki*(y_sum_theta*dt)+Kd*(y_diff/dt);
  return vel;
}
void speed(int vel)                 //vel=pwm calculated with PID and offset
{
  if (vel<0){
    digitalWrite(in2,HIGH);
    digitalWrite(in1,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in3,LOW);
    
    
  }
  else if (vel>0)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }
  analogWrite(en1,abs(vel));
   analogWrite(en2,abs(vel));
}
void setup()
{
  pinMode (en1,OUTPUT);
  pinMode (en2,OUTPUT);
  pinMode (in1,OUTPUT);
  pinMode (in2,OUTPUT);
  pinMode (in3,OUTPUT);
  pinMode (in4,OUTPUT);
  //pinMode (11,OUTPUT);
  //digitalWrite(11,HIGH);
  Serial.begin(38400);            //data send by IMU is too fast
  Wire.begin();   //start with I2C transmission
  Wire.beginTransmission(MPU);  //transmission with this address
  Wire.write(0x6B);  //first specifies power management address of MCU to be given command 
  Wire.write(0);   //awakes MCU by sending 0 to above register address
 Wire.endTransmission(true);
 }
void loop(){
  Wire.beginTransmission(MPU); //starting the communication again
  Wire.write(0x3B);  //start with this register address (its the first data register
  Wire.endTransmission(false);  //continue to read data
  Wire.requestFrom(MPU,14,true);  //request the slave to send the 14 byte data
  int acc_x=Wire.read()<<8|Wire.read();  //acc_x is 16 bit data .the data is automatically read sequently from 0x3B
  int acc_y=Wire.read()<<8|Wire.read();  //all the data is sequently stored in registers in IMU....hence we can read it sequently only by specifying the starting address .
  int acc_z=Wire.read()<<8|Wire.read();
  int tmp=Wire.read()<<8|Wire.read();  //each quantity has 16 bit data..however the wire.read reads only 8 bit at a time.first H register and then L register
  int gyr_x=Wire.read()<<8|Wire.read();
  int gyr_y=Wire.read()<<8|Wire.read();
  int gyr_z=Wire.read()<<8|Wire.read();
  Wire.endTransmission();  //end the transmission
  float ACCY=atan2((double)acc_x,(double)acc_z)*180/PI;      //ACCY is the theta about y axis calculated from accelerometer data
  int GYRY=(float)gyr_y/G_SENS;          //GYRY is the omega about y axis          
  //G_SENS is factor that directly gives the omega from raw data of gyroscope in IMU          
  
  y_theta=0.85*(y_old_theta+GYRY*dt)+0.15*(ACCY);//complimentary filter 
   y_diff=y_theta-y_old_theta; 
y_sum_theta+=y_theta;                                                              
  y_old_theta=y_theta;
vel=PID();
speed(vel);
                                                  //update of theta
 
  
  /*if ((y_theta>-2)&&(y_theta<2))  //condition for rest position
  {
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
     digitalWrite(en1,HIGH);
    digitalWrite(en2,HIGH);
     
}
 else if ((y_theta>2)&&(y_theta<15))   //condition
 {
   vel=map(constrain(y_theta,2,15),2,15,150,255);      //setting off set as 100
  speed(vel);                                          //constrain is a function==if value exceeds max. it will set the value constant on max. and same occurs for min
 }
 else if ((y_theta>-15)&&(y_theta<-2))
 {
   vel=map(constrain(y_theta,-15,-2),-2,-15,-150,-255);
  speed(vel);
 }*/
 

 Serial.print("theta_y: "); Serial.print(y_theta);                //for calculating the threshold values
 Serial.print(" | omega_y: "); Serial.println(GYRY);
 
 delay(50);
}
  
  
  
  
  
