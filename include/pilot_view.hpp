#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

class BookingSystem;

class PilotView
{
public:
    void viewDetails(const BookingSystem &system,
                     const std::string &pilotId) const;

    void viewSchedule(const BookingSystem &system,
                      const std::string &pilotId) const;
};

