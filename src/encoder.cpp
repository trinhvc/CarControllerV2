#include "encoder.h"

Encoder::Encoder(unsigned gpio): _gpio(gpio), _counter(0)
{
    //_gpio = gpio;

    gpioSetMode(gpio, PI_INPUT);

    // let input signal steady for 50us
    gpioGlitchFilter(gpio, 50);

    // call _pulseProc everytime _gpio change state
    gpioSetAlertFuncEx(gpio, pulseProc, this);
}

Encoder::~Encoder()
{
    gpioSetAlertFunc(_gpio, NULL);
}

void Encoder::pulseProc(int gpio, int level, uint32_t tick, void* data)
{
    Encoder* me = (Encoder*) data;
    ++(me->_counter);
}

int Encoder::getCounter()
{
    return _counter;
}

void Encoder::resetCounter()
{
    _counter = 0;
}


