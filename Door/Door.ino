#define LED_PIN 2

byte settings = 0;
int doorCloseDelay = 0;

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

  pinMode(LED_PIN, OUTPUT);      // set LED pin as output
  digitalWrite(LED_PIN, HIGH);    // switch off LED pin

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() >= 0) {
    char receivedData = Serial.read();   // read one byte from serial buffer and save to receivedData
    // Serial.println(receivedData);
    if (receivedData == '1') {
      digitalWrite(LED_PIN, LOW); // switch LED On
    }
    else if (receivedData == '0') {
      digitalWrite(LED_PIN, HIGH);  // switch LED Off
    }
  }
}
