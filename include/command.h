#ifndef COMMAND_H
#define COMMAND_H

#include <string>
using namespace std;

class Command
{
private:
    int _id;
    string _action;
    int _distance;
    int _speed;
public:
    Command();
    Command(int id, string action, int distance, int speed);
    int getID();
    void setID(int id);
    string getAction();
    void setAction(string action);
    int getDistance();
    void setDistance(int distance);
    int getSpeed();
    void setSpeed(int speed);
};

#endif // COMMAND_H
