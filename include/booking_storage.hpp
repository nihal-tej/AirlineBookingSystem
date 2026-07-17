#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <utility>

class Flight;
class Passenger;
class Pilot;

struct BookingRecord
{
    std::string flightId;
    std::string bookingTime;
    std::string status;
};
class BookingStorage
{
public:
    static void saveHistory(const std::map<std::string, std::vector<BookingRecord>> &passengerHistory,const std::string &file) ;
    
    static void loadHistory(std::map<std::string, std::vector<BookingRecord> > &passengerHistory,
                            const std::string &file) ;
    
    static void saveBookings(const std::map<std::string,std::vector<Passenger> > &bookings,
        const std::unordered_map<std::string,std::vector<std::pair<std::string,
        std::pair<int, int> > > > &passengerSeatMap,const std::string &file) ;
    
    static void loadBookings(std::map<std::string, std::vector<Passenger> > &bookings, std::map<std::string,
         std::unordered_set<std::string> > &bookedPassports, std::unordered_map<std::string, 
         std::vector<std::pair<std::string, std::pair<int,int>>>> &passengerSeatMap, 
         std::unordered_map<std::string, Flight> &flights,const std::string &file) ;


    static void saveFlights(const std::unordered_map<std::string, Flight> &flights, const std::string &file);

    static void loadFlights(std::unordered_map<std::string, Flight> &flights,
        std::unordered_map<std::string,std::vector<std::string> > &pilotFlights,
        std::unordered_map<std::string,std::vector<std::pair<std::string,std::tuple<std::string,
        std::string,std::string,std::string>>>> &pilotData,const std::string &file);

    static void savePilots(
        const std::unordered_map<std::string,Pilot> &pilots, const std::string &file);
    
    static void loadPilots(std::unordered_map<std::string, Pilot> &pilots,
        std::unordered_set<std::string> &pilotIds,const std::string &file);
    
};

