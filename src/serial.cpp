#include "serial.h"

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


void Serial::write(char* message, unsigned length)
{
    serWrite(_handle, message, length);
}

