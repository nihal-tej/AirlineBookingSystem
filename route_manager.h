#ifndef ROUTE_MANAGER_H
#define ROUTE_MANAGER_H
#include "booking_system.h"
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

class RouteManager
{
public:
    enum TimeSlot
    {
        Morning,    // 05:00 - 11:59
        Afternoon,  // 12:00 - 17:59
        Evening     // 18:00 - 23:59
    };

    static string normalize(const string &city)
    {
        string s = city;
        transform(s.begin(), s.end(), s.begin(),
                  [](unsigned char c)
                  {
                      return tolower(c);
                  });
        return s;
    }
    vector<Flight> getFlightOptionsByTime(const string &src, const string &dst, TimeSlot slot, const string &date, const BookingSystem &system)
    {
        vector<Flight> result;
        
        // Use normalized strings 
        const string normalized_src = normalize(src);
        const string normalized_dst = normalize(dst);

        string low, high;

        if (slot == Morning)
        {
            low = "05:00";
            high = "11:59";
        }
        else if (slot == Afternoon)
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
            // The time and date check is correct as is:
            if (x.getdate() == date && x.getTime() >= low && x.getTime() <= high)
            {
                if (normalize(x.getSource()) == normalized_src &&
                    normalize(x.getDestination()) == normalized_dst)
                {
                    result.push_back(x);
                }
            }
        }

        return result;
    }
};

#endif