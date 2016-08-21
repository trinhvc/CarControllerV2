#ifndef LED_H
#define LED_H

#include "constants.h"
#include <unistd.h>
class Led
{
    private:
        int _status[10];
    public:
        Led()
        {
            for(int i = 0; i < 10; i++)
            {
                _status[i] = 0;
            }
            gpioSetMode(INDICATOR_EN, PI_OUTPUT);
            gpioSetMode(INDICATOR_PULSE, PI_OUTPUT);
            gpioSetMode(INDICATOR_BUZZER, PI_OUTPUT);
            gpioSetMode(INDICATOR_RESET, PI_OUTPUT);
            gpioWrite(INDICATOR_RESET, PI_LOW);
            gpioWrite(INDICATOR_EN, PI_LOW);
            gpioWrite(INDICATOR_PULSE, PI_LOW);
            gpioWrite(INDICATOR_BUZZER, PI_LOW);
        }

        static Led& getInstance()
        {
            static Led instance;
            return instance;
        }

        void setReady(int val)
        {
            _status[5] = val;
        }
        void setData(int val)
        {
            _status[2] = val;
        }
        void setEncoder1(int val)
        {
            _status[4] = val;
        }
        void setEncoder2(int val)
        {
            _status[6] = val;
        }
        void setMotor1(int val)
        {
            _status[3] = val;
        }
        void setMotor2(int val)
        {
            _status[9] = val;
        }
        void setSonar1(int val)
        {
            _status[0] = val;
        }
        void setSonar2(int val)
        {
            _status[1] = val;
        }
        void setSonar3(int val)
        {
            _status[7] = val;
        }
        void setSonar4(int val)
        {
            _status[8] = val;
        }
        void setLed(int led)
        {
            _status[led] = 1;
        }
        void unsetLed(int led)
        {
            _status[led] = 0;
        }
        void buzz()
        {
            gpioWrite(INDICATOR_BUZZER, PI_HIGH);
            usleep(100000);
            gpioWrite(INDICATOR_BUZZER, PI_LOW);
            usleep(200000);
            gpioWrite(INDICATOR_BUZZER, PI_HIGH);
            usleep(100000);
            gpioWrite(INDICATOR_BUZZER, PI_LOW);
        }
        void start()
        {
            while(true)
            {
                gpioTrigger(INDICATOR_RESET, 1, PI_HIGH);
                for(int i = 0 ; i < 10 ; i++)
                {
                    if(_status[i] == 1)
                    {
                        gpioWrite(INDICATOR_EN, PI_HIGH);
                        usleep(1000);
                        gpioWrite(INDICATOR_EN, PI_LOW);
                    }
                    gpioTrigger(INDICATOR_PULSE, 1, PI_HIGH);
                }
            }
        }

};

#endif // LED_H
