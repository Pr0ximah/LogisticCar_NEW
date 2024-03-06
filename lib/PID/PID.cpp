#include "PID.h"

#include <Arduino.h>

void PID_Controller::SetIMax(double I_max) { I_max_ = I_max; }

void PID_Controller::SetJumpTime(int jump_time) { jump_time_ = jump_time; }

void PID_Controller::SetPersistentControl(bool is_persistent) { persistent_control_ = is_persistent; }

void PID_Controller::SetOutputRange(double output_range) { output_range_ = output_range; }

void PID_Controller::SetParameters(double kp, double ki, double kd) {
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

void PID_Controller::UpdateController(double input) {
    input_ = input;
    UpdateOutput();
}

void PID_Controller::UpdateOutput() {
    double P = 0, I = 0, D = 0;
    error_last_ = error_current_;
    error_current_ = target_ - input_;
    error_diff_ = error_current_ - error_last_;
    P = kp_ * error_current_;
    D = kd_ * error_diff_;
    if (abs(P) > I_range_ || Sign(error_integral_) != Sign(error_current_) || abs(error_current_) < error_tolerance_)) {
        error_integral_ = 0;
    }
    else {
        error_integral_ += error_current_;
        I = ki_ * error_integral_;
        if (abs(I) > I_max_) {
            I = Sign(I) * I_max_;
        }
    }
    double output_temp = P + I + D;
    if (abs(error_current_) <= error_tolerance_ && !persistent_control_ && abs(output_temp) <= output_range_) {
        if (stabilization_start_time_ != -1) {
            stabilization_start_time_ = micros();
        } else {
            stabilization_time_ = micros() - stabilization_start_time_;
        }
        if (stabilization_time_ >= jump_time_) {
            output_temp = 0;
        }
    } else {
        stabilization_start_time_ = -1;
    }
    output_ = output_temp;
}

double PID_Controller::GetOutput() { return output_; }