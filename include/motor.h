#ifndef MOTOR_H
#define MOTOR_H

#include <pigpio.h>

enum class MotorDirection
{
    FORWARD,
    BACKWARD
};

class Motor
{
    private:
        int _enable;
        int _in1;
        int _in2;
        int _led;
        bool _isRunning;
    public:
        Motor(int enable, int in1, int in2);
        ~Motor();
        void setPWMDutyCycle(int dutycycle);
        void run(MotorDirection direction, int duycycle);
        void stop(bool force);
        void setLed(int led){_led = led;}
};

#endif // MOTOR_H
