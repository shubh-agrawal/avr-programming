#include <Wire.h>  //include the IC2 library wire
int temp_address=72;  //setting the address of slave
 void setup()
 {
   Serial.begin();
   Wire.begin();
 }
 void loop(){
   Wire.beginTransmission(temp_address); //this means that arduino is beginning to transmit data to temp_address slave
   Wire.send(0); //arduino wants to read data.
   Wire.endTransmission;  //arduino on its side has ended up transmission
   Wire.requestFrom(temp_address,1); //requesting the slave to send the 1 byte data that contains the info.
   while (Wire.available==0);  //wait for input to come
   int c=Wire.receive();  //reads the data acttually
