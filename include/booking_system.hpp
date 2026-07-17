#pragma once

#include "flight.hpp"
#include "passenger.hpp"
#include "pilot.hpp"
class TimeUtils;
#include "pilot.hpp"
#include "booking_storage.hpp"
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <tuple>
#include <utility>

class BookingSystem
{
private:
    std::unordered_map<std::string, Flight> flights;
    std::map<std::string, std::vector<Passenger>> bookings;
    std::map<std::string, std::unordered_set<std::string>> bookedPassports;
    std::map<std::string, std::vector<BookingRecord>> passengerHistory;
    std::unordered_map<std::string, Pilot> pilots;
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<int, int>>>> passengerSeatMap;
    std::unordered_map<std::string, std::vector<std::pair<std::string,
                                                          std::tuple<std::string, std::string, std::string, std::string>>>>
        pilotData;
    std::unordered_map<std::string, std::vector<std::string>> pilotFlights;
    std::unordered_set<std::string> pilotIds;

public:
    std::unordered_map<std::string, Pilot> &getPilotsall() ;

    std::unordered_set<std::string> &getAllPilotIds() ;
    
    std::unordered_map<std::string, Flight> &getAllFlights() ;
    std::unordered_map<std::string, std::vector<std::string>> &getPilotFlights() ;

    std::unordered_map<std::string, std::vector<std::pair<std::string,
                                                          std::tuple<std::string, std::string, std::string, std::string>>>> &
    getPilotData() ;
    
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<int, int>>>> &getPassengerSeatMapAll();

    std::map<std::string, std::unordered_set<std::string>> &getBookedPassports();
    
    std::map<std::string, std::vector<BookingRecord>>& getPassengerHistory();

const std::map<std::string, std::vector<BookingRecord>>&getPassengerHistory() const;
   
    std::vector<std::pair<std::string, std::tuple<std::string, std::string, std::string, std::string>>> getPilotSchedule(const std::string &pilotId) const;
    
    std::map<std::string, std::vector<Passenger>>& getBookings();
const std::map<std::string, std::vector<Passenger>>& getBookings() const;

std::unordered_map<std::string, Flight>& getFlights();
const std::unordered_map<std::string, Flight>& getFlights() const;

std::unordered_map<std::string, Pilot>& getPilots();
const std::unordered_map<std::string, Pilot>& getPilots() const;

    std::string getLoginPassword(const std::string &pilotId) const;
    

    bool checkPilot(const std::string &pilotId) const;

    Flight *findFlight(const std::string &flightId);

    Passenger *findPassenger(const std::string &flightId, const std::string &passport) ;
    

    bool addPilot(const Pilot &pilot) ;

    bool removePilot(const std::string &pilotId) ;

    bool addFlight(const Flight &flight) ;

    bool removeFlight(const std::string &flightId) ;

    bool bookTicket(const std::string &flightId, const Passenger &passenger, int row, int col) ;
 
    void cancelTicket(const std::string &flightId,const std::string &passport) ;
   
    std::pair<int, int> getPassengerSeat(const std::string &flightId, const std::string &passport)const;
   
  
    const std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<int, int>>>> getPassengerSeatMap() const;
};

