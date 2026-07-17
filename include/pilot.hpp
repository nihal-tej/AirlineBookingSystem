#pragma once

#include <string>
#include <stdexcept>

class Pilot
{
    std::string name, passportNumber, id;
    int age;
    char gender;
    std::string password;

public:
Pilot();

    Pilot(const std::string &i, const std::string &n, const std::string &pno, int a, char g, const std::string &pa);
    std::string getPilotName() const ;
    std::string getPassportNumber() const ;
    int getAge() const ;
    char getGender() const ;
    std::string getPilotId() const;
    std::string getPassword() const;
};

