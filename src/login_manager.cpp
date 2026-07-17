#include "login_manager.hpp"

#include <iostream>
#include <string>
#include <cctype>

#include "booking_system.hpp"


    bool LoginManager::loginAsAdmin() const
    {
        std::string password;
        std::cout << "Enter Admin Password: ";
        std::cin >> password;
        if (password == "admin@123")
        {
            std::cout << "Admin login successful.\n";
            return true;
        }
        std::cout << "Invalid admin password.\n";
        return false;
    }
    bool LoginManager::isValidPilot(const std::string &pilotId,
                      const BookingSystem &system) const
    {
        return system.checkPilot(pilotId);
    }
    bool LoginManager::loginAsPilot(const std::string &pilotId,
                      const BookingSystem &system) const
    {
        if (!isValidPilot(pilotId, system))
        {
            std::cout << "Invalid Pilot ID.\n";
            return false;
        }
        std::string password;
        std::cout << "Enter Pilot Password: ";
        std::cin >> password;
        if (password == system.getLoginPassword(pilotId))
        {
            std::cout << "Pilot login successful.\n";
            return true;
        }
        std::cout << "Invalid Pilot password.\n";
        return false;
    }

    bool LoginManager::loginAsPassenger(const std::string &passport) const
    {
        if (!isValidPassport(passport))
        {
            std::cout << "Invalid passport number.\n";
            return false;
        }
        std::cout << "Passenger login successful.\n";
        return true;
    }

    bool LoginManager::isValidPassport(const std::string &passport)
    {
        if (passport.size() != 12)
            return false;
        for (const char c : passport)
        {
            if (!std::isdigit(c))
                return false;
        }
        return true;
    }
