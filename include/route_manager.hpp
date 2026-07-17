#pragma once
class BookingSystem;
#include "flight.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class RouteManager
{
public:
    enum class TimeSlot
    {
        Morning,   // 05:00 - 11:59
        Afternoon, // 12:00 - 17:59
        Evening    // 18:00 - 23:59
    };

    static std::string normalize(const std::string &city) ;
    std::vector<Flight> getFlightOptionsByTime(const std::string &src, const std::string &dst, TimeSlot slot, const std::string &date, const BookingSystem &system) const;
    
};

