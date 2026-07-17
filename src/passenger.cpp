#include "passenger.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

    Passenger::Passenger()
{
    name = "";
    passportNumber = "";
    age = 0;
    gender = 'U';
}
    Passenger::Passenger(const std::string &n, const std::string &pno, int a, char g)
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
    std::string Passenger::getName() const { return name; }
    std::string Passenger::getPassportNumber() const { return passportNumber; }
    int Passenger::getAge() const { return age; }
    char Passenger::getGender() const { return gender; }

