#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

#include "Header_files/booking_system.h"
#include "Header_files/flight.h"
#include "Header_files/passenger.h"
#include "Header_files/route_manager.h"
#include "Header_files/admin_view.h"
#include "Header_files/pilot_view.h"
#include "Header_files/boarding_pass_printer.h"
#include "Header_files/login_manager.h"
#include "Header_files/booking_storage.h"
#include <climits>
void clearInputStream()
{
    std::cin.clear();

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
}

int getValidatedInt(const std::string &prompt, int min = INT_MIN, int max = INT_MAX)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max)
        {
            std::cout << "Invalid input.\n";
            clearInputStream();
        }
        else
        {
            clearInputStream();
            return value;
        }
    }
}

char getValidatedChar(const std::string &prompt, const std::string &validChars)
{
    char ch;
    while (true)
    {
        std::cout << prompt;
        std::cin >> ch;
        ch = std::toupper(ch);
        if (validChars.find(ch) != std::string::npos)
        {
            clearInputStream();
            return ch;
        }
        std::cout << "Invalid input.\n";
        clearInputStream();
    }
}
void showAdminMenu(AdminView &adminview, BookingSystem &system)
{
    std::string hi = "bookings.txt";
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
        std::cout << "Enter choice: ";
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

            std::cout << "Data saved.\n";
            break;
        }
        case 5:
        {
            adminview.addFlight(system);
            break;
        }
        case 6:
        {

            adminview.removeFlight(system);
            break;
        }
        case 7:
        {
            adminview.addPilot(system);
            std::cout << "Succesfully added pilot" << std::endl;
            break;
        }
        case 8:
        {

            adminview.removePilot(system);
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
            BookingStorage::savePilots(system.getPilots(), "pilots.txt");
            std::cout << "Data saved\n";
            break;
        case 4:
            std::cout << "Exiting Pilot Panel.\n";
            return;
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

    BoardingPassPrinter boardingPassPrinter;

    const std::string flightFile = "flights.txt";
    const std::string bookingFile = "bookings.txt";
    const std::string pilotFile = "pilots.txt";
    const std::string historyFile = "bookinghistory.txt";

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
        bool p=true;
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
                adminView.listFlights(system);
                break;
            }
            case 2:
            {
                std::string source;
                std::string destination;
                std::string date;
                std::cout << "Enter Source: ";
                std::cin >> source;
                std::cout << "Enter Destination: ";
                std::cin >> destination;
                std::cout << "Enter Date: ";
                std::cin >> date;
                std::cout << "1. Morning\n";
                std::cout << "2. Afternoon\n";
                std::cout << "3. Evening\n";
                int slotChoice = getValidatedInt("Choose slot: ", 1, 3);
                RouteManager::TimeSlot slot;
                switch (slotChoice)
                {
                case 1:
                    slot = RouteManager::TimeSlot::Morning;
                    break;

                case 2:
                    slot = RouteManager::TimeSlot::Afternoon;
                    break;

                case 3:
                    slot = RouteManager::TimeSlot::Evening;
                    break;
                }
                auto flights = routeManager.getFlightOptionsByTime(source,destination,slot,date,system);
                if (flights.empty())
                {
                    std::cout << "No flights found.\n";
                    continue;
                }
                for (const auto &flight : flights)
                {
                    std::cout << "\nFlight ID: "
                              << flight.getFlightId()
                              << " | Time: "
                              << flight.getTime()
                              << " | Vacancies: "
                              << flight.getVacancies()
                              << "\n";
                }
                std::string flightId;
                std::cout << "Enter Flight ID: ";
                std::cin >> flightId;
                Flight *target = system.findFlight(flightId);
                if (!target)
                {
                    std::cout << "Flight not found.\n";
                    continue;
                }
                target->displaySeats();
                std::string name;
                int age;
                char gender;
                int row;
                std::cout << "Enter Name: ";
                std::cin >> name;
                age = getValidatedInt("Enter Age: ", 1, 120);
                gender = getValidatedChar("Enter Gender(M/F): ", "MF");
                row = getValidatedInt("Enter Row: ",1,target->getTotalRows());
                std::string validCols;
                for (int i = 0; i < target->getTotalCols(); i++)
                {
                    validCols += char('A' + i);
                }
                char colChar = getValidatedChar(
                    "Enter Column: ",
                    validCols);
                int col = std::toupper(colChar) - 'A';
                Passenger passenger(name, passport, age, gender);
                if (system.bookTicket(flightId, passenger, row - 1, col))
                {
                    std::cout << "Booking successful.\n";
                }
                else
                {
                    std::cout << "Booking failed.\n";
                }
                break;
            }
            case 3:
            {
                std::string flightId;
                std::cout << "Enter Flight ID: ";
                std::cin >> flightId;
                system.cancelTicket(flightId, passport);
                std::cout << "Cancellation completed.\n";
                break;
            }

            case 4:
            {
                std::string flightId;
                std::cout << "Enter Flight ID: ";
                std::cin >> flightId;
                Flight *flight = system.findFlight(flightId);
                if (!flight)
                {
                    std::cout << "Flight not found.\n";
                    continue;
                }
                auto seat = system.getPassengerSeat(flightId, passport);
                if (seat.first == -1)
                {
                    std::cout << "Boarding pass unavailable.\n";
                    continue;
                }
                const auto &bookings = system.getBookings();
                if (!bookings.count(flightId))
                {
                    continue;
                }
                for (const auto &passenger : bookings.at(flightId))
                {
                    if (passenger.getPassportNumber() == passport)
                    {
                        boardingPassPrinter.generate(passenger,*flight,seat.first + 1,seat.second);
                        break;
                    }
                }
                break;
            }
            case 5:
            {
                adminView.viewPassengerBookingHistory(passport, system);
                break;
            }
            case 6:
            {
                std::cout << "Logged out.\n";
                p=false;
                break;
            }
            default:
            {
                std::cout << "Invalid Entry\n";
                p=false;
                break;
            }
            }
        }
    }
    BookingStorage::saveFlights(system.getFlights(), flightFile);
    BookingStorage::saveBookings(system.getBookings(), system.getPassengerSeatMap(), bookingFile);
    BookingStorage::savePilots(system.getPilots(), pilotFile);
    BookingStorage::saveHistory(system.getPassengerHistory(), historyFile);

    return 0;
}