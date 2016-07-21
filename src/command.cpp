#include "command.h"

Command::Command()
{
    _id = -1;
}

Command::Command(int id, string action, int distance, int speed)
{
    _id = id;
    _action = action;
    _distance = distance;
    _speed = speed;
}

int Command::getID()
{
    return _id;
}

void Command::setID(int id)
{
    _id = id;
}

string Command::getAction()
{
    return _action;
}

void Command::setAction(string action)
{
    _action = action;
}

int Command::getDistance()
{
    return _distance;
}

void Command::setDistance(int distance)
{
    _distance = distance;
}

int Command::getSpeed()
{
    return _speed;
}

void Command::setSpeed(int speed)
{
    _speed = speed;
}
