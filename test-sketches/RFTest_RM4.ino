#include <rm4.h>

// Arduino pin connected to the receiver VCC in. Set this high to enable the
// receiver.
static const int kEnablePin = 13;

// Arduino pins connected to the data pins on the receiver.
static const int kData0Pin = 2;
static const int kData1Pin = 10;
static const int kData2Pin = 11;
static const int kData3Pin = 12;
//const int relay1 =  14;             // the number of the relay1 pin
//const int relay2 =  15;             // the number of the relay1 pin
//const int relay3 =  16;             // the number of the relay1 pin
//const int relay4 =  17;             // the number of the relay1 pin

// Create an RM4 object to read the button codes from the remote.
RM4 remote(kData0Pin, kData1Pin, kData2Pin, kData3Pin);

void setup() {
  // Initialize the serial interface.
  Serial.begin(9600);

  // Turn on the receiver.
  pinMode(kEnablePin, OUTPUT);
  digitalWrite(kEnablePin, LOW);
//  pinMode(relay1, OUTPUT);
//  pinMode(relay2, OUTPUT);
//  pinMode(relay3, OUTPUT);
//  pinMode(relay4, OUTPUT);

}

void loop() {
  // Print the button code to the serial interface every 100 ms.
  const int button_code = remote.buttonCode();
//   if (button_code == 8) {                      // pin 2 is pressed and connected to GND so it will be LOW
//    digitalWrite(relay1, LOW);                    // remove 5v from pin 11 so relay in1 will be 0v and this make relay on
//    digitalWrite(kEnablePin, HIGH);
//    delay (2000);                                 // wait 1 second
//  } else {                                        
//    digitalWrite(relay1, HIGH);                   // add 5v to arduino pin 11 so relay in1 will be 5v and this make relay off
//     //digitalWrite(kEnablePin, HIGH);
//  }
//   if (button_code == 2) {                      // pin 2 is pressed and connected to GND so it will be LOW
//    digitalWrite(relay2, LOW);                    // remove 5v from pin 11 so relay in1 will be 0v and this make relay on
//     digitalWrite(kEnablePin, HIGH);
//    delay (2000);                                 // wait 1 second
//  } else {                                        
//    digitalWrite(relay2, HIGH);                   // add 5v to arduino pin 11 so relay in1 will be 5v and this make relay off
//  }
//   if (button_code == 1) {                      // pin 2 is pressed and connected to GND so it will be LOW
//    digitalWrite(relay3, LOW);                    // remove 5v from pin 11 so relay in1 will be 0v and this make relay on
//     digitalWrite(kEnablePin, HIGH);
//    delay (2000);                                 // wait 1 second
//  } else {                                        
//    digitalWrite(relay3, HIGH);                   // add 5v to arduino pin 11 so relay in1 will be 5v and this make relay off
//  }
//   if (button_code == 4) {                      // pin 2 is pressed and connected to GND so it will be LOW
//    digitalWrite(relay4, LOW);                    // remove 5v from pin 11 so relay in1 will be 0v and this make relay on
//     digitalWrite(kEnablePin, HIGH);
//    delay (2000);                                 // wait 1 second
//  } else {                                        
//    digitalWrite(relay4, HIGH);                   // add 5v to arduino pin 11 so relay in1 will be 5v and this make relay off
//  }

  //Serial.println(button_code);
//Serial.println(kData0Pin);
  
 // delay(100);
}
