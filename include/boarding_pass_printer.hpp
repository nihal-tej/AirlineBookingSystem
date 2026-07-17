#pragma once

#include <iostream>
#include <string>
class Passenger;
class Flight;

class BoardingPassPrinter
{
public:
    void generate(const Passenger &p, const Flight &f, int row, int col) const;
};