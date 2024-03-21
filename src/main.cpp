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
    IMU_Init();

    Serial.begin(9600);

    // Chassis *c = Chassis::GetInstance();
    // c->SetMove(Vector2D(0, 1), 40);
    // int time_start = micros();
    // while (true) {
    //     if (micros() - time_start <= 1000000) {
    //         c->UpdateChassis();
    //     } else {
    //         c->Stop();
    //         delay(UPDATE_TIME_INTERVAL * 10);
    //         break;
    //     }
    //     // c->UpdateChassis();
    //     delay(UPDATE_TIME_INTERVAL);
    // }
}

void loop() {
    Serial.println(IMU_Heading());
    // IMU_Heading();
    delay(1);
}
