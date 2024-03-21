#ifndef _IMU_H
#define _IMU_H

#include <MPU6050.h>
class myIMU{
private:
    MPU6050 imu;
    double curTime=0;
    double lastTime=0;
    double angleSpeed;
    double angle;
    double angleSpeed_bias;
    const double coe=65.5;
public:
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
