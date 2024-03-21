#include "IMU.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "ConstDef.h"
#include "PinDef.h"
// 软串口 (rx, tx)
void MyIMU::InitIMU(){
    double angleSpeed_sum = 0;       //初始化静态偏移量和变量
    int16_t angleSpeedOri;  // 角加速度原始数值
    int16_t temp1, temp2, temp3, temp4, temp5;  // 不使用这些变量，仅用于imu函数传参
    Serial.println("IMU initializing starts...");
    delay(1500);                    //等待车辆静止
    for (int i = 0; i < 500; i++) {
        imu.getMotion6(&temp1, &temp2, &temp3, &temp4, &temp5, &angleSpeedOri); //获取三轴加速度和三轴角速度初始值
        float angleSpeed0 = angleSpeedOri / coe;
        angleSpeed_sum += angleSpeed0;
        delay(10);
    }
    angleSpeed_bias = angleSpeed_sum / 500;
    Serial.println("IMU initialize finished!");
}

void MyIMU::updateIMU(){
        int16_t angleSpeedOri;  // 角加速度原始数值
        int16_t temp1, temp2, temp3, temp4, temp5;  // 不使用这些变量，仅用于imu函数传参
        imu.getMotion6(&temp1, &temp2, &temp3, &temp4, &temp5, &angleSpeedOri); //获取三轴加速度和三轴角速度初始值
        angleSpeed = angleSpeedOri / coe - angleSpeed_bias;
        float angleAcce;
        curTime = millis();
        double imuUpdateTimeInterval = updateTimeCur - updateTimeLast;
        lastTime=curTime;
        angle += angleAcce * imuUpdateTimeInterval / 1000;
}