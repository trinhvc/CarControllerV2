#include "sonar.h"
#include <unistd.h>
Sonar::Sonar(int trigger, int echo): _trigger(trigger), _echo(echo)
{
    gpioSetMode(trigger, PI_OUTPUT);
    gpioWrite(trigger, PI_LOW);

    gpioSetMode(echo, PI_INPUT);
    gpioSetAlertFuncEx(_echo, echoProc, this);
}

void Sonar::pullTrigger()
{
    gpioWrite(_trigger, PI_HIGH);
    usleep(10); // 10us
    gpioWrite(_trigger, PI_LOW);
}

void Sonar::echoProc(int gpio, int level, uint32_t tick, void* data)
{
    static uint32_t startTick;
    Sonar* me = (Sonar*) data;
    if(PI_HIGH == level)
    {
        startTick = tick;
    }
    else
    {
        me->_ping = tick - startTick;
    }
}

int Sonar::ping()
{
    pullTrigger();
    _ping = -1;
    usleep(30*1000); //30 ms
    return _ping;
}

Sonar::~Sonar()
{
    gpioSetAlertFunc(_echo, NULL);
}
