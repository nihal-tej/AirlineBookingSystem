#ifndef ROUTE_MANAGER_H
#define ROUTE_MANAGER_H
#include "booking_system.h"
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

    static std::string normalize(const std::string &city) 
    {
        std::string s = city;
        std::transform(s.begin(), s.end(), s.begin(),[](unsigned char c)
                  {
                      return std::tolower(c);
                  });
        return s;
    }
    std::vector<Flight> getFlightOptionsByTime(const std::string &src, const std::string &dst, TimeSlot slot, const std::string &date, const BookingSystem &system) const
    {
        std::vector<Flight> result;
        //  normalized strings to lower so that no case sensitive
        const std::string normalized_src = normalize(src);
        const std::string normalized_dst = normalize(dst);

        std::string low, high;

        if (slot == TimeSlot::Morning)
        {
            low = "05:00";
            high = "11:59";
        }
        else if (slot == TimeSlot::Afternoon)
        {
            low = "12:00";
            high = "17:59";
        }
        else
        {
            low = "18:00";
            high = "23:59";
        }
        for (const auto &x : system.getFlights())
        {
            const auto& flight = x.second;
            // The time and date check
            if (flight.getDate() == date && flight.getTime() >= low && flight.getTime() <= high)
            {
                if (normalize(flight.getSource()) == normalized_src &&
                    normalize(flight.getDestination()) == normalized_dst)
                {
                    result.push_back(flight);
                }
            }
        }

        return result;
    }
};

#endif