#ifndef ADMIN_H
#define ADMIN_H

#include "booking_system.h"
#include "pilot.h"
#include "flight.h"
#include <iostream>
#include <string>
using namespace std;

class Admin
{
public:
    void viewAllBookings(const BookingSystem &system)
    {
        cout << "\n========== ALL BOOKINGS ==========\n";
        auto all = system.getBookings();

        if (all.empty())
        {
            cout << "No bookings found.\n";
            return;
        }

        for (const auto &entry : all)
        {
            string flightID = entry.first;
            const auto &plist = entry.second;

            cout << "\nFlight ID: " << flightID << "\n";
            cout << "---------------------------------------\n";

            for (const auto &p : plist)
            {
                cout << "Passenger Name: " << p.getName() << "\n";
                cout << "Passport Number: " << p.getPassportNumber() << "\n";
                cout << "Age: " << p.getAge() << "\n";
                cout << "Gender: " << p.getGender() << "\n";
                cout << "---------------------------------------\n";
            }
        }
    }
    void viewoneflightbooking(const BookingSystem &system)
    {
        cout << "\n==========  BOOKINGS ==========\n";
        auto all = system.getBookings();

        if (all.empty())
        {
            cout << "No bookings found.\n";
            return;
        }
        string flid;
        cout << "Enter the flight ID:";
        cin >> flid;

        if (all.count(flid))
        {
            const auto &plist = all[flid];

            cout << "\nFlight ID: " << flid << "\n";
            cout << "---------------------------------------\n";

            for (const auto &p : plist)
            {
                cout << "Passenger Name: " << p.getName() << "\n";
                cout << "Passport Number: " << p.getPassportNumber() << "\n";
                cout << "Age: " << p.getAge() << "\n";
                cout << "Gender: " << p.getGender() << "\n";
                cout << "---------------------------------------\n";
            }
        }
    }
    void viewFlightStats(const BookingSystem &system)
    {
        cout << "\n========== FLIGHT STATISTICS ==========\n";

        const auto &flights = system.getFlights();
        const auto &bookings = system.getBookings();

        if (flights.empty())
        {
            cout << "No flights loaded.\n";
            return;
        }

        for (auto &f1 : flights)
        {
            auto f = f1.second;
            int booked = 0;

            if (bookings.count(f.getFlightID()))
                booked = bookings.at(f.getFlightID()).size();

            int totalSeats = f.getTotalRows() * f.getTotalCols();

            cout << "\nFlight: " << f.getFlightID() << "\n";
            cout << "Flight Pilot id:" << f.getPilotId() << "\n";
            cout << "Route: " << f.getSource() << " -> " << f.getDestination() << "\n";
            cout << "Date: " << f.getdate() << "\n";
            cout << "Time: " << f.getTime() << "\n";
            cout << "Seats Booked: " << booked << "/" << totalSeats << "\n";
            cout << "---------------------------------------\n";
        }
    }

    void viewOccupancyAndRevenue(const BookingSystem &system)
    {
        cout << "\n========== OCCUPANCY & REVENUE REPORT ==========\n";

        const auto &flights = system.getFlights();
        const auto &bookings = system.getBookings();

        if (flights.empty())
        {
            cout << "No flights found.\n";
            return;
        }

        for (auto &f1 : flights)
        {
            auto f = f1.second;
            int booked = 0;
            double revenue = 0;

            if (bookings.count(f.getFlightID()))
            {
                booked = bookings.at(f.getFlightID()).size();
                revenue = f.getRevenue();
            }

            int totalSeats = f.getTotalRows() * f.getTotalCols();
            double occupancy = f.getOccupancyRate();

            cout << "\nFlight: " << f.getFlightID() << "\n";
            cout << "Flight Pilot id:" << f.getPilotId() << "\n";
            cout << "Occupancy: " << occupancy << "%\n";
            cout << "Revenue: Rs. " << revenue << "\n";
            cout << "---------------------------------------\n";
        }
    }
    void viewoneflightoccupancy(const BookingSystem &system)
    {
        cout << "\n========== OCCUPANCY & REVENUE of one flight==========\n";

        const auto &flights = system.getFlights();
        const auto &bookings = system.getBookings();

        if (flights.empty())
        {
            cout << "No flights found.\n";
            return;
        }
        string flid;
        cout << "Enter id of flight:";
        cin >> flid;
        if (flights.count(flid))
        {
            auto f = flights.at(flid);
            int booked = 0;
            double revenue = 0;

            if (bookings.count(f.getFlightID()))
            {
                booked = bookings.at(f.getFlightID()).size();
                revenue = f.getRevenue();
            }

            int totalSeats = f.getTotalRows() * f.getTotalCols();
            double occupancy = f.getOccupancyRate();

            cout << "\nFlight: " << f.getFlightID() << "\n";
            cout << "Flight Pilot id:" << f.getPilotId() << "\n";
            cout << "Occupancy: " << occupancy << "%\n";
            cout << "Revenue: Rs. " << revenue << "\n";
            cout << "---------------------------------------\n";
        }
        else
        {
            cout << "NO Flight with flight ID:" << flid << endl;
        }
    }
    void showallpilots(BookingSystem &system)
    {

        const auto &pilots = system.getpilots();
        for (auto &p1 : pilots)
        {
            auto p = p1.second;
            cout << "\nPilot Id:" << p.getpilotid() << "\n";
            cout << "Pilot Name:" << p.getpilotname() << "\n";
            cout << "Passport Number:" << p.getpilotpassportnumber() << "\n";
            cout << "Age:" << p.getpilotage() << "\n";
            cout << "Gender:" << p.getpilotgender() << "\n";
            cout << "---------------------------------------\n";
        }
    }
    void showonepilotdetails(BookingSystem &system)
    {

        const auto &pilots = system.getpilots();
        string plid;
        int r = 0;
        cout << "Enter the pilotid of required pilot:" << endl;
        cin >> plid;
        if (pilots.count(plid))
        {

            cout << "\nPilot Name:" << pilots.at(plid).getpilotname() << "\n";
            cout << "Passport Number:" << pilots.at(plid).getpilotpassportnumber() << "\n";
            cout << "Age:" << pilots.at(plid).getpilotage() << "\n";
            cout << "Gender" << pilots.at(plid).getpilotgender() << "\n";
            cout << "---------------------------------------\n";
        }
        else
        {
            cout << "Pilot not found with pilot ID" << plid << endl;
        }
    }
    void showMenu(BookingSystem &system)
    {
        string hi = "bookings.txt";
        while (true)
        {
            cout << "\n============ ADMIN PANEL ============\n";
            cout << "1. View All Bookings\n";
            cout << "2. View All Flights Stats\n";
            cout << "3. View All Flights Occupancy & Revenue\n";
            cout << "4. Save Data\n";
            cout << "5. Add Flight\n";
            cout << "6. Remove Flight\n";
            cout << "7. Add Pilot\n";
            cout << "8. Remove Pilot\n";
            cout << "9. Show all Pilots\n";
            cout << "10. Show one pilot details\n";
            cout << "11. Show one Flight Bookings\n";
            cout << "12. Show one Flight Occupancy and revenue \n";
            cout << "13. Exit Admin Panel\n";
            cout << "Enter choice: ";

            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                viewAllBookings(system);
                break;
            }
            case 2:
            {
                viewFlightStats(system);
                break;
            }
            case 3:
            {
                viewOccupancyAndRevenue(system);
                break;
            }
            case 4:
            {

                cout << "Data saved.\n";
                break;
            }
            case 5:
            {
                system.addFlight();
                break;
            }
            case 6:
            {

                system.removeflight();
                break;
            }
            case 7:
            {
                system.addpilot();
                cout << "Succesfully added pilot" << endl;
                break;
            }
            case 8:
            {

                system.removepilot();
                break;
            }
            case 9:
            {
                showallpilots(system);
                break;
            }
            case 10:
            {
                showonepilotdetails(system);
                break;
            }
            case 11:
            {
                viewoneflightbooking(system);
                break;
            }
            case 12:
            {
                viewoneflightoccupancy(system);
                break;
            }
            case 13:
            {
                cout << "Exiting admin panel.\n";
                return;
            }
            default:
                cout << "Invalid option.\n";
            }
        }
    }
};

#endif // ADMIN_H
