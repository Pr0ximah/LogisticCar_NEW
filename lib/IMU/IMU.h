#ifndef _IMU_H
#define _IMU_H

/// @brief heading初始值，缺省401
static double heading_original = 401;

/// @brief 初始化IMU，启动软串口
void IMU_Init();

/// @brief 获取IMU当前朝向，(-180, 180] (deg)
double IMU_Heading();

#endif  //_IMU_H