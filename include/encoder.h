#ifndef ENCODER_H
#define ENCODER_H

#include <pigpio.h>

class Encoder
{
private:
    int _gpio;
    int _counter;
    int _led;
    static void pulseProc(int gpio, int level, uint32_t tick, void *data);
public:
    Encoder(unsigned gpio);
    ~Encoder();
    int getCounter();
    void start();
    void stop();
    void setLed(int led){_led = led;}
};

#endif // ENCODER_H
