#include "motor.h"
#include "led.h"
Motor::Motor(int enable, int in1, int in2)
{
    _enable = enable;
    _in1 = in1;
    _in2 = in2;
    _led = -1;
    _isRunning = false;
    gpioSetMode(enable, PI_OUTPUT);
    gpioSetPWMfrequency(enable, 40);
    gpioWrite(enable, PI_LOW);
    gpioSetMode(in1, PI_OUTPUT);
    gpioSetMode(in2, PI_OUTPUT);
}

Motor::~Motor()
{
    gpioWrite(_enable, PI_LOW);
}

void Motor::run(MotorDirection direction, int dutycycle)
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
    gpioPWM(_enable, dutycycle);
    _isRunning = true;
    if (_led >=0)
    {
    Led::getInstance().setLed(_led);
    }
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
    _isRunning = false;
    if (_led >=0)
    {
        Led::getInstance().unsetLed(_led);
    }
}

void Motor::setPWMDutyCycle(int dutycycle)
{
    if(_isRunning)
    {
        gpioPWM(_enable, dutycycle);
    }
}




