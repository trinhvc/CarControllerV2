#ifndef CAR_H
#define CAR_H


#include "motor.h"
#include "encoder.h"
#include "sonar.h"
#include "constants.h"
enum class CarSpeed
{
    SLOW,
    MEDIUM,
    FAST
};

enum class CarDirection
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

class Car
{
    private:
        Motor _leftMotor;
        Motor _rightMotor;
        Encoder _leftEncoder;
        Encoder _rightEncoder;
        Sonar _sonar1;
        Sonar _sonar2;
        Sonar _sonar3;
        Sonar _sonar4;
        int _speed;
        int _minPing;
        int moveCar(CarDirection direction, int pulse);
        int rotateCar(CarDirection direction, int pulse);
        int rotateCarEx(CarDirection direction, int degree);
        Car();
        Car(Car const&);
        void operator = (Car const&);
    public:
        static Car& getInstance();
        ~Car();
        int moveForward(int distance);
        int moveBackward(int distance);
        int rotateLeft(int degree);
        int rotateRight(int degree);
        void stop();
        void test();
        void setSpeed(int level);
};

#endif // CAR_H
