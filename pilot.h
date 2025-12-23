#ifndef PILOT_H
#define PILOT_H

#include <string>
using namespace std;

class Pilot
{
    string name, passportNumber, id;
    int age;
    char gender;
    string password;

public:
    Pilot(const string &i,const string &n,const string &pno, int a, char g,const string &pa)
    {
        this->name = n;
        this->id = i;
        this->passportNumber = pno;
        this->age = a;
        this->gender = g;
        password = pa;
    }
    string getpilotname()const { return name; }
    string getpilotpassportnumber()const { return passportNumber; }
    int getpilotage()const { return age; }
    char getpilotgender()const { return gender; }
    string getpilotid()const
    {
        return id;
    }
    string getpilotpassword()const
    {
        return password;
    }
};

#endif
