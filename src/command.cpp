#include "command.h"

Command::Command()
{
    _id = -1;
}

Command::Command(int id, string action, int param1, int param2)
{
    _id = id;
    _action = action;
    _param1 = param1;
    _param2 = param2;
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

int Command::getParam1()
{
    return _param1;
}

void Command::setParam1(int value)
{
    _param1 = value;
}

int Command::getParam2()
{
    return _param2;
}

void Command::setParam2(int value)
{
    _param2 = value;
}
