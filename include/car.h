#ifndef CAR_H
#define CAR_H


#include "motor.h"
#include "encoder.h"
enum class CarSpeed: unsigned char
{
    SLOW = 31;
    MEDIUM = 63;
    FAST = 127
};

class Car
{
    private:


    public:
        Car();
        void moveForward();
        void moveBackward();
        void turnLeft();
        void turnRight();
        void rotateLeft();
        void rotateRight();
        void setSpeed();
};

#endif // CAR_H
