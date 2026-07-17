#include "pilot.hpp"

#include <string>
#include <stdexcept>


Pilot::Pilot()
{
    name = "";
    passportNumber = "";
    id = "";
    password = "";
    age = 0;
    gender = 'U';
}
    Pilot::Pilot(const std::string &i, const std::string &n, const std::string &pno, int a, char g, const std::string &pa)
    {
        if (i.empty())
            throw std::invalid_argument("Pilot Id cannot be empty");
        if (n.empty())
            throw std::invalid_argument("Passenger name cannot be empty");
        if (pno.empty())
            throw std::invalid_argument("Passport number cannot be empty");
        if (a <= 0)
            throw std::invalid_argument("Invalid age");
        if (g != 'M' && g != 'F')
            throw std::invalid_argument("Invalid Gender");
        if (pa.empty())
            throw std::invalid_argument("Password cannot be empty");
        this->name = n;
        this->id = i;
        this->passportNumber = pno;
        this->age = a;
        this->gender = g;
        password = pa;
    }
    std::string Pilot::getPilotName() const { return name; }
    std::string Pilot::getPassportNumber() const { return passportNumber; }
    int Pilot::getAge() const { return age; }
    char Pilot::getGender() const { return gender; }
    std::string Pilot::getPilotId() const
    {
        return id;
    }
    std::string Pilot::getPassword() const
    {
        return password;
    }
