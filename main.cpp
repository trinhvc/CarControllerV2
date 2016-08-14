#include <iostream>
#include <sstream>
#include <queue>
#include <unistd.h>
//#include "queue.h"
#include "serial.h"
#include "car.h"
//#include "enhan"
//#include "hmc5883l.h"
//#include "encoder.h"
#include "command.h"
//#include "sonar.h"
//#include "constants.h"
#define MAGIC_NUM       22/20 // 22 cm per 20 pulse
using namespace std;

void* driveCar(void* arg);

int main()
{
    if(gpioInitialise() >= 0)
    {
        Serial serial("/dev/ttyAMA0", 9600);
        queue<Command> cmdQueue;
        pthread_t* t1 = NULL;
        string message;
        /*
        while(true)
        {
                Sonar sonar1(TRIGGER1, ECHO1);
                Sonar sonar2(TRIGGER4, ECHO4);
                int ping1 = sonar1.ping(); // delayed 50ms
                int ping2 = sonar2.ping(); // delayed 50ms
                cout << "ping1 " << ping1 << endl;
                cout << "ping2 " << ping2 << endl;
        }
        */
        while(true)
        {
            while(serial.dataAvailable() > 0)
            {
                bool isReady = false;
                char readChar = serial.readChar();
                if(readChar == ']')
                {
                    isReady = true;
                }
                else if(readChar == '[')
                {
                    message.clear();
                }
                else if(readChar == ',')
                {
                    message += ' ';
                }
                else
                {
                    message += readChar;
                }
                // parse instruction from message
                if(isReady)
                {
                    cout << message << endl;
                    int id;
                    string action;
                    int param1;
                    int param2;
                    istringstream ss(message);
                    ss >> id >> action >> param1 >> param2;
                    if(action == "stop")
                    {
                    cout << "stop" << endl;
                        if(t1 != NULL)
                        {
                            cout << "stop thread" << endl;
                            gpioStopThread(t1);
                            t1 = NULL;
                            cout << "thread stop" << endl;
                        }
                        Car::getInstance().stop();
                    }
                    else if(action == "speed")
                    {
                        Car::getInstance().setSpeed(param1);
                    }
                    else
                    {
                        Command cmd(id, action, param1, param2);
                        cmdQueue.push(cmd);
                        if(t1 == NULL)
                        {
                            t1 = gpioStartThread(driveCar, &cmdQueue);
                        }
                    }
                }
            }
            usleep(100); // 0.1ms
        }
//gpioDelay(1000000*10)
//cout << encoder1->getCount() << endl;
//cout << encoder2->getCount() << endl;
        cout << "main thread end" << endl;
    }
    gpioTerminate();
    return 0;
}

void* driveCar(void* arg)
{
    queue<Command>* queuePtr = (queue<Command>*) arg;
    queue<Command>& cmdQueue = *queuePtr;
    //cout << "queue address" << &cmdQueue << endl;
    // moving direction when no distance defined
    Car& car = Car::getInstance();
    int continuous = 0;
    while(true)
    {
        //[id,action,distance,speed]
        if(!cmdQueue.empty())
        {
            Command cmd = cmdQueue.front();
            int speedLevel = cmd.getParam2();
            Car::getInstance().setSpeed(speedLevel);
            string action = cmd.getAction();
            cout << action << " " << speedLevel << endl;
            if("ahead" == action)
            {
                int distance = cmd.getParam1();
                if(distance > 0)
                {
                    Car::getInstance().moveForward(distance);
                    continuous = 0;
                }
                else
                {
                    continuous = 1;
                }
            }
            else if("back" == action)
            {
                cout << "back = action" << endl;
                int distance = cmd.getParam1();
                if(distance > 0)
                {
                    Car::getInstance().moveBackward(distance);
                    continuous = 0;
                }
                else
                {
                    continuous = -1;
                }
            }
            else if("left" == action)
            {
                int distance = cmd.getParam1();
                Car::getInstance().rotateLeft(90);
                if(distance > 0)
                {
                    Car::getInstance().moveForward(distance);
                    continuous = 0;
                }
            }
            else if("right" == action)
            {
                int distance = cmd.getParam1();
                Car::getInstance().rotateRight(90);
                if(distance > 0)
                {
                    Car::getInstance().moveForward(distance);
                    continuous = 0;
                }
            }
            cmdQueue.pop();
        }
        else
        {
            if(continuous != 0)
            {
                int distance  = 10; //
                if(continuous > 0)
                {
                    Car::getInstance().moveForward(distance);
                }
                else
                {
                    Car::getInstance().moveBackward(distance);
                }
            }
        }
        usleep(100);
    }
}
