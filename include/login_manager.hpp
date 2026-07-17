#pragma once

#include <iostream>
#include <string>
#include <cctype>

class BookingSystem;

class LoginManager
{
public:
    bool loginAsAdmin() const;
    bool isValidPilot(const std::string &pilotId,
                      const BookingSystem &system) const;
    bool loginAsPilot(const std::string &pilotId,
                      const BookingSystem &system) const;

    bool loginAsPassenger(const std::string &passport) const;

    static bool isValidPassport(const std::string &passport);
};

