#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include "input_utils.hpp"
#include "booking_system.hpp"
#include "flight.hpp"
#include "passenger.hpp"
#include "route_manager.hpp"
#include "admin_view.hpp"
#include "pilot_view.hpp"
#include "boarding_pass_printer.hpp"
#include "login_manager.hpp"
#include "booking_storage.hpp"
#include "passenger_view.hpp"
#include <climits>

const std::string flightFile = "Data/flights.txt";
const std::string bookingFile = "Data/bookings.txt";
const std::string pilotFile = "Data/pilots.txt";
const std::string historyFile = "Data/bookinghistory.txt";

void savefiles(BookingSystem &system)
{
    BookingStorage::saveFlights(system.getFlights(), flightFile);
    BookingStorage::saveBookings(system.getBookings(), system.getPassengerSeatMap(), bookingFile);
    BookingStorage::savePilots(system.getPilots(), pilotFile);
    BookingStorage::saveHistory(system.getPassengerHistory(), historyFile);

}
void showAdminMenu(AdminView &adminview, BookingSystem &system)
{
    // std::string hi = "bookings.txt";
    while (true)
    {
        std::cout << "\n============ ADMIN PANEL ============\n";
        std::cout << "1. View All Bookings\n";
        std::cout << "2. View All Flights Stats\n";
        std::cout << "3. View All Flights Occupancy & Revenue\n";
        std::cout << "4. Save Data\n";
        std::cout << "5. Add Flight\n";
        std::cout << "6. Remove Flight\n";
        std::cout << "7. Add Pilot\n";
        std::cout << "8. Remove Pilot\n";
        std::cout << "9. Show all Pilots\n";
        std::cout << "10. Show one pilot details\n";
        std::cout << "11. Show one Flight Bookings\n";
        std::cout << "12. Show one Flight Occupancy and revenue \n";
        std::cout << "13. Exit Admin Panel\n";
        // std::cout << "Enter choice: ";
        int choice = getValidatedInt("Enter choice: ", 1, 13);

        switch (choice)
        {
        case 1:
        {
            adminview.viewAllBookings(system);
            break;
        }
        case 2:
        {
            adminview.viewFlightStats(system);
            break;
        }
        case 3:
        {
            adminview.viewOccupancyAndRevenue(system);
            break;
        }
        case 4:
        {
            savefiles(system);
            std::cout << "Data saved.\n";
            break;
        }
        case 5:
        {
            adminview.addFlight(system);
            savefiles(system);
            break;
        }
        case 6:
        {

            adminview.removeFlight(system);
            savefiles(system);
            break;
        }
        case 7:
        {
            adminview.addPilot(system);
            savefiles(system);
            std::cout << "Succesfully added pilot" << std::endl;
            break;
        }
        case 8:
        {

            adminview.removePilot(system);
            savefiles(system);
            break;
        }
        case 9:
        {
            adminview.showAllPilots(system);
            break;
        }
        case 10:
        {
            adminview.showOnePilotDetails(system);
            break;
        }
        case 11:
        {
            adminview.viewOneFlightBooking(system);
            break;
        }
        case 12:
        {
            adminview.viewOneFlightOccupancy(system);
            break;
        }
        case 13:
        {
            std::cout << "Exiting admin panel.\n";
            return;
        }
        default:
            std::cout << "Invalid option.\n";
            return;
        }
    }
}
void showPilotMenu(PilotView &pilotView, BookingSystem &system, const std::string &pilotId)
{
    while (true)
    {
        std::cout
            << "\n========== PILOT PANEL ==========\n";

        std::cout << "1. View Schedule\n";
        std::cout << "2. View Details\n";
        std::cout << "3. Save Data\n";
        std::cout << "4. Exit\n";

        int choice = getValidatedInt("Enter choice: ", 1, 4);

        switch (choice)
        {
        case 1:
            pilotView.viewSchedule(system, pilotId);
            break;

        case 2:
            pilotView.viewDetails(system, pilotId);
            break;
        case 3:
            savefiles(system);
            std::cout << "Data saved\n";
            break;
        case 4:
            std::cout << "Exiting Pilot Panel.\n";
            return;
        }
    }
}
void showPassengerView(PassengerView &passengerView, BookingSystem &system, const std::string &passport, RouteManager &routeManager, BoardingPassPrinter &boardingPassPrinter)
{
    bool p = true;
    while (p)
    {
        std::cout << "\n========== PASSENGER MENU ==========\n";
        std::cout << "1. View Flights\n";
        std::cout << "2. Book Ticket\n";
        std::cout << "3. Cancel Ticket\n";
        std::cout << "4. Generate Boarding Pass\n";
        std::cout << "5. View Booking History\n";
        std::cout << "6. Logout\n";
        int choice = getValidatedInt("Enter choice: ", 1, 6);
        switch (choice)
        {
        case 1:
        {
            passengerView.listFlights(system);
            break;
        }
        case 2:
        {
            passengerView.bookTicket(system, routeManager, passport);
            savefiles(system);
            break;
        }
        case 3:
        {
            passengerView.cancelTicket(system, passport);
            savefiles(system);
            break;
        }
        case 4:
        {
            passengerView.generateBoardingPass(system, passport, boardingPassPrinter);
            break;
        }
        case 5:
        {
            passengerView.viewPassengerBookingHistory(passport, system);
            break;
        }
        case 6:
        {
            std::cout << "Logged out.\n";
            savefiles(system);
            p = false;
            break;
        }
        default:
        {
            std::cout << "Invalid Entry\n";
            p = false;
            break;
        }
        }
    }
}
int main()
{
    std::cout << "Welcome to Domestic Airline Booking System.\n";
    BookingSystem system;
    RouteManager routeManager;
    LoginManager loginManager;
    AdminView adminView;
    PilotView pilotView;
    PassengerView passengerView;
    BoardingPassPrinter boardingPassPrinter;

    BookingStorage::loadPilots(system.getPilotsall(), system.getAllPilotIds(), pilotFile);
    BookingStorage::loadFlights(system.getAllFlights(), system.getPilotFlights(), system.getPilotData(), flightFile);
    BookingStorage::loadBookings(system.getBookings(), system.getBookedPassports(),
                                 system.getPassengerSeatMapAll(), system.getAllFlights(), bookingFile);
    BookingStorage::loadHistory(system.getPassengerHistory(), historyFile);

    std::cout << "\nLogin As:\n";
    std::cout << "1. Admin\n";
    std::cout << "2. Pilot\n";
    std::cout << "3. Passenger\n";
    int loginChoice = getValidatedInt("Enter choice: ", 1, 3);
    if (loginChoice == 1)
    {
        if (!loginManager.loginAsAdmin())
        {
            std::cout << "Admin login failed.\n";
            return 0;
        }
        showAdminMenu(adminView, system);
        
    }

    else if (loginChoice == 2)
    {
        std::string pilotId;
        std::cout << "Enter Pilot ID: ";
        std::cin >> pilotId;
        if (!loginManager.loginAsPilot(pilotId, system))
        {
            std::cout << "Pilot login failed.\n";
            return 0;
        }
        showPilotMenu(pilotView, system, pilotId);
        
    }

    else
    {
        std::string passport;
        std::cout << "Enter Passport Number: ";
        std::cin >> passport;
        if (!loginManager.loginAsPassenger(passport))
        {
            std::cout << "Passenger login failed.\n";
            return 0;
        }
        showPassengerView(passengerView, system, passport, routeManager, boardingPassPrinter);
        
    }
    
    return 0;
}