#ifndef COMMAND_H
#define COMMAND_H

#include <string>
using namespace std;

class Command
{
private:
    int _id;
    string _action;
    int _param1;
    int _param2;
public:
    Command();
    Command(int id, string action, int param1, int param2);
    int getID();
    void setID(int id);
    string getAction();
    void setAction(string action);
    int getParam1();
    void setParam1(int value);
    int getParam2();
    void setParam2(int value);
};

#endif // COMMAND_H
