#include "Chassis.h"

Chassis *Chassis::instance_ptr_ = nullptr;

Chassis::Chassis() {
    // 电机端口初始化
    pinMode(port_motor_FL, OUTPUT);
    pinMode(port_motor_FR, OUTPUT);
    pinMode(port_motor_BL, OUTPUT);
    pinMode(port_motor_BR, OUTPUT);
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
    if (sign(percent) == -1) {
        digitalWrite(port_dir_FL, HIGH);
        analogWrite(port_motor_FL, -255 * percent / 100);
    } else {
        digitalWrite(port_dir_FL, LOW);
        analogWrite(port_motor_FL, 255 * percent / 100);
    }
}

void Chassis::MotorSpinFR(double percent) {
    if (sign(percent) == -1) {
        digitalWrite(port_dir_FR, LOW);
        analogWrite(port_motor_FR, -255 * percent / 100);
    } else {
        digitalWrite(port_dir_FR, HIGH);
        analogWrite(port_motor_FR, 255 * percent / 100);
    }
}

void Chassis::MotorSpinBL(double percent) {
    if (sign(percent) == -1) {
        digitalWrite(port_dir_BL, HIGH);
        analogWrite(port_motor_BL, -255 * percent / 100);
    } else {
        digitalWrite(port_dir_BL, LOW);
        analogWrite(port_motor_BL, 255 * percent / 100);
    }
}

void Chassis::MotorSpinBR(double percent) {
    if (sign(percent) == -1) {
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
            speeds[]{FL, FR, BL, BR};
        }
    }
    motor_speed_ = {FL, FR, BL, BR};
}

void Chassis::Stop() { SetMotorSpeed(0, 0, 0, 0); }

void Chassis::UpdateMotorSpeed() {
    MotorSpinFL(motor_speed_[0]);
    MotorSpinFR(motor_speed_[1]);
    MotorSpinBL(motor_speed_[2]);
    MotorSpinBR(motor_speed_[3]);
}

/// @todo 平移+旋转模型解算
// --------------------------------------------------------------------------
// void Chassis::LineMoveByAngle_Base(float speed, float angleTar) {
//     float trans_Angle = dirAngle + PI / 4;  // 角度换算
//     double v_FL, v_FR, v_BL, v_BR;          // 左前和右后一致 右前和左后一致
//     v_FL = speed * cos(trans_Angle);
//     v_BR = speed * cos(trans_Angle);
//     v_FR = speed * sin(trans_Angle);
//     v_BL = speed * sin(trans_Angle);

//     SetMotorSpeed(v_FL, v_FR, v_BL, v_BR);
// }

// void Chassis::LineMoveByAngle_Base(float speed, float angleTar) {
//     float trans_Angle = dirAngle + PI / 4;  // 角度换算
//     double v_FL, v_FR, v_BL, v_BR;          // 左前和左后一致 右前和右后一致
//     v_FL = -speed;
//     v_BR = speed;
//     v_FR = -speed;
//     v_BL = speed;

//     SetMotorSpeed(v_FL, v_FR, v_BL, v_BR);
// }
// --------------------------------------------------------------------------