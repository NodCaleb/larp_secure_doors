#include <Wire.h>

#define I2C_ADDRESS 9
#define USE_TIMER_1     true
#define TIMER_INTERVAL_MS    1000

#include "TimerInterrupt.h"

#define LED_PIN 2

byte settings = 0;
int doorCloseDelay = 0;
int doorTimer = 0;
uint8_t command = 0x00; //0x01 - open door, 0x02 - close door

int doorDelays[32] = {
  10,
  20,
  30,
  60,
  90,
  120,
  150,
  180,
  210,
  240,
  270,
  300,
  360,
  420,
  480,
  540,
  600,
  660,
  720,
  780,
  840,
  900,
  1200,
  1500,
  1800,
  2100,
  2400,
  2700,
  3000,
  3300,
  3600,
  7200
};

void timerHandler(void)
{
  if (doorTimer > 0) doorTimer--;
  else closeDoor();
}

void openDoor(){
  digitalWrite(LED_PIN, LOW);
  doorTimer = doorCloseDelay;
}

void closeDoor(){
  digitalWrite(LED_PIN, HIGH);
  doorTimer = 0;
}

void receiveCommand(int bytes) {
  command = Wire.read();
}

void setup()
{
  Serial.begin(9600);

  //Reading settings from slide switches
  for (int p = 10; p <= 17; p++){
    pinMode(p, INPUT_PULLUP);
  }

  for (int p = 17; p > 10; p--){
    settings = settings | !digitalRead(p);
    settings = settings << 1;
  }
  settings = settings | !digitalRead(10);
  
  doorCloseDelay = doorDelays[settings & 0x1F];

  Serial.println(doorCloseDelay);

  pinMode(LED_PIN, OUTPUT);

  closeDoor();

  ITimer1.init();
  ITimer1.attachInterruptInterval(TIMER_INTERVAL_MS, timerHandler);

  // Start the I2C Bus as Slave on address 13
  Wire.begin(I2C_ADDRESS); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveCommand);

}

void loop() {

  switch (command){
    case 0x01:
      openDoor();
      break;
    case 0x02:
      closeDoor();
      break;
  }

  command =  0x00;

  delay(100);
}
