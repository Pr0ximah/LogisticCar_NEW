#include "IMU.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "ConstDef.h"
#include "PinDef.h"

// 软串口 (rx, tx)
SoftwareSerial SoftSerial(tx_IMU, rx_IMU);
static double heading_original = 401;  // heading初始值，缺省401

void IMU_Init() { SoftSerial.begin(9600); }

double IMU_Heading() {
    int16_t buffer[9];
    unsigned long long time_start = millis();
    while (true) {
        if (millis() - time_start > IMU_JUMP_TIME) {
            return 0;
        }
        if (SoftSerial.find(0x55)) {
            for (int i = 0; i < 9; i++) {
                while (!SoftSerial.available()) {
                    delayMicroseconds(1);
                }
                buffer[i] = SoftSerial.read();
            }
            if (buffer[0] == 0x55 && buffer[1] == 0x01 && buffer[2] == 0x06) {
                for (int i = 0; i < 9; i++) {
                    Serial.print(buffer[i], HEX);
                    Serial.print(" ");
                }
                Serial.print("\n");

                double heading = (float((int16_t)(buffer[8] << 8) | buffer[7])) / 32768.0 * 180;
                // if (heading_original == 401) {
                //     heading_original = heading;
                // }
                // heading -= heading_original;
                // // 归一化到 (-180 deg ~ 180 deg]
                // while (heading > 180) {
                //     heading -= 360;
                // }
                // while (heading <= -180) {
                //     heading += 360;
                // }
                return heading;
            }
        }
        delayMicroseconds(1);
    }
}