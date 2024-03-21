#include "Chassis.h"

#include <Arduino.h>
#include <math.h>

#include "PinDef.h"
#include "IMU.h"

Chassis *Chassis::instance_ptr_ = nullptr;

Chassis::Chassis() {
    // 电机端口初始化
    pinMode(port_motor_FL, OUTPUT);
    pinMode(port_motor_FR, OUTPUT);
    pinMode(port_motor_BL, OUTPUT);
    pinMode(port_motor_BR, OUTPUT);

    // heading PID参数初始化
    heading_pid.SetParameters(heading_pid_param[0], heading_pid_param[1], heading_pid_param[2]);
    heading_pid.SetPersistentControl(true);
}

Chassis *Chassis::GetInstance() {
    if (!instance_ptr_) {
        instance_ptr_ = new Chassis;
    }
    return instance_ptr_;
}

void Chassis::DeleteInstance() {
    if (instance_ptr_) {
        delete instance_ptr_;
        instance_ptr_ = nullptr;
    }
}

void Chassis::MotorSpinFL(double percent) {
    if (Sign(percent) == -1) {
        digitalWrite(port_dir_FL, HIGH);
        analogWrite(port_motor_FL, -255 * percent / 100);
    } else {
        digitalWrite(port_dir_FL, LOW);
        analogWrite(port_motor_FL, 255 * percent / 100);
    }
}

void Chassis::MotorSpinFR(double percent) {
    if (Sign(percent) == -1) {
        digitalWrite(port_dir_FR, LOW);
        analogWrite(port_motor_FR, -255 * percent / 100);
    } else {
        digitalWrite(port_dir_FR, HIGH);
        analogWrite(port_motor_FR, 255 * percent / 100);
    }
}

void Chassis::MotorSpinBL(double percent) {
    if (Sign(percent) == -1) {
        digitalWrite(port_dir_BL, HIGH);
        analogWrite(port_motor_BL, -255 * percent / 100);
    } else {
        digitalWrite(port_dir_BL, LOW);
        analogWrite(port_motor_BL, 255 * percent / 100);
    }
}

void Chassis::MotorSpinBR(double percent) {
    if (Sign(percent) == -1) {
        digitalWrite(port_dir_BR, LOW);
        analogWrite(port_motor_BR, -255 * percent / 100);
    } else {
        digitalWrite(port_dir_BR, HIGH);
        analogWrite(port_motor_BR, 255 * percent / 100);
    }
}

void Chassis::SetMotorSpeed(double FL, double FR, double BL, double BR) {
    double k = 0;  // 归一化系数
    double speeds[]{FL, FR, BL, BR};
    for (int i = 0; i < 4; i++) {
        double speed = speeds[i];
        if (abs(speed) > 100) {
            k = abs(100 / speed);
            FL *= k;
            FR *= k;
            BL *= k;
            BR *= k;
            speeds[0] = FL;
            speeds[1] = FR;
            speeds[2] = BL;
            speeds[3] = BR;
        }
    }
    motor_speed_[0] = FL;
    motor_speed_[1] = FR;
    motor_speed_[2] = BL;
    motor_speed_[3] = BR;
}

void Chassis::Stop() {
    speed_X_ = 0;
    speed_Y_ = 0;
    speed_Rotate_ = 0;
    motor_speed_[0] = 0;
    motor_speed_[1] = 0;
    motor_speed_[2] = 0;
    motor_speed_[3] = 0;
    ApplyMotorSpeed();
}

void Chassis::ApplyMotorSpeed() {
    MotorSpinFL(motor_speed_[0]);
    MotorSpinFR(motor_speed_[1]);
    MotorSpinBL(motor_speed_[2]);
    MotorSpinBR(motor_speed_[3]);
}

void Chassis::UpdateChassis() {
    double FL = 0, FR = 0, BL = 0, BR = 0;

    // 运动解算
    FL = speed_Y_ + speed_X_ - speed_Rotate_;
    FR = speed_Y_ - speed_X_ + speed_Rotate_;
    BL = speed_Y_ - speed_X_ - speed_Rotate_;
    BR = speed_Y_ + speed_X_ + speed_Rotate_;

    String str = "FL: " + String(FL) + ", FR: " + String(FR) + ", BL: " + String(BL) + ", BR: " + String(BR);
    Serial.println(str);
    SetMotorSpeed(FL, FR, BL, BR);
    ApplyMotorSpeed();
    heading_pid.UpdateController(IMU_Heading());
    SetRotate(heading_pid.GetOutput());
}

void Chassis::SetMove(Vector2D dir, double speed) {
    double ang = dir.GetAngleRad();
    Serial.println(ang);
    speed_X_ = speed * cos(ang);
    speed_Y_ = speed * sin(ang);
    String str = "speed_X: " + String(speed_X_) + ", speed_Y: " + String(speed_Y_);
    heading_pid.SetTarget(IMU_Heading());
    Serial.println(str);
}

void Chassis::SetRotate(double speed) { speed_Rotate_ = speed; }