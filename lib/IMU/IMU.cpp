#include "IMU.h"

#include <SoftwareSerial.h>
#include "PinDef.h"

// 软串口 (rx, tx)
SoftwareSerial SoftSerial(tx_IMU, rx_IMU);

void IMU_Init() { SoftSerial.begin(9600); }

double IMU_Heading() {
    int16_t Buffer[9];
    bool valid_flag = False;
    while (!valid_flag) {
        if (SoftSerial.find(0x55)) {
            for (int i = 0; i < 9; i++) {
                while (!SoftSerial.available()) {
                    delayMicroseconds(1);
                }
                Buffer[i] = SoftSerial.read();
            }
            if (Buffer[0] == 0x55 && Buffer[1] == 0x01 && Buffer[2] == 0x06) {
                double heading = (double((int16_t)(Buffer[8] << 8) | Buffer[7])) / 32768.0 * 180;
                if (heading_original == 401) {
                    heading_original = heading;
                }
                heading -= heading_original;
                // 归一化到 (-180 deg ~ 180 deg]
                while (heading > 180) {
                    heading -= 360;
                }
                while (heading <= -180) {
                    heading += 360;
                }
                return heading;
            }
        }
        delayMicroseconds(1);
    }
}

void print_0x_num(int16_t *arr, int len) {
    for (int i = 0; i < len; i++) {
        Serial.print(arr[i], HEX);
        Serial.print(" ");
    }
    Serial.print("\n");
}