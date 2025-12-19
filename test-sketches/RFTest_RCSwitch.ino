#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
const int LED_Pin=13;
const int D0_Pin=8;
const int D1_Pin=9;
const int D2_Pin=10;
const int D3_Pin=11;
const int Vt_Pin=12;
int  Read=0;
bool statusLED=LOW;
void setup() {
  pinMode(LED_Pin, OUTPUT);

  pinMode(D0_Pin, INPUT);
  pinMode(D1_Pin, INPUT);
  pinMode(D2_Pin, INPUT);
  pinMode(D3_Pin, INPUT);
  pinMode(Vt_Pin, INPUT);
   digitalWrite(LED_Pin, LOW);
  
  
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
       Serial.print("\t");
    Serial.print(mySwitch.getReceivedValue());
   Serial.print("\t");

    unsigned long int num=mySwitch.getReceivedValue();
    //Serial.print(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    
    Serial.print(num);
    switch(num){
   case 16777215:
    mySwitch.disableReceive();
  digitalWrite(LED_Pin,HIGH);
  delay(2000);
  digitalWrite(LED_Pin,LOW);
  delay(2000);
  digitalWrite(LED_Pin,HIGH);
  delay(2000);
   digitalWrite(LED_Pin,LOW);
  delay(2000);
  digitalWrite(LED_Pin,HIGH);
  delay(2000);
  digitalWrite(LED_Pin,LOW);
  delay(2000);
 break;
//      
//      case 5592512:
//      mySwitch.disableReceive();
//      statusLED=HIGH;
//      break;
//      
 }

if(digitalRead(D0_Pin)==HIGH){
   Read=1;
 // LEDBlink(200,1);
}

else if(digitalRead(D1_Pin)==HIGH){
 Read=2;
 // LEDBlink(200,2);
}
else if(digitalRead(D2_Pin)==HIGH){
 Read=3;
//  LEDBlink(200,3);
}
else if(digitalRead(D3_Pin)==HIGH){
Read=4;
 // LEDBlink(200,4);
}
else if(digitalRead(Vt_Pin)==HIGH){
Read=5;
 // LEDBlink(200,5);
}

//    digitalWrite(LED_Pin,statusLED);
//    unsigned long int time_now=millis();
//    int ck=500;
//    while(millis()<time_now+ck)
//    {}
LEDBlink(Read);
    mySwitch.resetAvailable();
    mySwitch.enableReceive(0);
  }
}


//**LED Blink
void LEDBlink(int a){
  
 // if((D0read==1)||(D1read==1)||(D2read==1)||(D3read==1)||(Vtread==1)){

    for(int i=0;i<=a;i++){
    digitalWrite(LED_Pin,HIGH);
    delay(500);
    digitalWrite(LED_Pin,LOW);
    delay(200);
  }
 Read=0;  
  }
