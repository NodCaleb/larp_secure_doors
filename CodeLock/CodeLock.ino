#include "Keypad.h"
#include <Wire.h>

#define I2C_ADDRESS 9
#define SETTING_FIRST_PIN 9
#define SETTING_LAST_PIN 16

const byte buzzerPin = 17;
const byte ROWS = 4; // number of rows
const byte COLS = 3; // number of columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };

char code[4] = {'0', '0', '0', '0'};
byte codeStep = 0;
byte settings = 0;
byte correctCodeIndex = 0;
bool brokenLock = false;

byte rowPins[ROWS] = {2, 7, 6, 4}; // row pinouts of the keypad
byte colPins[COLS] = {3, 8, 5};    // column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char codes[127][4] = {
  {'7', '3', '0', '2'},
  {'8', '9', '1', '2'},
  {'4', '5', '6', '0'},
  {'3', '5', '4', '3'},
  {'8', '2', '0', '7'},
  {'2', '2', '5', '8'},
  {'8', '6', '9', '4'},
  {'2', '3', '4', '0'},
  {'0', '6', '3', '7'},
  {'3', '9', '1', '4'},
  {'2', '1', '0', '7'},
  {'3', '9', '4', '3'},
  {'8', '8', '9', '4'},
  {'1', '0', '4', '1'},
  {'9', '7', '9', '4'},
  {'8', '6', '0', '6'},
  {'8', '9', '1', '6'},
  {'5', '2', '6', '1'},
  {'3', '6', '5', '8'},
  {'3', '1', '0', '1'},
  {'6', '5', '6', '1'},
  {'6', '9', '7', '3'},
  {'1', '5', '8', '0'},
  {'9', '4', '5', '4'},
  {'8', '1', '2', '4'},
  {'1', '4', '0', '0'},
  {'8', '3', '0', '2'},
  {'4', '5', '0', '0'},
  {'6', '0', '5', '7'},
  {'3', '1', '3', '4'},
  {'1', '1', '2', '1'},
  {'9', '6', '7', '5'},
  {'3', '8', '6', '6'},
  {'3', '0', '9', '0'},
  {'0', '7', '4', '8'},
  {'1', '8', '9', '6'},
  {'3', '6', '1', '2'},
  {'5', '5', '6', '4'},
  {'0', '2', '0', '5'},
  {'1', '8', '4', '4'},
  {'0', '1', '4', '5'},
  {'7', '5', '8', '5'},
  {'3', '3', '7', '0'},
  {'2', '7', '3', '5'},
  {'5', '8', '3', '9'},
  {'5', '2', '4', '2'},
  {'6', '7', '0', '4'},
  {'8', '8', '3', '3'},
  {'9', '6', '7', '1'},
  {'9', '4', '8', '6'},
  {'9', '2', '9', '9'},
  {'2', '3', '9', '6'},
  {'9', '7', '6', '1'},
  {'7', '7', '3', '0'},
  {'8', '5', '5', '7'},
  {'4', '1', '3', '3'},
  {'6', '7', '1', '7'},
  {'0', '1', '5', '3'},
  {'8', '0', '7', '6'},
  {'4', '0', '9', '2'},
  {'7', '0', '0', '8'},
  {'2', '4', '4', '9'},
  {'4', '5', '8', '3'},
  {'1', '7', '5', '0'},
  {'3', '0', '1', '3'},
  {'2', '2', '3', '0'},
  {'2', '9', '4', '2'},
  {'9', '1', '3', '7'},
  {'3', '9', '1', '7'},
  {'2', '2', '0', '2'},
  {'9', '6', '1', '4'},
  {'1', '5', '9', '7'},
  {'8', '7', '1', '3'},
  {'0', '5', '1', '4'},
  {'1', '3', '8', '2'},
  {'9', '7', '6', '0'},
  {'5', '6', '8', '4'},
  {'4', '3', '1', '5'},
  {'8', '7', '9', '4'},
  {'5', '6', '8', '2'},
  {'2', '4', '5', '3'},
  {'2', '6', '1', '2'},
  {'5', '9', '6', '6'},
  {'5', '7', '9', '8'},
  {'4', '9', '6', '7'},
  {'1', '8', '0', '0'},
  {'7', '6', '6', '2'},
  {'0', '2', '4', '0'},
  {'8', '9', '1', '6'},
  {'5', '2', '6', '0'},
  {'1', '2', '8', '3'},
  {'3', '5', '2', '0'},
  {'3', '1', '2', '9'},
  {'6', '4', '1', '5'},
  {'0', '5', '1', '1'},
  {'8', '7', '4', '3'},
  {'6', '2', '6', '3'},
  {'8', '9', '7', '2'},
  {'4', '7', '3', '0'},
  {'7', '0', '6', '9'},
  {'7', '8', '4', '0'},
  {'1', '2', '4', '1'},
  {'7', '9', '7', '5'},
  {'3', '5', '8', '3'},
  {'7', '1', '2', '7'},
  {'6', '2', '2', '1'},
  {'0', '8', '3', '9'},
  {'2', '6', '7', '9'},
  {'8', '6', '5', '6'},
  {'1', '9', '0', '4'},
  {'3', '6', '3', '5'},
  {'3', '1', '5', '9'},
  {'3', '8', '0', '2'},
  {'8', '4', '6', '5'},
  {'6', '4', '7', '7'},
  {'1', '4', '2', '9'},
  {'6', '0', '6', '0'},
  {'1', '6', '2', '6'},
  {'7', '9', '9', '9'},
  {'1', '6', '3', '7'},
  {'2', '8', '4', '4'},
  {'2', '3', '4', '1'},
  {'9', '6', '5', '6'},
  {'6', '8', '5', '8'},
  {'2', '3', '6', '7'},
  {'5', '4', '0', '4'},
  {'1', '3', '5', '2'}
};
 
void setup()
{
  Serial.begin(9600);

  //Reading settings from slide switches
  for (int p = SETTING_FIRST_PIN; p <= SETTING_LAST_PIN; p++){
    pinMode(p, INPUT_PULLUP);
  }

  for (int p = SETTING_LAST_PIN; p > SETTING_FIRST_PIN; p--){
    settings = settings | !digitalRead(p);
    settings = settings << 1;
  }
  settings = settings | !digitalRead(SETTING_FIRST_PIN);

  pinMode(buzzerPin, OUTPUT);

  // Serial.print("Settings: ");
  // Serial.println(settings);

  correctCodeIndex = settings & 0x7F; //Most significant bit reserved for "broken" lock
  brokenLock = settings & (1 << 7);

  Wire.begin();
}
 
void loop()
{
  char key = keypad.getKey(); 
  if (key != NO_KEY){

    if (!brokenLock){
      code[codeStep] = key;
      codeStep++;
      keypressBeep();
    }
    else{
      errorBeep();
    }    

    if (key == '#'){
      codeStep = 0;
    }

    if (codeStep == 4){
      codeStep = 0;
      if (checkCode()){
        transmitOpenCommand();
        successBeep();
      }
      else{
        errorBeep();
      }
    }
  }
}

void transmitOpenCommand(){
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(0x01);
    Wire.endTransmission();
}

void printCode(){
  for(int i = 0; i < 4; i++){
    Serial.print(code[i]);
  }
  Serial.println();
}

bool checkCode(){
  for (int i = 0; i < 4; i++){
    if (code[i] != codes[correctCodeIndex][i])
    return false;
  }
  return true;
}

void keypressBeep(){
  tone(buzzerPin, 1600, 100);
}

void successBeep(){
  tone(buzzerPin, 1046, 600);
}

void errorBeep(){
  tone(buzzerPin, 262, 600);
}
