#include "serial.h"
#include <pigpio.h>
Serial::Serial(char* device, int baudrate)
{
    _handle = serOpen(device, baudrate, 0);
}

Serial::~Serial()
{
    if(_handle >= 0)
    {
        serClose(_handle);
    }
}

void Serial::writeChar(char c)
{
    serWriteByte(_handle, c);
}

char Serial::readChar()
{
    return serReadByte(_handle);
}


void Serial::write(string message)
{
    //serWrite(_handle, message, message.length());
}

int Serial::dataAvailable()
{
    return serDataAvailable(_handle);
}
