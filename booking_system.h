#ifndef BOOKING_SYSTEM_H
#define BOOKING_SYSTEM_H

#include "flight.h"
#include "passenger.h"
#include "pilot.h"
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
using namespace std;

// Struct to keep track of booking times
struct BookingRecord
{
    string flightID;
    string bookingTime;
};

class BookingSystem
{
private:
    vector<Flight> flights;
    map<string, vector<Passenger>> bookings;
    map<string, unordered_set<string>> bookedPassports;
    map<string, vector<BookingRecord>> bookingHistory;
    map<string, vector<BookingRecord>> passengerHistory;
    vector<Pilot> pilots;
    unordered_map<string, vector<pair<string, pair<int, int>>>> passengerSeatMap;
    unordered_map<string, vector<pair<string, tuple<string, string, string, string>>>> pilotdata;
    unordered_map<string, vector<string>> pilotflight;
    unordered_set<string> pilot_ids;

public:
    vector<pair<string, tuple<string, string, string, string>>> getpilotsch(const string &pil)
    {
        if (pilotdata.count(pil))
            return pilotdata[pil];
        return {};
    }
    string getloginpassword(const string &l)
    {
        if (pilot_ids.find(l) == pilot_ids.end())
            return "";
        for (auto &x : pilots)
            if (x.getpilotid() == l){
                // cout<<x.getpilotpassword()<<endl;
                return x.getpilotpassword();
            }
        return "";
    }
    bool check_pilot(const string &p)
    {
        if (pilot_ids.find(p) != pilot_ids.end())
            return true;
        return false;
    }
    Flight *findFlight(const string &flightID)
    {
        for (auto &f : flights)
            if (f.getFlightID() == flightID)
                return &f; 
        return nullptr;
    }
    const map<string, vector<Passenger>> &getBookings() const
    {
        return bookings;
    }

    const vector<Flight> &getFlights() const
    {
        return flights;
    }

    void addFlight()
    {
        string id, src, dst, date, time, plid1;
        int rows, cols, basefare;
        double rev;
        cout << "Enter the flight details:\n";
        cout << "FlightID  PilotID  Source  Destination  Date  Time  Rows  Cols  BaseFare Revenue\n";
        cin >> id >> plid1 >> src >> dst >> date >> time >> rows >> cols >> basefare >> rev;
        Flight f(id, plid1, src, dst, date, time, rows, cols, basefare, rev);
        cout << "Flight created: " << id << endl;
        pilotflight[plid1].push_back(id);
        pilotdata[plid1].push_back({date, {src, dst, id, time}});
        if (!check_pilot(plid1))
        {
            addpilot();
        }
        flights.push_back(f);
    }
    void addpilot()
    {
        string name, passportNumber, plid;
        int age;
        char gender;
        string password;
        cout << "Enter: name passportNumber(12d) id age gender password\n";
        cin >> name >> passportNumber >> plid >> age >> gender >> password;
        Pilot p(plid, name, passportNumber, age, gender, password);
        pilots.push_back(p);
        pilot_ids.insert(plid);
    }
    int getvacancies(const string &id)
    {
        for (auto &x : flights)
            if (x.getFlightID() == id)
                return x.getvacancies();
        return 0;
    }

    void listFlights()
    {
        for (auto &f : flights)
        {
            cout << "Flight: " << f.getFlightID()
                 << " | " << f.getSource() << " -> " << f.getDestination()
                 << " | Time: " << f.getTime() << endl;
        }
    }

    bool bookTicket(const string &flightID,const Passenger &p, int row, int col)
    {
        Flight *target = nullptr;
        for (auto &f : flights)
            if (f.getFlightID() == flightID)
                target = &f;

        if (!target)
            return false;
        if (!target->isSeatAvailable(row, col))
            return false;

        target->bookSeat(row, col, 1);
        string temp = p.getPassportNumber();
        bookings[flightID].push_back(p);
        bookedPassports[flightID].insert(temp);

        passengerSeatMap[flightID].push_back({temp, {row, col}});

        bookingHistory[temp].push_back({flightID, "TIME"});
        passengerHistory[temp].push_back({flightID, "TIME"});

        return true;
    }
    void cancelTicket(const string &flightID,const string &passportNumber)
    {
        // 1. Find the flight object
        Flight *target = nullptr;
        for (auto &f : flights)
            if (f.getFlightID() == flightID)
                target = &f;

        // If flight or booking doesn't exist, exit
        if (!target || bookings.find(flightID) == bookings.end())
            return;

        // 2. Find the passenger's seat coordinates
        pair<int, int> seat_coords = getPassengerSeat(flightID, passportNumber);

        // 3. Remove passenger from internal booking lists
        auto &vec = bookings[flightID];
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].getPassportNumber() == passportNumber)
            {
                vec.erase(vec.begin() + i);
                bookedPassports[flightID].erase(passportNumber);
                break;
            }
        }

        // 4. FREE THE SEAT on the Flight object (THE FIX)
        if (seat_coords.first != -1)
        {
            target->freeSeat(seat_coords.first, seat_coords.second);

            // OPTIONAL: Remove the seat from the passengerSeatMap
            auto &seat_list = passengerSeatMap.at(flightID);
            for (auto it = seat_list.begin(); it != seat_list.end(); ++it)
            {
                if (it->first == passportNumber)
                {
                    seat_list.erase(it);
                    break;
                }
            }
        }
    }

    void viewPassengerHistory(const string &passport)
    {
        auto it = bookingHistory.find(passport);

        if (it == bookingHistory.end())
        {
            cout << "No history.\n";
            return;
        }

        for (auto &rec : it->second)
            cout << rec.flightID << " at " << rec.bookingTime << endl;
    }

    void viewBookingHistory(const string &passport)
    {
        auto it = passengerHistory.find(passport);

        if (it == passengerHistory.end())
        {
            cout << "No travel history.\n";
            return;
        }

        for (auto &b : it->second)
            cout << b.flightID << " at " << b.bookingTime << endl;
    }
    int num_pilots()
    {
        return (int)pilot_ids.size();
    }
    Passenger *findPassenger(const string &flightID,const string &passport)
    {
        auto &vec = bookings[flightID];
        for (auto &p : vec)
            if (p.getPassportNumber() == passport)
                return &p;
        return nullptr;
    }

    pair<int, int> getPassengerSeat(const string &flightID, const string &passport)
    {
        auto it = passengerSeatMap.find(flightID);
        if (it == passengerSeatMap.end())
            return {-1, -1};

        for (auto &x : it->second)
            if (x.first == passport)
                return x.second;

        return {-1, -1};
    }

    const unordered_map<string, vector<pair<string, pair<int, int>>>> &getPassengerSeatMap()
    {
        return passengerSeatMap;
    }
    // Update save_Data to include seat information (Row and Column index 0-5 for A-F)
    void save_Data(const string &file)
    {
        ofstream out(file);

        for (auto &f : bookings)
        {
            for (auto &p : f.second)
            {
                // Find the seat for this passenger
                pair<int, int> seat = getPassengerSeat(f.first, p.getPassportNumber());

                out << f.first << " "
                    << p.getName() << " "
                    << p.getPassportNumber() << " "
                    << p.getGender() << " "
                    << p.getAge() << " "
                    << seat.first << " "    
                    << seat.second << "\n"; 
            }
        }
    }

    // Update load_Data to read seat information and book the seat
    void load_Data(const string &file)
    {
        ifstream in(file);

        string flight, name, passport;
        int age, row_index, col_index; 
        char gender;

        // READS: FlightID Name Passport Gender Age RowIndex ColIndex
        while (in >> flight >> name >> passport >> gender >> age >> row_index >> col_index)
        {
            Passenger p(name, passport, age, gender);
            bookings[flight].push_back(p);
            bookedPassports[flight].insert(passport);
            
            // RE-BOOK THE SEAT ON LOAD (The Fix)
            Flight *target = nullptr;
            for (auto &f : flights)
                if (f.getFlightID() == flight)
                    target = &f;

            if (target)
            {
                target->bookSeat(row_index, col_index, 0);
                // Re-populate passengerSeatMap 
                passengerSeatMap[flight].push_back({passport, {row_index, col_index}});
            }
        }
    }
    void save_Flights(const string &file)
    {
        ofstream out(file);

        for (auto &f : flights)
        {
            out << f.getFlightID() << " "
                << f.getPilotId() << " "
                << f.getSource() << " "
                << f.getDestination() << " "
                << f.getdate() << " "
                << f.getTime() << " "
                << f.getTotalRows() << " "
                << f.getTotalCols() << " "
                << f.getBaseFare() << " "
                << f.getRevenue() << "\n";
        }
    }

    void load_Flights(const string &file)
    {
        ifstream in(file);

        string id, src, dst, date, time, plid;
        int rows, cols, basefare;
        double rev;
        while (in >> id >> plid >> src >> dst >> date >> time >> rows >> cols >> basefare >> rev)
        {
            Flight f(id, plid, src, dst, date, time, rows, cols, basefare, rev);
            flights.push_back(f);
            pilotflight[plid].push_back(id);
            pilotdata[plid].push_back({date, {src, dst, id, time}});
        }
    }
    void save_Pilots(const string &file)
    {
        ofstream out(file);
        if (!out)
        {
            cout << "Error opening pilots file for saving\n";
            return;
        }

        for (auto &p : pilots)
        {
            out << p.getpilotid() << " "
                << p.getpilotname() << " "
                << p.getpilotpassportnumber() << " "
                << p.getpilotage() << " "
                << p.getpilotgender() << " "
                << p.getpilotpassword() << "\n";
        }

        out.close();
    }
    void load_pilots(const string &file)
    {
        ifstream in(file);
        if (!in)
        {
            cout << "Pilots file not found. Starting fresh.\n";
            return;
        }

        pilots.clear();
        pilot_ids.clear();

        string id, name, passport, password;
        int age;
        char gender;

        while (in >> id >> name >> passport >> age >> gender >> password)
        {
            Pilot p(id, name, passport, age, gender, password);
            pilots.push_back(p);
            pilot_ids.insert(id);
        }

        in.close();
    }
};
#endif
