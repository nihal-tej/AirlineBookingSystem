#ifndef PASSENGER_H
#define PASSENGER_H
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
class Passenger
{
    std::string name;
    std::string passportNumber;
    int age;
    char gender;

public:
    Passenger()
{
    name = "";
    passportNumber = "";
    age = 0;
    gender = 'U';
}
    Passenger(const std::string &n, const std::string &pno, int a, char g)
    {
        if (n.empty())
            throw std::invalid_argument("Passenger name cannot be empty");
        if (pno.empty())
            throw std::invalid_argument("Passport number cannot be empty");
        if (a <= 0)
            throw std::invalid_argument("Invalid age");
        if (g != 'M' && g != 'F')
            throw std::invalid_argument("Invalid Gender");
        this->name = n;
        this->passportNumber = pno;
        this->age = a;
        this->gender = g;
    }
    std::string getName() const { return name; }
    std::string getPassportNumber() const { return passportNumber; }
    int getAge() const { return age; }
    char getGender() const { return gender; }
};

#endif
