#include "encoder.h"
#include "led.h"
Encoder::Encoder(unsigned gpio): _gpio(gpio), _counter(0)
{
    //_gpio = gpio;

    gpioSetMode(gpio, PI_INPUT);
    gpioSetPullUpDown(gpio,PI_PUD_UP);
    // let input signal steady for 100us
    gpioGlitchFilter(gpio, 100);

    // call _pulseProc everytime _gpio change state
}

Encoder::~Encoder()
{
    gpioSetAlertFunc(_gpio, NULL);
}

void Encoder::pulseProc(int gpio, int level, uint32_t tick, void* data)
{
    Encoder* me = (Encoder*) data;
    ++(me->_counter);
    if(me->_led>=0)
    {
        if (level == PI_HIGH){
        Led::getInstance().setLed(me->_led);
        } else
        {
        Led::getInstance().unsetLed(me->_led);
        }
    }
}

int Encoder::getCounter()
{
    return _counter;
}

void Encoder::start()
{
    _counter = 0;
    gpioSetAlertFuncEx(_gpio, pulseProc, this);
}
 void Encoder::stop()
 {
    gpioSetAlertFunc(_gpio, NULL);
    Led::getInstance().unsetLed(_led);
 }

