#ifndef PILOT_H
#define PILOT_H

#include <string>
#include <stdexcept>

class Pilot
{
    std::string name, passportNumber, id;
    int age;
    char gender;
    std::string password;

public:
Pilot()
{
    name = "";
    passportNumber = "";
    id = "";
    password = "";
    age = 0;
    gender = 'U';
}
    Pilot(const std::string &i, const std::string &n, const std::string &pno, int a, char g, const std::string &pa)
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
    std::string getPilotName() const { return name; }
    std::string getPassportNumber() const { return passportNumber; }
    int getAge() const { return age; }
    char getGender() const { return gender; }
    std::string getPilotId() const
    {
        return id;
    }
    std::string getPassword() const
    {
        return password;
    }
};

#endif
