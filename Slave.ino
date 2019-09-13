// Клиент

#include <SPI.h>
#include <Wire.h>
#include <RH_NRF24.h>
#include "PCF8574.h"

// Создаем экземпляр класса для трансивера:
RH_NRF24 nrf24;

// Создаем экземпляр класса для экспандеров
PCF8574 PCF_38(0x38);
PCF8574 PCF_39(0x39);
PCF8574 PCF_3A(0x3A);
PCF8574 PCF_3B(0x3B);
PCF8574 PCF_3C(0x3C);
PCF8574 PCF_3D(0x3D);
PCF8574 PCF_3E(0x3E);
PCF8574 PCF_3F(0x3F);

uint32_t player_number = 0;
uint32_t schedule[9] = {0};
uint32_t was_pressed[8] = {0};

void setup() {
  // Настройка Serial соединения с компьютером
  Serial.begin(115200);
  // Настройка микросхем экспандеров по адресам
  
    for (uint8_t i = 0; i < 8; i++) {
    PCF_38.pinMode(i, OUTPUT);
    PCF_39.pinMode(i, OUTPUT);
    PCF_3A.pinMode(i, OUTPUT);
    PCF_3B.pinMode(i, OUTPUT);
    PCF_3C.pinMode(i, OUTPUT);
    PCF_3D.pinMode(i, OUTPUT);
    PCF_3E.pinMode(i, OUTPUT);
    PCF_3F.pinMode(i, OUTPUT);
    }

  pinMode(A0, INPUT_PULLUP); // Кнопка сброса на приемнике

  // Настройка и инициализация nrf24l01
  if (!nrf24.init()) Serial.println("init failed");
  if (!nrf24.setChannel(1))  Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) Serial.println("setRF failed");
}


void loop() {
  uint8_t buf[1] = {0};
  uint8_t len = sizeof(buf);

  // Принимаем посылку с Мастер-платы
  if (nrf24.available()) {
    if (nrf24.recv(buf, &len)) {
      Serial.print("Player number is :");
      Serial.println(player_number);
    }
  }

  // Проверяем очередность и количество нажатий
  if (buf[0] == '1' && was_pressed[0] == 0) {
    PCF_38.digitalWrite(player_number, 1);
    was_pressed[0] = 1;
    Serial.println("One!");
    player_number++;
  }
  if (buf[0] == '2' && was_pressed[1] == 0) {
    PCF_39.digitalWrite(player_number, 1);
    was_pressed[1] = 1;
    Serial.println("Two!");
    player_number++;
  }
  if (buf[0] == '3' && was_pressed[2] == 0) {
    PCF_3A.digitalWrite(player_number, 1);
    was_pressed[2] = 1;
    Serial.println("Three!");
    player_number++;
  }
  if (buf[0] == '4' && was_pressed[3] == 0) {
    PCF_3B.digitalWrite(player_number, 1);
    was_pressed[3] = 1;
    Serial.println("Four!");
    player_number++;
  }
  if (buf[0] == '5' && was_pressed[4] == 0) {
    PCF_3C.digitalWrite(player_number, 1);
    was_pressed[4] = 1;
    Serial.println("Five!");
    player_number++;
  }
  if (buf[0] == '6' && was_pressed[5] == 0) {
    PCF_3D.digitalWrite(player_number, 1);
    was_pressed[5] = 1;
    Serial.println("Six!");
    player_number++;
  }
  if (buf[0] == '7' && was_pressed[6] == 0) {
    PCF_3E.digitalWrite(player_number, 1);
    was_pressed[6] = 1;
    Serial.println("Seven!");
    player_number++;
  }
  if (buf[0] == '8' && was_pressed[7] == 0) {
    PCF_3F.digitalWrite(player_number, 1);
    was_pressed[7] = 1;
    Serial.println("Eight!");
    player_number++;
  }

  // Была нажата кнопка сброса, сбрасываем очередь
  if (buf[0] == '9') {
    Serial.println("Reset");
    for (uint8_t i = 0; i < 8; i++) schedule[i] = 0;
    for (uint8_t i = 0; i < 8; i++) was_pressed[i] = 0;
    player_number = 0;
  }

  // Сброс кнопкой на приемнике
  if (!(digitalRead(A0))) {
    Serial.println("Reset");
    for (uint8_t i = 0; i < 8; i++) schedule[i] = 0;
    for (uint8_t i = 0; i < 8; i++) was_pressed[i] = 0;
    player_number = 0;
    delay(200);
  }
}
