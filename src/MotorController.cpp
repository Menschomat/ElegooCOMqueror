#include "MotorController.h"
#include "Globals.h"

DeviceDriverSet_Motor AppMotor;
Application_xxx Application_ConquerorCarxxx0;
MPU6050_getdata AppMPU6050getdata;
int m_speed = 128;
ConquerorCarMotionControl status = stop_it;

void initializeMotors()
{
    setColor(255, 255, 0);
    AppMotor.DeviceDriverSet_Motor_Init();
    AppMPU6050getdata.MPU6050_dveInit();
    delay(2000);
    AppMPU6050getdata.MPU6050_calibration();
    setColor(0, 255, 0);
    delay(500);
    setColor(0, 0, 0);
}

void updateCarMotion()
{
    ApplicationFunctionSet_ConquerorCarMotionControl(status, m_speed);
}
