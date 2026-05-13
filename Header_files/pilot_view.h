#ifndef PILOT_VIEW_H
#define PILOT_VIEW_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

#include "booking_system.h"

class PilotView
{
public:
    void viewDetails(const BookingSystem &system,
                     const std::string &pilotId) const
    {
        const auto &pilots = system.getPilots();

        if (pilots.count(pilotId))
        {
            const auto &pilot = pilots.at(pilotId);
            std::cout << "\n========== PILOT DETAILS ==========\n";
            std::cout << "Pilot Name: "<< pilot.getPilotName()<< "\n";
            std::cout << "Passport Number: "<< pilot.getPassportNumber()<< "\n";
            std::cout << "Age: "<< pilot.getAge()<< "\n";
            std::cout << "Gender: "<< pilot.getGender()<< "\n";
            std::cout << "---------------------------------------\n";
        }
        else
        {
            std::cout << "Pilot not found with Pilot ID: "<< pilotId<< "\n";
        }
    }

    void viewSchedule(const BookingSystem &system,
                      const std::string &pilotId) const
    {
        const auto &pilotSchedules =system.getPilotSchedule(pilotId);
        if (pilotSchedules.empty())
        {
            std::cout << "No flights assigned.\n";
            return;
        }
        std::string date;
        std::cout << "Enter date to view schedule: ";
        std::cin >> date;
        std::cout << "\nDate: " << date<< "\n";
        int foundCount = 0;
        for (const auto &flightEntry : pilotSchedules)
        {
            if (flightEntry.first != date)
                continue;
            const auto &flightInfo =flightEntry.second;
            foundCount++;
            std::cout << "\nFlight ID: "<< std::get<2>(flightInfo)<< "\n";
            std::cout << "Route: "<< std::get<0>(flightInfo)<< " -> "<< std::get<1>(flightInfo)<< "\n";
            std::cout << "Time: "<< std::get<3>(flightInfo)<< "\n";
            std::cout << "---------------------------------------\n";
        }

        if (foundCount == 0)
        {
            std::cout << "No schedule found on this date.\n";
        }
    }
};

#endif