#ifndef _CHASSIS_H
#define _CHASSIS_H

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

    // 电机转速 (percent 0-100)
    float motor_speed_[4]{0, 0, 0, 0};

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

    /// @todo 平移+旋转模型解算
    // /// @brief 沿指定方向直线移动，方向表示为为y轴正半轴极坐标
    // /// @note 基础函数，无PID
    // /// @param speed 移动速度(percent)
    // /// @param angleTar 目标方向(radians)
    // void LineMoveByAngle_Base(float speed, float angleTar);

    // /// @brief 绕中心旋转
    // /// @note 基础函数，无PID
    // /// @param speed 旋转速度(percent)，逆时针为正，顺时针为负
    // void Rotate_Base(float speed);

    // ---------------------------------------------

public:
    // 获取单例
    static Chassis *GetInstance();

    // 删除单例
    static void DeleteInstance();

    // 控制函数
    // ---------------------------------------------

    // 刹车
    void Stop();

    // 刷新电机转速
    void UpdateMotorSpeed();

    // ---------------------------------------------
};

#endif  //_CHASSIS_H