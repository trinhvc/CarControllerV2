#include "car.h"
#include "hmc5883l.h"
#include "constants.h"
#include "sonar.h"
#include <unistd.h>
#include <iostream>
using namespace std;

Car::Car():
    _leftMotor(BRIDGE2_ENABLE, BRIDGE2_IN1, BRIDGE2_IN2),
    _rightMotor(BRIDGE1_ENABLE, BRIDGE1_IN1, BRIDGE1_IN2),
    _leftEncoder(ENCODER2),
    _rightEncoder(ENCODER1),
    _sonar1(TRIGGER1, ECHO1),
    _sonar2(TRIGGER2, ECHO2),
    _sonar3(TRIGGER3, ECHO3),
    _sonar4(TRIGGER4, ECHO4)
{
    setSpeed(0);
    cout << "car created" << endl;
}

Car::~Car()
{
    cout << "car deleted" << endl;
}

Car& Car::getInstance()
{
    static Car instance;
    return instance;
}

int Car::rotateCar(CarDirection direction, int pulse)
{
    int leftPulse = 0;
    int rightPulse = 0;
    _leftEncoder.resetCounter();
    _rightEncoder.resetCounter();
    int rotateSpeed = 31;
    if(CarDirection::LEFT == direction)
    {
        _rightMotor.run(MotorDirection::FORWARD, rotateSpeed);
        _leftMotor.run(MotorDirection::BACKWARD, rotateSpeed);
    }
    else
    {
        _leftMotor.run(MotorDirection::FORWARD, rotateSpeed);
        _rightMotor.run(MotorDirection::BACKWARD, rotateSpeed);
    }
    while(leftPulse < pulse && rightPulse < pulse)
    {
        leftPulse = _leftEncoder.getCounter();
        rightPulse = _rightEncoder.getCounter();
        usleep(100);
    }
    _leftMotor.stop(false);
    _rightMotor.stop(false);
    return 1;
}

/*
int Car::rotateCarEx(CarDirection direction, int degree)
{
    int measured = 0;
    HMC5883L compass;
    int lastAngle = compass.getAngle();
    if(CarDirection::LEFT == direction)
    {
        _leftMotor.run(MotorDirection::BACKWARD, _speed);
        _rightMotor.run(MotorDirection::FORWARD, _speed);
    }
    else if(CarDirection::RIGHT == direction)
    {
        _rightMotor.run(MotorDirection::BACKWARD, _speed);
        _leftMotor.run(MotorDirection::FORWARD, _speed);
    }
    while(measured < degree)
    {
        int currentAngle = compass.getAngle();
        int diffAngle = currentAngle - lastAngle;
        lastAngle = currentAngle;
        if(diffAngle < 0)
        {
            diffAngle = -diffAngle;
        }
        if(diffAngle > 180)
        {
            diffAngle = 360 - diffAngle;
        }
        measured += diffAngle;
        usleep(1000);
        cout << "current angle: " << currentAngle << endl;
        cout << "diff angle: " << diffAngle << endl;
        cout << "measure angle: " << measured << endl;
    }
    _leftMotor.stop(false);
    _rightMotor.stop(false);
    return 1;
}
*/

int Car::moveCar(CarDirection direction, int pulse)
{
    int ping1;
    int ping2;
    MotorDirection md;
    if(CarDirection::FORWARD == direction)
    {
        md = MotorDirection::FORWARD;
        _leftMotor.run(md, _speed);
        _rightMotor.run(md, _speed);
        ping1 = _sonar2.ping();
        ping2 = _sonar3.ping();
    }
    else
    {
        md = MotorDirection::BACKWARD;
        _leftMotor.run(md, _speed);
        _rightMotor.run(md, _speed);
        ping1 = _sonar1.ping(); // back right
        ping2 = _sonar4.ping(); //back left
    }
    // check distance once before moving
    if(ping1 < _minPing && ping2 < _minPing)
    {
        _leftMotor.stop(true);
        _rightMotor.stop(true);
        return -1;
    }
    _leftEncoder.resetCounter();
    _rightEncoder.resetCounter();
    int leftPulse = 0;
    int rightPulse = 0;
    bool switcher = true;
    int slowPulse = 0.8 * pulse;
    int sslowPulse = 0.9 * pulse;
    bool isSlow = false;
    bool isSSlow = false;
    while(leftPulse < pulse && rightPulse < pulse)
    {
        // check if distance reached
        // check if any blockage
        // then stop until unblocked
        //cout << leftPulse << endl << rightPulse << endl;
        /*
        do
        {
            int ping1 =0 , ping2;
            if(CarDirection::FORWARD == direction)
            {
                ping1 = _sonar2.ping();
                ping2 = _sonar3.ping();
            }
            else
            {
                ping1 = _sonar1.ping(); // back right
                ping2 = _sonar4.ping(); //back left
            }


            if(ping1 < _minPing && ping2 < _minPing)
            {
                if(!isBlocked)
                {
                    isBlocked = true;
                    cout << "block : " << ping1 << ", " << ping2 << endl;
                    _leftMotor.stop(true);
                    _rightMotor.stop(true);
                }
                usleep(100000); // 1 second
            }
            else
            {
                if(isBlocked)
                {
                    isBlocked = false;
                    cout << "unblock : " << ping1 << ", " << ping2 << endl;
                    _leftMotor.run(md, _speed);
                    _rightMotor.run(md, _speed);
                }
            }
        }
        while(isBlocked);
        */
        if(CarDirection::FORWARD == direction)
        {
            if(switcher)
            {
                ping1 = _sonar2.ping();
            }
            else
            {
                ping2 = _sonar3.ping();
            }
        }
        else
        {
            if(switcher)
            {
                ping1 = _sonar1.ping(); // back right
            }
            else
            {
                ping2 = _sonar4.ping(); //back left
            }
        }
        //cout << ping1 << " vs " << ping2 << endl;
        if(ping1 < _minPing || ping2 < _minPing)
        {
            _leftMotor.stop(true);
            _rightMotor.stop(true);
            cout << "blocked while running" << endl;
            return -1;
        }
        switcher = !switcher;
        leftPulse = _leftEncoder.getCounter();
        rightPulse = _rightEncoder.getCounter();
        //cout << leftPulse << " vs " << rightPulse << endl;
        int leftSpeed = _speed;
        leftSpeed += (rightPulse - leftPulse);
        _leftMotor.run(md, leftSpeed);
        if(slowPulse > 20 && leftPulse > slowPulse)
        {
            if(!isSlow)
            {
                _leftMotor.run(md, _speed / 2);
                _rightMotor.run(md, _speed / 2);
                cout << pulse << " slow: " << slowPulse << endl;
                isSlow = true;
            }
            else
            {
                if(leftPulse > sslowPulse)
                {
                    if(!isSSlow)
                    {
                        _leftMotor.run(md, _speed / 4);
                        _rightMotor.run(md, _speed / 4);
                        cout << pulse << " slow: " << slowPulse << endl;
                        isSSlow = true;
                    }
                }
            }
        }
    }
    _leftMotor.stop(false);
    _rightMotor.stop(false);
    return 1;
}

int Car::moveForward(int distance)
{
    int result = 0;
    if(distance > 0)
    {
        int pulse = (distance * 40) / 22;
        result = moveCar(CarDirection::FORWARD, pulse);
    }
    return result;
}

int Car::moveBackward(int distance)
{
    int result = 0;
    if(distance > 0)
    {
        int pulse = (distance * 40) / 22;
        result = moveCar(CarDirection::BACKWARD, pulse);
    }
    return result;
}

/*
void Car::turnCar(CarDirection direction, int degree)
{
    _leftMotor.stop(false);
    _rightMotor.stop(false);
    usleep(10000);
    int pulse = 160;
    int outerPulse;
    _leftEncoder.resetCounter();
    _rightEncoder.resetCounter();
    if(1 == direction) // turn left
    {
        _leftMotor.setPWMFrequency(25);
        _leftMotor.setPWMDutyCycle(15);
        _rightMotor.setPWMFrequency(50);
        _rightMotor.setPWMDutyCycle(127);
    }
    else if(2 == direction)
    {
        _leftMotor.setPWMFrequency(50);
        _leftMotor.setPWMDutyCycle(127);
        _rightMotor.setPWMFrequency(25);
        _rightMotor.setPWMDutyCycle(15);
    }
    _leftMotor.run(MotorDirection::FORWARD);
    _rightMotor.run(MotorDirection::FORWARD);
    do
    {
        if(1 == direction)
        {
            outerPulse = _rightEncoder.getCounter();
        }
        else
        {
            outerPulse = _leftEncoder.getCounter();
        }
        usleep(100);
    }
    while(outerPulse < pulse);
    _leftMotor.stop(false);
    _rightMotor.stop(false);
}


void Car::turnLeft(int degree)
{
    turnCar(1, degree);
}

void Car::turnRight(int degree)
{
    turnCar(2, degree);
}
*/

int Car::rotateLeft(int degree)
{
    int result = 0;
    int pulse = 28;
    result = rotateCar(CarDirection::LEFT, pulse);
    return result;
}

int Car::rotateRight(int degree)
{
    int result = 0;
    int pulse = 28;
    result = rotateCar(CarDirection::RIGHT, pulse);
    return result;
}

void Car::test()
{
    //cout << CarSpeed::FAST < CarSpeed::MEDIUM << endl;
}

void Car::stop()
{
    _leftMotor.stop(true);
    _rightMotor.stop(true);
}

void Car::setSpeed(int level)
{
    if(1 == level)
    {
        _speed = 16;
        _minPing = 15 * 58; // 10cm
    }
    else if(2 == level || 0 == level)
    {
        _speed = 25;
        _minPing = 25 * 58;
    }
    else if(3 == level)
    {
        _speed = 40;
        _minPing = 35 * 58;
    }
    _leftMotor.setPWMDutyCycle(_speed);
    _rightMotor.setPWMDutyCycle(_speed);
}
