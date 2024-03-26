#ifndef _IMU_H
#define _IMU_H

#include <MPU6050.h>
#include "Wire.h"
class myIMU{
private:
    MPU6050 mpu;
    static myIMU *instance_ptr_;
    double curTime=0;
    double lastTime=0;
    double angleSpeed;
    double angle;
    double angleSpeed_bias;
    const double coe=65.5;
public:
    static myIMU *GetInstance(){
        if (!instance_ptr_) {
       instance_ptr_ = new myIMU;
        }
        return instance_ptr_;
    }
    myIMU(){
        angleSpeed=0;
        angle =0;
        angleSpeed_bias=0;
    }
    void resetIMU(){
        angle=0;
        angleSpeed=0;
    }
    void setIMU(double ANGLE){
        angle=ANGLE;
    }
    void InitIMU();
    void updateIMU();
    double ReadAngleSpeed();
    double getAngle(){
        return angle;
    }


};
#endif  //_IMU_H
