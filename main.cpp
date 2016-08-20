#include <iostream>
#include <sstream>
#include <queue>
#include <unistd.h>
//#include "queue.h"
#include "serial.h"
#include "car.h"
//#include "enhan"
#include "led.h"
#include "encoder.h"
#include "command.h"
//#include "sonar.h"
//#include "constants.h"
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
        Led::getInstance().setReady(1);
        Car::getInstance().test();

        /*
        Sonar sonar1(TRIGGER1, ECHO1);
        Sonar sonar4(TRIGGER4, ECHO4);
        Sonar sonar3(TRIGGER3, ECHO3);
        Sonar sonar2(TRIGGER2, ECHO2);
        while(true)
        {
            int ping1 = sonar1.ping(); // delayed 50ms
            int ping2 = sonar2.ping(); // delayed 50ms
            int ping4 = sonar4.ping(); // delayed 50ms
            int ping3 = sonar3.ping(); // delayed 50ms
            //cout << ping1/58 << " vs " << ping4/58 << endl;
            cout << ping2/58 << " vs " << ping3/58 << endl;
        }
        */
        while(true)
        {
            while(serial.dataAvailable() > 0)
            {
                Led::getInstance().setData(1);
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
                            gpioStopThread(t1);
                            t1 = NULL;
                        }
                        Car::getInstance().stop();
                    }
                    else if(action == "speed")
                    {
                        int speedlv = param1;
                        Car::getInstance().setSpeed(speedlv);
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
            Led::getInstance().setData(0);
            usleep(100); // 0.1ms
        }
        cout << "main thread end" << endl;
    }
    gpioTerminate();
    return 0;
}

void* driveCar(void* arg)
{
    queue<Command>* queuePtr = (queue<Command>*) arg;
    queue<Command>& cmdQueue = *queuePtr;
    Car& car = Car::getInstance();

    //cout << "queue address" << &cmdQueue << endl;
    // moving direction when no distance defined

    int continuous = 0;
    while(true)
    {
        //[id,action,distance,speed]
        if(!cmdQueue.empty())
        {
            Led::getInstance().setSonar1(0);
            Led::getInstance().setSonar2(0);
            Led::getInstance().setSonar3(0);
            Led::getInstance().setSonar4(0);

            Command cmd = cmdQueue.front();

            string action = cmd.getAction();
            cout << action << endl;
            if("ahead" == action)
            {
                int speedLevel = cmd.getParam2();
                car.setSpeed(speedLevel);
                int distance = cmd.getParam1();
                if(distance > 0)
                {
                    car.moveForward(distance);
                    car.stop();
                    car.setSpeed(0); // default speed
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
                int speedLevel = cmd.getParam2();
                car.setSpeed(speedLevel);
                int distance = cmd.getParam1();
                if(distance > 0)
                {
                    car.moveBackward(distance);
                    car.stop();
                    car.setSpeed(0); // default speed
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
                car.rotateLeft(90);
                if(distance > 0)
                {
                    car.moveForward(distance);
                    car.stop();
                    car.setSpeed(0); // default speed
                    continuous = 0;
                }
            }
            else if("right" == action)
            {
                int distance = cmd.getParam1();
                car.rotateRight(90);
                if(distance > 0)
                {
                    car.moveForward(distance);
                    car.stop();
                    car.setSpeed(0); // default speed
                    continuous = 0;
                }
            }
            cmdQueue.pop();
        }
        else
        {
            if(continuous != 0)
            {
                int distance  = 10; // 10cm
                if(continuous > 0)
                {
                    int result = car.moveForward(distance);
                    if(result != 1)
                    {
                        continuous = 0;
                        car.setSpeed(0); // default speed
                    }
                }
                else
                {
                    int result = car.moveBackward(distance);
                    if(result != 1)
                    {
                        continuous = 0;
                        car.setSpeed(0); // default speed
                    }
                }
            }
        }
        usleep(100);
    }
}
