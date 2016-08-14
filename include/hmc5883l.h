#ifndef HMC5883L_H
#define HMC5883L_H


class HMC5883L
{
    private:
        int _handle;
    public:
        HMC5883L();
        int getAngle();
        ~HMC5883L();
};

#endif // HMC5883L_H
