// Сервер

#include <SPI.h>
#include <RH_NRF24.h>

// Время, исключающее повторные нажатия
uint8_t delay_time = 100;

// создаем экземпляр класса для трансивера:
RH_NRF24 nrf24;

void setup() {
  // Настройка Serial соединения с компьютером
  Serial.begin(115200);

  // Настройка кнопок
  pinMode(A0, INPUT_PULLUP); // 1
  pinMode(A1, INPUT_PULLUP); // 2
  pinMode(A2, INPUT_PULLUP); // 3
  pinMode(A3, INPUT_PULLUP); // 4
  pinMode(A4, INPUT_PULLUP); // 5
  pinMode(A5, INPUT_PULLUP); // 6
  pinMode(2, INPUT_PULLUP);  // 7
  pinMode(3, INPUT_PULLUP);  // 8
  pinMode(5, INPUT_PULLUP);  // RESET

  // Настройка и инициализация nrf24l01
  if (!nrf24.init()) Serial.println("init failed");
  if (!nrf24.setChannel(1))  Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) Serial.println("setRF failed");
}

void loop() {

  // Проверяем нажатие кнопок

  // 1
  if (!(digitalRead(A0))) {
    nrf24.send("1", 1);
    Serial.println(1);
    delay(delay_time);
  }
  // 2
  if (!(digitalRead(A1))) {
    nrf24.send("2", 1);
    Serial.println(2);
    delay(delay_time);
  }
  // 3
  if (!(digitalRead(A2))) {
    nrf24.send("3", 1);
    Serial.println(3);
    delay(delay_time);
  }
  // 4
  if (!(digitalRead(A3))) {
    nrf24.send("4", 1);
    Serial.println(4);
    delay(delay_time);
  }
  // 5
  if (!(digitalRead(A4))) {
    nrf24.send("5", 1);
    Serial.println(5);
    delay(delay_time);
  }
  // 6
  if (!(digitalRead(A5))) {
    nrf24.send("6", 1);
    Serial.println(6);
    delay(delay_time);
  }
  // 7
  if (!(digitalRead(2))) {
    nrf24.send("7", 1);
    Serial.println(6);
    delay(delay_time);
  }
  // 8
  if (!(digitalRead(3))) {
    nrf24.send("8", 1);
    Serial.println(8);
    delay(delay_time);
  }
  // RESET
  if (!(digitalRead(5))) {
    nrf24.send("9", 1);
    Serial.println("Reset!");
    delay(delay_time);
  }
}
