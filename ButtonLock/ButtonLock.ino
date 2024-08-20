#include <Wire.h>

#define OPEN_PIN  2
#define CLOSE_PIN 3


void setup() {
  Serial.begin(9600);
  pinMode(OPEN_PIN, INPUT_PULLUP);
  pinMode(CLOSE_PIN, INPUT_PULLUP);
  Wire.begin();
}

void loop() {
  
  if (!digitalRead(OPEN_PIN)){
    transmitI2C('1');
    delay(500);
  }

  if (!digitalRead(CLOSE_PIN)){
    transmitI2C('0');
    delay(500);
  } 

}

void transmitI2C(char data){
  Serial.println(data);
  Wire.beginTransmission(13); // transmit to device #13
  Wire.write(data);             // sends data
  Wire.endTransmission();       // stop transmitting
}
