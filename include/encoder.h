#ifndef ENCODER_H
#define ENCODER_H

#include <pigpio.h>

class Encoder
{
private:
    int _gpio;
    int _counter;
    static void pulseProc(int gpio, int level, uint32_t tick, void *data);
public:
    Encoder(unsigned gpio);
    ~Encoder();
    int getCounter();
    void resetCounter();
};

#endif // ENCODER_H
