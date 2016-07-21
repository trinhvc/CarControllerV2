#include "motor.h"

Motor::Motor(unsigned enable, unsigned in1, unsigned in2)
{
    _enable = enable;
    _in1 = in1;
    _in2 = in2;
    gpioSetMode(enable, PI_OUTPUT);
    gpioSetMode(in1, PI_OUTPUT);
    gpioSetMode(in2, PI_OUTPUT);
    gpioWrite(enable, PI_LOW);
}

Motor::~Motor()
{
    gpioWrite(_enable, PI_LOW);
}

void Motor::run(MotorDirection direction)
{
    if(MotorDirection::FORWARD == direction)
    {
        gpioWrite(_in1, PI_HIGH);
        gpioWrite(_in2, PI_LOW);
    }
    else
    {
        gpioWrite(_in1, PI_LOW);
        gpioWrite(_in2, PI_HIGH);
    }
    gpioPWM(_enable, _pwmDuty);
}

void Motor::stop(bool force)
{
    gpioWrite(_enable, PI_LOW);
    if(true == force)
    {
        gpioWrite(_in1, PI_HIGH);
        gpioWrite(_in2, PI_HIGH);
        gpioWrite(_enable, PI_HIGH);
    }
}

void Motor::setPWMFrequency(unsigned frequency)
{
    gpioSetPWMfrequency(_enable, frequency);
}
void Motor::setPWMDutyCycle(unsigned dutycycle)
{
    _pwmDuty = dutycycle;
}




