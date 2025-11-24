#include <ESP32Servo.h>
#include <SPI.h>
#include "RF24.h"

#define CE_PIN 4
#define CSN_PIN 16

RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[][6] = { "1Node", "2Node" };

bool radioNumber;

#define SIZE 1   
char buffer[SIZE + 1];    

static const int servoPin = 27;
Servo servo1;
bool switchstate = false;
#define SIZE 1

void setup() {

  Serial.begin(115200);
  servo1.attach(servoPin);


  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  
  }
 
  Serial.println(F("RF24/examples/StreamingData"));
  Serial.println(F("Radio 1"));
  radioNumber = 1;
  Serial.print(F("radioNumber = "));
  Serial.println((int)radioNumber);

  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(1, address[!radioNumber]);
  radio.startListening();
  servo1.write(60);
}

void loop() {
  char c = toupper(Serial.read());
  if (c == 'T') {
      servo1.write(90);
  } else if (c == 'F') {
        servo1.write(30);
  }

  if (radio.available()) {
    radio.read(&buffer, SIZE);
    Serial.print(F("Received: "));
    Serial.println(buffer[0]);
    //Serial.println(buffer[1]);

//     if (buffer[0] == '1') {


//       if (!switchstate) {
//        servo1.write(90);
//        switchstate = true;
//     } else {
//        servo1.write(30);
//        switchstate = false;
//     }

//    }
  
  }
  
  Serial.println("hi");
  if (radio.available()) {      // is there a payload?
      radio.read(&buffer, SIZE);  // fetch payload from FIFO
      Serial.print(F("Received: "));
      
      Serial.println(buffer[0]);  // print the payload's value
      Serial.println(buffer[1]);

}