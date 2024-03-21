#include "Car.h"

Car *Car::instance_ptr_ = nullptr;

Car *Car::GetInstance() {
    if (!instance_ptr_) {
        instance_ptr_ = new Car;
    }
    return instance_ptr_;
}

void Car::DeleteInstance() {
    if (instance_ptr_) {
        delete instance_ptr_;
        instance_ptr_ = nullptr;
    }
}