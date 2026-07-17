#pragma once

#include <string>

class BookingSystem;
class RouteManager;
class BoardingPassPrinter;

class PassengerView
{
public:
    void listFlights(BookingSystem& system);

    void bookTicket(
        BookingSystem& system,
        RouteManager& routeManager,
        const std::string& passport);

    void cancelTicket(
        BookingSystem& system,
        const std::string& passport);

    void generateBoardingPass(
        BookingSystem& system,
        const std::string& passport,
        BoardingPassPrinter& boardingPassPrinter);

    void viewPassengerBookingHistory(
        const std::string& passport,
        const BookingSystem& system) const;
};