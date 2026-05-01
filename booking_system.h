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
string getcurrenttime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday << "___"
       << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min << ":"
       << setw(2) << setfill('0') << ltm->tm_sec;

    return ss.str();
}
// Struct to keep track of booking times
struct BookingRecord
{
    string flightID;
    string bookingTime;
    string status;
};

class BookingSystem
{
private:
    unordered_map<string, Flight> flights;
    map<string, vector<Passenger>> bookings;
    map<string, unordered_set<string>> bookedPassports;

    map<string, vector<BookingRecord>> passengerHistory;
    unordered_map<string, Pilot> pilots;
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
            if (x.second.getpilotid() == l)
            {
                // cout<<x.getpilotpassword()<<endl;
                return x.second.getpilotpassword();
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
        if (flights.count(flightID))
            return &flights[flightID];
        return nullptr;
    }
    const map<string, vector<Passenger>> &getBookings() const
    {
        return bookings;
    }

    const unordered_map<string, Flight> &getFlights() const
    {
        return flights;
    }
    const unordered_map<string, Pilot> &getpilots() const
    {
        return pilots;
    }
    void removeflight()
    {
        string flid;
        cout << "Enter the Flight Id which you want to remove:";
        cin >> flid;
        if (flights.count(flid))
        {
            flights.erase(flid);
            cout << "Succesfully removed flight with flight Id:" << flid << endl;
        }
        else
            cout << "No Flight with flight ID:" << flid << endl;
    }
    void removepilot()
    {
        string plid;
        cout << "Enter the Pilot Id which you want to remove:";
        cin >> plid;
        if (pilots.count(plid))
        {
            pilots.erase(plid);
            cout << "Succesfully removed Pilot with Pilot Id:" << plid << endl;
        }
        else
            cout << "No pilot with pilot ID:" << plid << endl;
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
        if (flights.count(id))
            cout << id << "  Flight ID had already allocated to some flight";
        else
            flights[id] = f;
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
        if (!pilots.count(plid))
            pilots[plid] = p;
        else
        {
            cout << "Pilot already present with this pilot ID" << endl;
        }
        pilot_ids.insert(plid);
    }
    int getvacancies(const string &id)
    {
        if (flights.count(id))
            return flights[id].getvacancies();
        return 0;
    }

    void listFlights()
    {
        for (auto &f1 : flights)
        {
            auto f = f1.second;
            cout << "Flight: " << f.getFlightID()
                 << " | " << f.getSource() << " -> " << f.getDestination()
                 << " | Time: " << f.getTime() << endl;
        }
    }

    bool bookTicket(const string &flightID, const Passenger &p, int row, int col)
    {
        Flight *target = nullptr;
        if (flights.count(flightID))
            target = &flights[flightID];
        if (!target)
            return false;
        if (!target->isSeatAvailable(row, col))
            return false;

        target->bookSeat(row, col, 1);
        string temp = p.getPassportNumber();
        bookings[flightID].push_back(p);
        bookedPassports[flightID].insert(temp);

        passengerSeatMap[flightID].push_back({temp, {row, col}});

        passengerHistory[temp].push_back({flightID, getcurrenttime(), "booked"});

        return true;
    }
    void cancelTicket(const string &flightID, const string &passportNumber)
    {
        // 1. Find the flight object
        Flight *target = nullptr;
        if (flights.count(flightID))
            target = &flights[flightID];
        // If flight or booking doesn't exist,then exit
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
                passengerHistory[passportNumber].push_back({flightID, getcurrenttime(), "cancelled"});

                break;
            }
        }

        // 4. FREE THE SEAT on the Flight object
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
    void viewBookingHistory(const string &passport)
    {
        auto it = passengerHistory.find(passport);

        if (it == passengerHistory.end())
        {
            cout << "No travel history.\n";
            return;
        }

        for (auto &b : it->second)
            cout << b.flightID << " at " << b.bookingTime << " status " << b.status << endl;
    }
    int num_pilots()
    {
        return (int)pilot_ids.size();
    }
    Passenger *findPassenger(const string &flightID, const string &passport)
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
    void save_history(const string &file)
    {
        ofstream out(file);

        for (auto &f : passengerHistory)
        {
            for (auto &p : f.second)
            {

                out << f.first << " "
                    << p.flightID << " "
                    << p.bookingTime << " "
                    << p.status << "\n";
            }
        }
    }
    void load_history(const string &file)
    {
        ifstream in(file);
        if (!in)
        {
            cout << "Passenger history file not found. Starting fresh.\n";
            return;
        }

        passengerHistory.clear();

        string id, flightid, time, status;

        while (in >> id >> flightid >> time >> status)
        {
            passengerHistory[id].push_back({flightid, time, status});
        }

        in.close();
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

            // RE-BOOK THE SEAT ON LOAD which keeps the past booking data

            Flight *target = nullptr;
            if (flights.count(flight))
                target = &flights[flight];

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

        for (auto &f1 : flights)
        {
            auto f = f1.second;
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
            if (!check_pilot(plid))
            {
                addpilot();
            }
            if (flights.count(id))
                cout << id << "  Flight ID had already allocated to some flight";
            else
                flights[id] = f;
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

        for (auto &p1 : pilots)
        {
            auto p = p1.second;
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
            if (!pilots.count(id))
                pilots[id] = p;
            else
            {
                cout << "Pilot already present with this pilot ID" << id << endl;
            }
            pilot_ids.insert(id);
        }

        in.close();
    }
};
#endif
