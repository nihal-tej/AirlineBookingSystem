#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class TimeUtils
{
public:
    static std::string getCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm *localTime =std::localtime(&now);
        std::stringstream ss;
        ss << 1900 + localTime->tm_year<< "-"<< std::setw(2)
           << std::setfill('0')<< 1 + localTime->tm_mon<< "-"
           << std::setw(2)<< std::setfill('0')<< localTime->tm_mday
           << "___"<< std::setw(2)<< std::setfill('0') << localTime->tm_hour
           << ":"<< std::setw(2)<< std::setfill('0')<< localTime->tm_min
           << ":"<< std::setw(2)<< std::setfill('0')<< localTime->tm_sec;
        return ss.str();
    }
};

#endif