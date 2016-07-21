#ifndef MOTOR_H
#define MOTOR_H

#include <pigpio.h>

enum class MotorDirection:unsigned char
{
    FORWARD,
    BACKWARD
};

class Motor
{
    private:
        unsigned _enable;
        unsigned _in1;
        unsigned _in2;
        unsigned _pwmDuty;
    public:
        Motor(unsigned enable, unsigned in1, unsigned in2);
        ~Motor();
        void setPWMFrequency(unsigned frequency);
        void setPWMDutyCycle(unsigned dutycycle);
        void run(MotorDirection direction);
        void stop(bool force);
};

#endif // MOTOR_H
