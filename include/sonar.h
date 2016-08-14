#ifndef SONAR_H
#define SONAR_H

#include <pigpio.h>
class Sonar
{
    private:
        int _trigger;
        int _echo;
        int _ping;
        void pullTrigger();
        static void echoProc(int gpio, int level, uint32_t tick, void *data);
    public:
        Sonar(int trigger, int echo);
        int ping();
        ~Sonar();
};

#endif // SONAR_H
