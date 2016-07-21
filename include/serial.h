#ifndef SERIAL_H
#define SERIAL_H

#include <pigpio.h>
class Serial
{
    private:
        unsigned _handle;
    public:
        Serial(char* device, int baudrate);
        ~Serial();
        char readChar();
        void writeChar(char c);
        void write(char* message, unsigned length);


};

#endif // SERIAL_H
