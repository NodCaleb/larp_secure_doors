#define RST_PIN         9        // Пин rfid модуля RST
#define SS_PIN          10       // Пин rfid модуля SS
#define USE_TIMER_1     true
#define TIMER_INTERVAL_MS    1000

#include <SPI.h>
#include <MFRC522.h>
#include "TimerInterrupt.h"

MFRC522 rfid(SS_PIN, RST_PIN);   // Объект rfid модуля
MFRC522::MIFARE_Key key;         // Объект ключа
MFRC522::StatusCode status;      // Объект статуса

int rfidCooldown = 0;

void timerHandler(void)
{
  if (rfidCooldown > 0) rfidCooldown--;

    // digitalWrite(RST_PIN, HIGH);          // Сбрасываем модуль
    // delayMicroseconds(2);                 // Ждем 2 мкс
    // digitalWrite(RST_PIN, LOW);           // Отпускаем сброс
    // rfid.PCD_Init();                      // Инициализируем заного
}

void setup() {
  Serial.begin(9600);            // Инициализация Serial
  SPI.begin();                   // Инициализация SPI
  rfid.PCD_Init();               // Инициализация модуля
  for (byte i = 0; i < 6; i++) { // Наполняем ключ
    key.keyByte[i] = 0xFF;       // Ключ по умолчанию 0xFFFFFFFFFFFF
  }

  ITimer1.init();
  ITimer1.attachInterruptInterval(TIMER_INTERVAL_MS, timerHandler);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent()) return;  // Если новая метка не поднесена - вернуться в начало loop
  if (!rfid.PICC_ReadCardSerial()) return;    // Если метка не читается - вернуться в начало loop
  if (rfidCooldown > 0) return;               // Cooldown для RFID
  // Работаем с RFID
  rfidCooldown = 3;
  Serial.println(0x01);
  // Serial.print("UID: ");
  // for (uint8_t i = 0; i < 4; i++) {           // Цикл на 4 итерации
  //   Serial.print("0x");                       // В формате HEX
  //   Serial.print(rfid.uid.uidByte[i], HEX);   // Выводим UID по байтам
  //   Serial.print(", ");
  // }
  // Serial.println("");
}
