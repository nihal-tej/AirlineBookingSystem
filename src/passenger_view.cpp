#include "passenger_view.hpp"
#include <iostream>
#include <string>
#include <set>
#include "route_manager.hpp"
#include "flight.hpp"
#include "input_utils.hpp"
#include <cctype>
#include "booking_system.hpp"
#include "passenger.hpp"
#include "boarding_pass_printer.hpp"
std::set<std::string> cities={"del","mum","che","kol","hyd"};
void PassengerView::listFlights(BookingSystem &system)
    {

        const auto&flights = system.getFlights();
        std::string src=getValidatedCity("Enter source city:",cities);
        std::string dest=getValidatedCity("Enter source city:",cities);
        for (const auto &f1 : flights)
        {
            const auto& f = f1.second;
            if(f.getSource()==src && f.getDestination()==dest)
               std::cout << "Flight: " << f.getFlightId() << "|" << f.getSource() << "->" << f.getDestination() << "| Time:" << f.getTime() << "| Price:" << f.getBaseFare() <<"| Vacancies:" << f.getVacancies() <<std::endl;
        }
    }
void PassengerView::bookTicket(BookingSystem& system,
    RouteManager& routeManager,
    const std::string& passport)
{
    
                std::string date;
                std::string source=getValidatedCity("Enter source city:",cities);
        std::string destination=getValidatedCity("Enter destination city:",cities);
        
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
                    return ;
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
                std::cout << "Enter Flight ID for booking: ";
                std::cin >> flightId;
                Flight *target = system.findFlight(flightId);
                if (!target)
                {
                    std::cout << "Flight not found.\n";
                    return ;
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
                char colChar = getValidatedChar("Enter Column: ",validCols);
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
}
void PassengerView::cancelTicket(BookingSystem& system,const std::string &passport)
{
    std::string flightId;
                std::cout << "Enter Flight ID: ";
                std::cin >> flightId;
                system.cancelTicket(flightId, passport);
                }
void PassengerView::generateBoardingPass(BookingSystem& system,const std::string &passport,BoardingPassPrinter &boardingpassprinter)
{
    std::string flightId;
                std::cout << "Enter Flight ID: ";
                std::cin >> flightId;
                Flight *flight = system.findFlight(flightId);
                if (!flight)
                {
                    std::cout << "Flight not found.\n";
                    return;
                }
                auto seat = system.getPassengerSeat(flightId, passport);
                if (seat.first == -1)
                {
                    std::cout << "Boarding pass unavailable.\n";
                    return;
                }
                const auto &bookings = system.getBookings();
                if (!bookings.count(flightId))
                {
                    return;
                }
                for (const auto &passenger : bookings.at(flightId))
                {
                    if (passenger.getPassportNumber() == passport)
                    {
                        boardingpassprinter.generate(passenger,*flight,seat.first + 1,seat.second);
                        break;
                    }
                }
}
void PassengerView::viewPassengerBookingHistory(const std::string& passport, const BookingSystem &system) const
    {
        const auto& passhis = system.getPassengerHistory();
        auto it = passhis.find(passport);
        if (it == passhis.end())
        {
            std::cout << "No Past Travel history Found" << std::endl;
            return;
        }
        for (const auto &b : it->second)
        {
            std::cout << b.flightId << " at " << b.bookingTime << " status " << b.status << std::endl;
        }
    }