#ifndef SERIAL_H
#define SERIAL_H

#include <string>
using namespace std;
class Serial
{
    private:
        int _handle;
    public:
        Serial(char* device, int baudrate);
        ~Serial();
        int dataAvailable();
        char readChar();
        void writeChar(char c);
        void write(string message);
};

#endif // SERIAL_H
