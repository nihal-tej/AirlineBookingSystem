#ifndef BOOKING_SYSTEM_H
#define BOOKING_SYSTEM_H

#include "flight.h"
#include "passenger.h"
#include "pilot.h"
#include "time_utils.h"

#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <tuple>
#include <utility>

struct BookingRecord
{
    std::string flightId;
    std::string bookingTime;
    std::string status;
};

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
    std::unordered_map<std::string, Pilot> &getPilotsall()
    {
        return pilots;
    }
    std::unordered_set<std::string> &getAllPilotIds()
    {
        return pilotIds;
    }
    std::unordered_map<std::string, Flight> &getAllFlights()
    {
        return flights;
    }
    std::unordered_map<std::string, std::vector<std::string>> &getPilotFlights()
    {
        return pilotFlights;
    }
    std::unordered_map<std::string, std::vector<std::pair<std::string,
                                                          std::tuple<std::string, std::string, std::string, std::string>>>> &
    getPilotData()
    {
        return pilotData;
    }
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<int, int>>>> &getPassengerSeatMapAll()
    {
        return passengerSeatMap;
    }
    std::map<std::string, std::unordered_set<std::string>> &getBookedPassports()
    {
        return bookedPassports;
    }
    std::map<std::string, std::vector<BookingRecord>> &getPassengerHistory()
    {
        return passengerHistory;
    }
    std::vector<std::pair<std::string, std::tuple<std::string, std::string, std::string, std::string>>> getPilotSchedule(const std::string &pilotId) const
    {
        if (pilotData.count(pilotId))
            return pilotData.at(pilotId);

        return {};
    }
    std::map<std::string, std::vector<Passenger>> &getBookings()
    {
        return bookings;
    }

    std::string getLoginPassword(const std::string &pilotId) const
    {
        if (pilotIds.find(pilotId) == pilotIds.end())
        {
            return "";
        }

        for (const auto &pilotEntry : pilots)
        {
            if (pilotEntry.second.getPilotId() == pilotId)
            {
                return pilotEntry.second.getPassword();
            }
        }

        return "";
    }

    bool checkPilot(const std::string &pilotId) const
    {
        return pilotIds.find(pilotId) != pilotIds.end();
    }

    Flight *findFlight(const std::string &flightId)
    {
        if (flights.count(flightId))
            return &flights[flightId];
        return nullptr;
    }

    Passenger *findPassenger(const std::string &flightId, const std::string &passport)
    {
        auto &passengerList = bookings[flightId];

        for (auto &passenger : passengerList)
        {
            if (passenger.getPassportNumber() == passport)
            {
                return &passenger;
            }
        }

        return nullptr;
    }

    bool addPilot(const Pilot &pilot)
    {
        const std::string pilotId = pilot.getPilotId();

        if (pilots.count(pilotId))
            return false;
        pilots[pilotId] = pilot;
        pilotIds.insert(pilotId);
        return true;
    }

    bool removePilot(const std::string &pilotId)
    {
        if (!pilots.count(pilotId))
            return false;
        pilots.erase(pilotId);
        pilotIds.erase(pilotId);
        return true;
    }

    bool addFlight(const Flight &flight)
    {
        const std::string flightId = flight.getFlightId();
        if (flights.count(flightId))
            return false;
        flights[flightId] = flight;
        const std::string pilotId = flight.getPilotId();
        pilotFlights[pilotId].push_back(flightId);
        pilotData[pilotId].push_back({flight.getDate(), {flight.getSource(), flight.getDestination(), flightId, flight.getTime()}});
        return true;
    }

    bool removeFlight(const std::string &flightId)
    {
        if (!flights.count(flightId))
            return false;
        flights.erase(flightId);
        return true;
    }

    bool bookTicket(const std::string &flightId, const Passenger &passenger, int row, int col)
    {
        Flight *target = findFlight(flightId);

        if (!target)
            return false;
        if (!target->isSeatAvailable(row, col))
        {
            return false;
        }
        target->reserveSeat(row, col, passenger.getPassportNumber());
        const std::string passport = passenger.getPassportNumber();
        bookings[flightId].push_back(passenger);
        bookedPassports[flightId].insert(passport);
        passengerSeatMap[flightId].push_back({passport, {row, col}});
        passengerHistory[passport].push_back({flightId, TimeUtils::getCurrentTime(), "booked"});
        return true;
    }

    void cancelTicket(
        const std::string &flightId,
        const std::string &passport)
    {
        Flight *target = findFlight(flightId);

        if (!target)
            return;

        if (bookings.find(flightId) == bookings.end())
        {
            return;
        }

        std::pair<int, int> seat = getPassengerSeat(flightId, passport);

        auto &passengerList = bookings[flightId];

        for (int i = 0; i < passengerList.size(); i++)
        {
            if (passengerList[i].getPassportNumber() == passport)
            {
                passengerList.erase(passengerList.begin() + i);
                bookedPassports[flightId].erase(passport);
                passengerHistory[passport].push_back({flightId, TimeUtils::getCurrentTime(), "cancelled"});
                break;
            }
        }

        if (seat.first != -1)
        {
            target->freeSeat(seat.first, seat.second);
            auto &seatList = passengerSeatMap.at(flightId);
            for (auto it = seatList.begin(); it != seatList.end(); ++it)
            {
                if (it->first == passport)
                {
                    seatList.erase(it);
                    break;
                }
            }
        }
    }

    std::pair<int, int> getPassengerSeat(const std::string &flightId, const std::string &passport)
    {
        auto it = passengerSeatMap.find(flightId);
        if (it == passengerSeatMap.end())
        {
            return {-1, -1};
        }
        for (const auto &seat : it->second)
        {
            if (seat.first == passport)
                return seat.second;
        }
        return {-1, -1};
    }

    const std::map<std::string, std::vector<Passenger>> &getBookings() const
    {
        return bookings;
    }
    const std::unordered_map<std::string, Flight> &getFlights() const
    {
        return flights;
    }
    const std::unordered_map<std::string, Pilot> &getPilots() const
    {
        return pilots;
    }
  
    const std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<int, int>>>> getPassengerSeatMap() const
    {
        return passengerSeatMap;
    }
};

#endif