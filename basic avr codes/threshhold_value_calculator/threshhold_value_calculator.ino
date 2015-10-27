
int i;
void setup(){
pinMode(A0,INPUT);
pinMode(A1,INPUT);
Serial.begin(9600);
}
void loop(){
  //while (Serial.available()==0);
  //for (i=0;i<200;i++){
    Serial.print(((analogRead(A0)/1023.0)*255));
    delay(100);
    Serial.print("     ");
     //for (i=0;i<200;i++){
   Serial.println(((analogRead(A1)/1023.0)*255));
    delay(100);
    
    
}
