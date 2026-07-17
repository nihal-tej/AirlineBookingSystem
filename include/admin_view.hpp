#pragma once

#include <string>
#include "passenger.hpp"
class BookingSystem;

class AdminView
{
public:
    void viewAllBookings(const BookingSystem &system) const;

    void viewOneFlightBooking(const BookingSystem &system) const;

    void viewFlightStats(const BookingSystem &system) const;

    void viewOccupancyAndRevenue(const BookingSystem &system) const;

    void viewOneFlightOccupancy(const BookingSystem &system) const;

    void showAllPilots(const BookingSystem &system) const;

    void showOnePilotDetails(const BookingSystem &system) const;

    void addPilot(BookingSystem &system) const;

    void removePilot(BookingSystem &system) const;

    void addFlight(BookingSystem &system) const;

    void removeFlight(BookingSystem &system) const;

    void listFlights(BookingSystem &system);

    void viewPassengerBookingHistory(const std::string passport,
                                     BookingSystem &system) const;
};