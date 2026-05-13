#ifndef BOOKING_STORAGE_H
#define BOOKING_STORAGE_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <utility>

#include "flight.h"
#include "passenger.h"
#include "pilot.h"
struct BookingRecord
{
    std::string flightId;
    std::string bookingTime;
    std::string status;
};
class BookingStorage
{
public:
    static void saveHistory(const std::map<std::string, std::vector<BookingRecord>> &passengerHistory,const std::string &file)
    {
        std::ofstream out(file);
        for (const auto &historyEntry : passengerHistory)
        {
            for (const auto &record : historyEntry.second)
            {
                out << historyEntry.first << " " << record.flightId << 
                " " << record.bookingTime << " "<< record.status << "\n";
            }
        }
    }

    static void loadHistory(std::map<std::string, std::vector<BookingRecord> > &passengerHistory,
                            const std::string &file)
    {
        std::ifstream in(file);
        if (!in)
        {
            std::cout << "Passenger history file not found. Starting fresh.\n";
            return;
        }
        passengerHistory.clear();
        std::string passport;
        std::string flightId;
        std::string bookingTime;
        std::string status;
        while (in >> passport >> flightId >> bookingTime >> status)
        {
            passengerHistory[passport].push_back({flightId, bookingTime, status});
        }
        in.close();
    }
    static void saveBookings(const std::map<std::string,std::vector<Passenger> > &bookings,
        const std::unordered_map<std::string,std::vector<std::pair<std::string,
        std::pair<int, int> > > > &passengerSeatMap,const std::string &file)
    {
        std::ofstream out(file);
        for (const auto &bookingEntry : bookings)
        {
            const std::string &flightId = bookingEntry.first;
            for (const auto &passenger :bookingEntry.second)
            {
                int row = -1;
                int col = -1;
                if (passengerSeatMap.count(flightId))
                {
                    const auto &seatList = passengerSeatMap.at(flightId);
                    for (const auto &seatEntry : seatList)
                    {
                        if (seatEntry.first == passenger.getPassportNumber())
                        {
                            row = seatEntry.second.first;
                            col = seatEntry.second.second;
                            break;
                        }
                    }
                }
                out << flightId << " " << passenger.getName() << " " << passenger.getPassportNumber() << " "
                    << passenger.getGender() << " " << passenger.getAge() << " " << row << " " << col << "\n";
            }
        }
    }

    static void loadBookings(std::map<std::string, std::vector<Passenger> > &bookings, std::map<std::string,
         std::unordered_set<std::string> > &bookedPassports, std::unordered_map<std::string, 
         std::vector<std::pair<std::string, std::pair<int,int>>>> &passengerSeatMap, 
         std::unordered_map<std::string, Flight> &flights,const std::string &file)
    {
        std::ifstream in(file);
        std::string flightId;
        std::string name;
        std::string passport;
        int age;
        int row;
        int col;
        char gender;
        while (in >> flightId >> name >> passport >> gender >> age >> row >> col)
        {
            Passenger passenger(name, passport, age, gender);
            bookings[flightId].push_back(passenger);
            bookedPassports[flightId].insert(passport);
            Flight *target = nullptr;
            if (flights.count(flightId))
            {
                target = &flights[flightId];
            }
            if (target)
            {
                target->reserveSeat(row, col, passport, true);
                passengerSeatMap[flightId].push_back({passport, {row, col}});
            }
        }
        in.close();
    }

    static void saveFlights(const std::unordered_map<std::string, Flight> &flights, const std::string &file)
    {
        std::ofstream out(file);
        for (const auto &flightEntry : flights)
        {
            const auto &flight = flightEntry.second;
            out << flight.getFlightId() << " "
                << flight.getPilotId() << " "
                << flight.getSource() << " "
                << flight.getDestination() << " "
                << flight.getDate() << " "
                << flight.getTime() << " "
                << flight.getTotalRows() << " "
                << flight.getTotalCols() << " "
                << flight.getBaseFare() << " "
                << flight.getRevenue() << "\n";
        }
        out.close();
    }

    static void loadFlights(std::unordered_map<std::string, Flight> &flights,
        std::unordered_map<std::string,std::vector<std::string> > &pilotFlights,
        std::unordered_map<std::string,std::vector<std::pair<std::string,std::tuple<std::string,
        std::string,std::string,std::string>>>> &pilotData,const std::string &file)
    {
        std::ifstream in(file);
        std::string id;
        std::string source;
        std::string destination;
        std::string date;
        std::string time;
        std::string pilotId;
        int rows;
        int cols;
        int baseFare;
        double revenue;

        while (in >> id >> pilotId >> source >> destination >> date >> time >> rows >> cols >> baseFare >> revenue)
        {
            Flight flight(id, pilotId, source, destination,date,time,rows, cols,baseFare, revenue);

            flights[id] = flight;
            pilotFlights[pilotId].push_back(id);
            pilotData[pilotId].push_back({date, {source, destination,id,time}});
        }
        in.close();
    }

    static void savePilots(
        const std::unordered_map<std::string,Pilot> &pilots, const std::string &file)
    {
        std::ofstream out(file);
        if (!out)
        {
            std::cout << "Error opening pilots file.\n";
            return;
        }
        for (const auto &pilotEntry : pilots)
        {
            const auto &pilot = pilotEntry.second;
            out << pilot.getPilotId() << " "
                << pilot.getPilotName() << " "
                << pilot.getPassportNumber() << " "
                << pilot.getAge() << " "
                << pilot.getGender() << " "
                << pilot.getPassword() << "\n";
        }
        out.close();
    }
    static void loadPilots(std::unordered_map<std::string, Pilot> &pilots,
        std::unordered_set<std::string> &pilotIds,const std::string &file)
    {
        std::ifstream in(file);
        if (!in)
        {
            std::cout << "Pilots file not found. Starting fresh.\n";
            return;
        }
        pilots.clear();
        pilotIds.clear();
        std::string id;
        std::string name;
        std::string passport;
        std::string password;
        int age;
        char gender;
        while (in >> id >> name >> passport >> age >> gender >> password)
        {
            Pilot pilot( id,  name,  passport, age,gender,  password);
            pilots[id] = pilot;
            pilotIds.insert(id);
        }
        in.close();
    }
};

#endif