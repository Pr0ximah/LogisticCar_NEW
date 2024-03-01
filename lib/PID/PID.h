#ifndef _PID_H
#define _PID_H

/// @brief PID控制器类
/// @date 2024.03.01
class PID_Controller {
private:
    double target_ = 0;
    double input_ = 0;
    double error_current_ = 0, error_last_ = 0;
    double error_diff_ = 0;
    double error_integral_ = 0;

    // I最大值
    double I_max_ = 10;

    // I控制阈值(P)
    double I_range_ = 10;

    // 退出输出阈值
    double output_range_ = 10;

    double error_tolerance_ = 0;
    double kp_ = 0, ki_ = 0, kd_ = 0;
    double output_ = 0;

    // PID稳定开始时间(msec)
    int stabilization_start_time_ = 0;

    // 稳定后退出前保持的时间(msec)
    int jump_time_ = 1000;

    // 稳定时间 (msec)，-1标志位表示未稳定
    int stabilization_time_ = -1;

    // 是否持续控制
    bool persistent_control_ = false;

    // 更新输出量
    void UpdateOutput();

public:
    PID_Controller() = default;

    /// @brief 更新控制器
    /// @param input 系统输入量
    void UpdateController(double input);

    /// @brief 获取系统输出值
    /// @return 输出量
    double GetOutput();

    // 参数设置
    void SetParameters(double kp, double ki, double kd);
    void SetIMax(double I_max);
    void SetPersistentControl(bool is_persistent);
    void SetJumpTime(int jump_time);
    void SetOutputRange(double output_range);
};

int Sign(double val) {
    if (val >= 0) {
        return 1;
    } else {
        return -1;
    }
}

#endif  //_PID_H