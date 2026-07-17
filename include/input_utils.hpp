#pragma once

#include <cctype>
#include <climits>
#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>
void clearInputStream();

int getValidatedInt(const std::string& prompt,int min,int max);

char getValidatedChar(const std::string& prompt,const std::string& validChars);
std::string getValidatedCity(const std::string& prompt,const std::set<std::string>& validCities);
