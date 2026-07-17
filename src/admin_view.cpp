// #ifndef ADMIN_H
// #define ADMIN_H

// #include <iostream>
#include "admin_view.hpp"

#include <iostream>
#include <string>
#include "booking_system.hpp"
#include "flight.hpp"
#include "pilot.hpp"


    void AdminView::viewAllBookings(const BookingSystem &system) const
    {
        std::cout << "\n========== ALL BOOKINGS ==========\n";
        const auto &all = system.getBookings();
        if (all.empty())
        {
            std::cout << "No bookings found.\n";
            return;
        }
        for (const auto &entry : all)
        {
            const std::string &flightId = entry.first;
            const auto &plist = entry.second;
            std::cout << "\nFlight ID: " << flightId << "\n";
            std::cout << "---------------------------------------\n";
            for (const auto &p : plist)
            {
                std::cout << "Passenger Name: " << p.getName() << "\n";
                std::cout << "Passport Number: " << p.getPassportNumber() << "\n";
                std::cout << "Age: " << p.getAge() << "\n";
                std::cout << "Gender: " << p.getGender() << "\n";
                std::cout << "---------------------------------------\n";
            }
        }
    }

    void AdminView:: viewOneFlightBooking(const BookingSystem &system) const
    {
        std::cout << "\n========== FLIGHT BOOKINGS ==========\n";
        const auto &all = system.getBookings();
        if (all.empty())
        {
            std::cout << "No bookings found.\n";
            return;
        }
        std::string flightId;
        std::cout << "Enter Flight ID: ";
        std::cin >> flightId;
        if (all.count(flightId))
        {
            const auto &plist = all.at(flightId);
            std::cout << "\nFlight ID: " << flightId << "\n";
            std::cout << "---------------------------------------\n";
            for (const auto &p : plist)
            {
                std::cout << "Passenger Name: " << p.getName() << "\n";
                std::cout << "Passport Number: " << p.getPassportNumber() << "\n";
                std::cout << "Age: " << p.getAge() << "\n";
                std::cout << "Gender: " << p.getGender() << "\n";
                std::cout << "---------------------------------------\n";
            }
        }
        else
        {
            std::cout << "Flight not found.\n";
        }
    }

    void AdminView::viewFlightStats(const BookingSystem &system) const
    {
        std::cout << "\n========== FLIGHT STATISTICS ==========\n";
        const auto &flights = system.getFlights();
        const auto &bookings = system.getBookings();
        if (flights.empty())
        {
            std::cout << "No flights loaded.\n";
            return;
        }
        for (const auto &f1 : flights)
        {
            const auto &f = f1.second;
            int booked = 0;
            if (bookings.count(f.getFlightId()))
                booked = bookings.at(f.getFlightId()).size();
            int totalSeats = f.getTotalRows() * f.getTotalCols();
            std::cout << "\nFlight: " << f.getFlightId() << "\n";
            std::cout << "Pilot ID: " << f.getPilotId() << "\n";
            std::cout << "Route: " << f.getSource() << " -> " << f.getDestination() << "\n";
            std::cout << "Date: " << f.getDate() << "\n";
            std::cout << "Time: " << f.getTime() << "\n";
            std::cout << "Seats Booked: " << booked << "/" << totalSeats << "\n";
            std::cout << "---------------------------------------\n";
        }
    }

    void AdminView:: viewOccupancyAndRevenue(const BookingSystem &system) const
    {
        std::cout << "\n========== OCCUPANCY & REVENUE REPORT ==========\n";
        const auto &flights = system.getFlights();
        if (flights.empty())
        {
            std::cout << "No flights found.\n";
            return;
        }
        for (const auto &f1 : flights)
        {
            const auto &f = f1.second;
            double occupancy = f.getOccupancyRate() * 100;

            std::cout << "\nFlight: " << f.getFlightId() << "\n";
            std::cout << "Pilot ID: " << f.getPilotId() << "\n";
            std::cout << "Occupancy: " << occupancy << "%\n";
            std::cout << "Revenue: Rs. " << f.getRevenue() << "\n";
            std::cout << "---------------------------------------\n";
        }
    }

    void AdminView:: viewOneFlightOccupancy(const BookingSystem &system) const
    {
        
        const auto &flights = system.getFlights();
        if (flights.empty())
        {
            std::cout << "No flights found.\n";
            return;
        }
        std::string flightId;
        std::cout << "Enter Flight ID: ";
        std::cin >> flightId;
        if (flights.count(flightId))
        {
            std::cout << "\n========== FLIGHT OCCUPANCY & REVENUE ==========\n";
            const auto &f = flights.at(flightId);
            double occupancy = f.getOccupancyRate() * 100;
            std::cout << "\nFlight: " << f.getFlightId() << "\n";
            std::cout << "Pilot ID: " << f.getPilotId() << "\n";
            std::cout << "Occupancy: " << occupancy << "%\n";
            std::cout << "Revenue: Rs. " << f.getRevenue() << "\n";
            std::cout << "---------------------------------------\n";
        }
        else
        {
            std::cout << "Flight not found with ID: " << flightId << "\n";
        }
    }

    void AdminView:: showAllPilots(const BookingSystem &system) const
    {
        const auto &pilots = system.getPilots();
        if (pilots.empty())
        {
            std::cout << "No pilots found.\n";
            return;
        }
        for (const auto &p1 : pilots)
        {
            const auto &p = p1.second;
            std::cout << "\nPilot ID: " << p.getPilotId() << "\n";
            std::cout << "Pilot Name: " << p.getPilotName() << "\n";
            std::cout << "Passport Number: " << p.getPassportNumber() << "\n";
            std::cout << "Age: " << p.getAge() << "\n";
            std::cout << "Gender: " << p.getGender() << "\n";
            std::cout << "---------------------------------------\n";
        }
    }

    void AdminView:: showOnePilotDetails(const BookingSystem &system) const
    {
        const auto &pilots = system.getPilots();
        std::string pilotId;
        std::cout << "Enter Pilot ID: ";
        std::cin >> pilotId;
        if (pilots.count(pilotId))
        {
            const auto &p = pilots.at(pilotId);
            std::cout << "\nPilot Name: " << p.getPilotName() << "\n";
            std::cout << "Passport Number: " << p.getPassportNumber() << "\n";
            std::cout << "Age: " << p.getAge() << "\n";
            std::cout << "Gender: " << p.getGender() << "\n";
            std::cout << "---------------------------------------\n";
        }
        else
        {
            std::cout << "Pilot not found with ID: "
                      << pilotId << "\n";
        }
    }
    void AdminView:: addPilot(BookingSystem &system) const
    {
        std::string name;
        std::string passportNumber;
        std::string pilotId;
        std::string password;

        int age;
        char gender;
        std::cout
            << "Enter (Name PassportNumber PilotID Age Gender Password):\n";
        std::cin >> name >> passportNumber >> pilotId >> age >> gender >> password;
        Pilot pilot(pilotId, name, passportNumber, age, gender, password);
        if (system.addPilot(pilot))
        {
            std::cout << "Pilot added successfully.\n";
        }
        else
        {
            std::cout << "Pilot already exists.\n";
        }
    }
    void AdminView:: removePilot(BookingSystem &system) const
    {
        std::string pilotId;
        std::cout << "Enter Pilot ID: ";
        std::cin >> pilotId;
        if (system.removePilot(pilotId))
        {
            std::cout << "Pilot removed successfully.\n";
        }
        else
        {
            std::cout << "Pilot not found.\n";
        }
    }
    void AdminView::addFlight(BookingSystem &system) const
    {
        std::string id;
        std::string pilotId;
        std::string source;
        std::string destination;
        std::string date;
        std::string time;
        int rows;
        int cols;
        int baseFare;

        double revenue;
        std::cout << "Enter Flight Details (id pilotId source destination date time rows cols baseFare revenue): ";
        std::cin >> id >> pilotId >> source >> destination >> date >> time >> rows >> cols >> baseFare >> revenue;
        Flight flight(id, pilotId, source, destination, date, time, rows, cols, baseFare, revenue);
        if (system.addFlight(flight))
        {
            std::cout << "Flight added successfully.\n";
        }
        else
        {
            std::cout << "Flight already exists.\n";
        }
    }

    void AdminView::removeFlight(
        BookingSystem &system) const
    {
        std::string flightId;
        std::cout << "Enter Flight ID: ";
        std::cin >> flightId;
        if (system.removeFlight(flightId))
        {
            std::cout << "Flight removed successfully.\n";
        }
        else
        {
            std::cout << "Flight not found.\n";
        }
    }
    void AdminView::listFlights(BookingSystem &system)
    {
        auto flights = system.getAllFlights();
        for (auto &f1 : flights)
        {
            auto f = f1.second;
            std::cout << "Flight: " << f.getFlightId() << "|" << f.getSource() << "->" << f.getDestination() << "| Time:" << f.getTime() << std::endl;
        }
    }
    void AdminView::viewPassengerBookingHistory(const std::string passport, BookingSystem &system) const
    {
        auto passhis = system.getPassengerHistory();
        auto it = passhis.find(passport);
        if (it == passhis.end())
        {
            std::cout << "No Past Travel history Found" << std::endl;
            return;
        }
        for (auto &b : it->second)
        {
            std::cout << b.flightId << " at " << b.bookingTime << " status " << b.status << std::endl;
        }
    }

