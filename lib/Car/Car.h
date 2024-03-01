#ifndef _CAR_H
#define _CAR_H

/// @brief 小车总控类，包含底盘+机械臂
/// @note 使用单例模式
/// @date 2024.03.01
class Car {
private:
    // 单例指针
    static Car *instance_ptr_;

    // 防止构造
    Car() = default;

    // 防止析构
    ~Car() = default;

    // 其他禁用函数
    Car(const Car &) = delete;
    Car &operator=(const Car &) = delete;

    class Deleter {
    public:
        ~Deleter() {
            if (Car::instance_ptr_) {
                delete Car::instance_ptr_;
                Car::instance_ptr_ = nullptr;
            }
        }
    };

public:
    // 获取单例
    static Car *GetInstance();

    // 删除单例
    static void DeleteInstance();
};

#endif  //_CAR_H