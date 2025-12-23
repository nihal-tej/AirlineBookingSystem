#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger {
    string name, passportNumber;
    int age;
    char gender;

public:
    
    Passenger(string &n, string &pno, int &a, char &g)
    {
        this->name = n;
        this->passportNumber = pno;
        this->age = a;
        this->gender = g;
    }
    string getName() const { return name; }
    string getPassportNumber() const { return passportNumber; }
    int getAge() const { return age; }
    char getGender() const { return gender; }
};

#endif
