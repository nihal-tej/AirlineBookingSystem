#pragma once
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
    Passenger();
    Passenger(const std::string &n, const std::string &pno, int a, char g);
    std::string getName() const ;
    std::string getPassportNumber() const ;
    int getAge() const ;
    char getGender() const ;
};


