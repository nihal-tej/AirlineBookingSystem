#include "booking_system.hpp"
#include "flight.hpp"
#include "passenger.hpp"
#include "pilot.hpp"
#include "time_utils.hpp"

#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <tuple>
#include <utility>

std::unordered_map<std::string, Pilot> &BookingSystem::getPilotsall()
{
    return pilots;
}
std::unordered_set<std::string> &BookingSystem::getAllPilotIds()
{
    return pilotIds;
}
std::unordered_map<std::string, Flight> &BookingSystem::getAllFlights()
{
    return flights;
}
std::unordered_map<std::string, std::vector<std::string>> &BookingSystem::getPilotFlights()
{
    return pilotFlights;
}
std::unordered_map<std::string, std::vector<std::pair<std::string,
                                                      std::tuple<std::string, std::string, std::string, std::string>>>> &
BookingSystem::getPilotData()
{
    return pilotData;
}
std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<int, int>>>> &BookingSystem::getPassengerSeatMapAll()
{
    return passengerSeatMap;
}
std::map<std::string, std::unordered_set<std::string>> &BookingSystem::getBookedPassports()
{
    return bookedPassports;
}
const std::map<std::string, std::vector<BookingRecord>> &BookingSystem::getPassengerHistory() const
{
    return passengerHistory;
}
std::map<std::string, std::vector<BookingRecord>> &BookingSystem::getPassengerHistory()
{
    return passengerHistory;
}
std::vector<std::pair<std::string, std::tuple<std::string, std::string, std::string, std::string>>> BookingSystem::getPilotSchedule(const std::string &pilotId) const
{
    if (pilotData.count(pilotId))
        return pilotData.at(pilotId);

    return {};
}
std::map<std::string, std::vector<Passenger>> &
BookingSystem::getBookings()
{
    return bookings;
}

const std::map<std::string, std::vector<Passenger>> &
BookingSystem::getBookings() const
{
    return bookings;
}
const std::unordered_map<std::string, Flight> &BookingSystem::getFlights() const
{
    return flights;
}
std::unordered_map<std::string, Flight> &BookingSystem::getFlights()
{
    return flights;
}
const std::unordered_map<std::string, Pilot> &BookingSystem::getPilots() const
{
    return pilots;
}
std::unordered_map<std::string, Pilot> &BookingSystem::getPilots()
{
    return pilots;
}

std::string BookingSystem::getLoginPassword(const std::string &pilotId) const
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

bool BookingSystem::checkPilot(const std::string &pilotId) const
{
    return pilotIds.find(pilotId) != pilotIds.end();
}

Flight *BookingSystem::findFlight(const std::string &flightId)
{
    if (flights.count(flightId))
        return &flights[flightId];
    return nullptr;
}

Passenger *BookingSystem::findPassenger(const std::string &flightId, const std::string &passport)
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

bool BookingSystem::addPilot(const Pilot &pilot)
{
    const std::string pilotId = pilot.getPilotId();

    if (pilots.count(pilotId))
        return false;
    pilots[pilotId] = pilot;
    pilotIds.insert(pilotId);
    return true;
}

bool BookingSystem::removePilot(const std::string &pilotId)
{
    if (!pilots.count(pilotId))
        return false;
    pilots.erase(pilotId);
    pilotIds.erase(pilotId);
    return true;
}

bool BookingSystem::addFlight(const Flight &flight)
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

bool BookingSystem::removeFlight(const std::string &flightId)
{
    if (!flights.count(flightId))
        return false;
    flights.erase(flightId);
    return true;
}

bool BookingSystem::bookTicket(const std::string &flightId, const Passenger &passenger, int row, int col)
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

void BookingSystem::cancelTicket(
    const std::string &flightId,
    const std::string &passport)
{
    Flight *target = findFlight(flightId);

    if (!target)
    {
        std::cout << "Failed: Flight not found\n";
        return;
    }

    if (bookings.find(flightId) == bookings.end())
    {
        std::cout << "Failed: Booking not found\n";
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
    else
        {
            std::cout << "Failed: Seat not found\n";
            return;
        }
    
    std::cout<<"Cancellation successfull\n";
}

std::pair<int, int> BookingSystem::getPassengerSeat(const std::string &flightId, const std::string &passport) const
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

const std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<int, int>>>> BookingSystem::getPassengerSeatMap() const
{
    return passengerSeatMap;
}
