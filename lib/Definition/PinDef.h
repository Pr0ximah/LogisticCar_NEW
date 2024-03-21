#ifndef _PIN_DEF_H
#define _PIN_DEF_H

const int tx_IMU = 13; // IMUtx 接入 软串口rx
const int rx_IMU = 9; // IMUrx 接入 软串口tx

// 电机端口
const int port_motor_FL = 10;  // 左前电机PWM
const int port_motor_FR = 9;  // 右前电机PWM
const int port_motor_BL = 5;   // 左后电机PWM
const int port_motor_BR = 4;   // 右后电机PWM
const int port_dir_FL = 12;    // 左前电机方向
const int port_dir_FR = 11;    // 右前电机方向
const int port_dir_BL = 7;     // 左后电机方向
const int port_dir_BR = 6;     // 右后电机方向

#endif  //_PIN_DEF_H