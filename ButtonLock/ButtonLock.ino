#define OPEN_PIN  2
#define CLOSE_PIN 3


void setup() {
  Serial.begin(9600);
  pinMode(OPEN_PIN, INPUT_PULLUP);
  pinMode(CLOSE_PIN, INPUT_PULLUP);

}

void loop() {
  
  if (!digitalRead(OPEN_PIN)){
    Serial.println(0x01);
    delay(1000);
  }

  if (!digitalRead(CLOSE_PIN)){
    Serial.println(0x00);
    delay(1000);
  } 

}
