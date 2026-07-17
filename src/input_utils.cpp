#include "input_utils.hpp"

#include <cctype>
#include <climits>
#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>
void clearInputStream()
{
    std::cin.clear();
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
}

int getValidatedInt(
    const std::string& prompt,
    int min,
    int max)
{
    int value;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value < min || value > max)
        {
            std::cout << "Invalid input.\n";
            clearInputStream();
        }
        else
        {
            clearInputStream();
            return value;
        }
    }
}

char getValidatedChar(
    const std::string& prompt,
    const std::string& validChars)
{
    char ch;

    while (true)
    {
        std::cout << prompt;
        std::cin >> ch;

        ch = std::toupper(static_cast<unsigned char>(ch));

        if (validChars.find(ch) != std::string::npos)
        {
            clearInputStream();
            return ch;
        }

        std::cout << "Invalid input.\n";
        clearInputStream();
    }
}
std::string getValidatedCity(
    const std::string& prompt,
    const std::set<std::string>& validCities)
{
    std::string ch;
    while (true)
    {
        std::cout << prompt;
        std::cin >> ch;

        std::transform(ch.begin(), ch.end(), ch.begin(),
               [](unsigned char c)
               {
                   return std::toupper(c);
               });
        if (validCities.find(ch) !=validCities.end())
        {
            clearInputStream();
            return ch;
        }

        std::cout << "Invalid input.\n";
        clearInputStream();
    }
}