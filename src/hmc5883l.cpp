#include "hmc5883l.h"
#include "constants.h"
#include <cmath>
#include <unistd.h>
#include <pigpio.h>

HMC5883L::HMC5883L()
{
    _handle = i2cOpen(1, 0x1E, 0);

}

HMC5883L::~HMC5883L()
{

    i2cClose(_handle);
}

int HMC5883L::getAngle()
{
    short x, y;
    int msb, lsb;
    i2cWriteByteData(_handle, 0x02, 0x00); // enter continuous mode
    msb = i2cReadByteData(_handle, 0x03);
    lsb = i2cReadByteData(_handle, 0x04);
    x = (msb << 8) | lsb;
    msb = i2cReadByteData(_handle, 0x07);
    lsb = i2cReadByteData(_handle, 0x08);
    y = (msb << 8) | lsb;
    i2cWriteByteData(_handle, 0x02, 0x02); // enter idle mode
    double rad = atan2(y, x);
    double degree = round(rad * 180 / PI + 180);
    return (int) degree;
}
