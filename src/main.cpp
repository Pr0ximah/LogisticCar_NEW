/*
  This code is used for connecting arduino to serial ATK-IMU901 module, and test in arduino uno R3 board.
  connect map:
  arduino   ATK901 module
  VCC    5v/3.3v
  TX     RX<-0
  TX     TX->1
  GND    GND
*/
#include <Arduino.h>
// #include "Car.h"

// void setup() {
//     Car *car = Car::GetInstance();
// }

// void loop() {}

// Debug
// 24.03.17
#include "Chassis.h"
#include "ConstDef.h"
#include "IMU.h"
void setup() {
    // 初始化设置
    myIMU::GetInstance()->InitIMU();
    Serial.begin(9600);
}

void loop() {
    Serial.println(myIMU::GetInstance()->getAngle());
    // IMU_Heading();
    delay(500);
}
