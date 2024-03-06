#ifndef _CHASSIS_H
#define _CHASSIS_H

#include "Geometry.h"

/// @brief 底盘类，控制小车运动
/// @date 2024.03.01
class Chassis {
private:
    // 单例指针
    static Chassis *instance_ptr_;

    // 防止构造
    Chassis();

    // 防止析构
    ~Chassis() = default;

    // 其他禁用函数
    Chassis(const Chassis &) = delete;
    Chassis &operator=(const Chassis &) = delete;

    class Deleter {
    public:
        ~Deleter() {
            if (Chassis::instance_ptr_) {
                delete Chassis::instance_ptr_;
                Chassis::instance_ptr_ = nullptr;
            }
        }
    };

    // 电机转速 (percent 0~100)
    double motor_speed_[4]{0, 0, 0, 0};

    // 运动速度信息
    // ---------------------------------------------

    // Y轴速度 (percent -100~100)
    double speed_Y_ = 0;

    // X轴速度 (percent -100~100)
    double speed_X_ = 0;

    // 旋转速度，逆时针为正 (percent -100~100)
    double speed_Rotate_ = 0;

    // ---------------------------------------------

    // 底层驱动函数模块
    // ---------------------------------------------

    // 电机驱动-左前
    void MotorSpinFL(double percent);
    // 电机驱动-右前
    void MotorSpinFR(double percent);
    // 电机驱动-左后
    void MotorSpinBL(double percent);
    // 电机驱动-右后
    void MotorSpinBR(double percent);

    // 设置电机转速，自动归一化
    void SetMotorSpeed(double FL, double FR, double BL, double BR);

    // 应用电机转速
    void ApplyMotorSpeed();

    // ---------------------------------------------

public:
    // 获取单例
    static Chassis *GetInstance();

    // 删除单例
    static void DeleteInstance();

    // 控制函数
    // ---------------------------------------------

    /// @brief 设置平移状态
    /// @param dir 平移方向，二维向量 (x, y)
    /// @param speed 平移速度 (percent 0~100)
    void SetMove(Vector2D dir, double speed);

    /// @brief 设置旋转状态
    /// @param speed 旋转速度 (percent -100~100)，逆时针为正
    void SetRotate(double speed);

    // 刹车
    void Stop();

    // 根据设置底盘速度刷新电机转速
    void UpdateChassis();

    // ---------------------------------------------
};

#endif  //_CHASSIS_H