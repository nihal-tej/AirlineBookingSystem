#ifndef ADMIN_H
#define ADMIN_H

#include "booking_system.h"
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

        for (auto &f : flights)
        {
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

        for (auto &f : flights)
        {
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
    void showMenu(BookingSystem &system)
    {
        string hi = "bookings.txt";
        while (true)
        {
            cout << "\n============ ADMIN PANEL ============\n";
            cout << "1. View All Bookings\n";
            cout << "2. View Flight Stats\n";
            cout << "3. View Occupancy & Revenue\n";
            cout << "4. Save Data\n";
            cout << "5. Add Flight\n";
            cout << "6. Exit Admin Panel\n";
            cout << "Enter choice: ";

            int choice;
            cin >> choice;
            
            switch (choice)
            {
            case 1:
                viewAllBookings(system);
                break;

            case 2:
                viewFlightStats(system);
                break;

            case 3:
                viewOccupancyAndRevenue(system);
                break;

            case 4:
                system.save_Data(hi);
                cout << "Data saved.\n";
                break;

            case 6:
                cout << "Exiting admin panel.\n";
                return;
            case 5:
            {
                system.addFlight();
                
                break;
            }
            default:
                cout << "Invalid option.\n";
            }
        }
    }
};

#endif // ADMIN_H
