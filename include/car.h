#ifndef CAR_H
#define CAR_H


#include "motor.h"
#include "encoder.h"
#include "sonar.h"
#include "hmc5883l.h"
enum class CarSpeed
{
    SLOW,
    MEDIUM,
    FAST
};

enum class CarDirection
{
    FORWARD=1,
    BACKWARD=2,
    LEFT=3,
    RIGHT=4
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
        HMC5883L _compass;
        int _speed;
        int _minPing;
        void moveCar(CarDirection direction, int pulse);
        void turnCar(CarDirection direction, int degree);
        void rotateCar(CarDirection direction, int degree);
        void rotateCarEx(CarDirection direction, int degree);
        Car();
        Car(Car const&);
        void operator = (Car const&);
    public:
        static Car& getInstance();
        void moveForward(int distance);
        void moveBackward(int distance);
        void turnLeft(int degree);
        void turnRight(int degree);
        void rotateLeft(int degree);
        void rotateRight(int degree);
        void stop();
        void test();
        void setSpeed(int level);
};

#endif // CAR_H
