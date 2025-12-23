#include "booking_system.h"
#include "flight.h"
#include "passenger.h"
#include "route_manager.h"
#include "admin.h"
#include "boardingpass.h"
#include "login_man.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

void clearInputStream()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValidatedInt(string prompt, int min = INT_MIN, int max = INT_MAX)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max)
        {
            cout << "Invalid input. Enter a valid number";
            if (min != INT_MIN && max != INT_MAX)
                cout << " between " << min << " and " << max;
            cout << ".\n";
            clearInputStream();
        }
        else
        {
            clearInputStream();
            return value;
        }
    }
}

char getValidatedChar(string prompt, string validChars)
{
    char ch;
    while (true)
    {
        cout << prompt;
        cin >> ch;
        ch = toupper(ch);

        if (validChars.find(ch) != string::npos)
        {
            clearInputStream();
            return ch;
        }

        cout << "Invalid input. Enter one of: " << validChars << "\n";
        clearInputStream();
    }
}

string getValidatedid()
{
    string id;
    while (true)
    {
        cout << "Enter id Number (12-digit number): ";
        cin >> id;

        if (id.size() != 12)
        {
            cout << "Invalid id. Must be 12 digits.\n";
            clearInputStream();
        }
        else
        {
            return id;
        }
    }
}

int main()
{
    printf("Welcome to the Domestic Airline Booking System.");

    BookingSystem S;
    RouteManager R;
    string passport_num;
    int loginChoice;
    LoginManager L;
    string fli = "flights.txt",
           boo = "bookings.txt", pil = "pilots.txt";
    S.load_pilots(pil);
    S.load_Flights(fli);
    S.load_Data(boo);

    cout << "Login as:\n1. Admin\n2. Pilot\n3. Passenger\nEnter choice (1 or 2 or 3): ";
    cin >> loginChoice;
    clearInputStream();

    // ADMIN LOGIN
    if (loginChoice == 1)
    {
        if (!L.loginAsAdmin())
        {
            cout << "Admin login failed. Exiting." << endl;
            return 0;
        }

        // cout << "Admin login successful." << endl;

        Admin A;

        A.showMenu(S);
        S.save_Data(boo);
        S.save_Flights(fli);
        S.save_Pilots(pil);
        return 0;
    }
    // Pilot login
    else if (loginChoice == 2)
    {

        string pilot_id;
        cout << "Enter the pilot Id:";
        cin>>pilot_id;
        cout << S.num_pilots() << endl;
        if (!L.loginAspilot(pilot_id, S))
        {
            cout << "Pilot login failed. Exiting." << endl;
            return 0;
        }
       S.save_Pilots(pil);
        return 0;
    }
    // PASSENGER LOGIN
    else if (loginChoice == 3)
    {
        cout << "Enter passport Number: ";
        cin >> passport_num;
        if (!L.loginAsPassenger(passport_num))
        {
            cout << "Passenger login failed. Exiting." << endl;
            return 0;
        }
        cout << "Passenger login successful.\n";
        // cout << "Passenger login successful.\n";

        // Passenger Input
        string src,
            dst,
            date;
        int slotChoice;
        cout << "Total flights loaded = " << S.getFlights().size() << endl;

        cout << "Enter Source City: ";
        cin >> src;

        cout << "Enter Destination City: ";
        cin >> dst;

        cout << "Enter Date (YYYY-MM-DD): ";
        cin >> date;

        cout << "Select Time Slot:\n";
        cout << "1. Morning\n2. Afternoon\n3. Evening\nChoice: ";
        cin >> slotChoice;

        RouteManager::TimeSlot slot;

        if (slotChoice == 1)
            slot = RouteManager::Morning;
        else if (slotChoice == 2)
            slot = RouteManager::Afternoon;
        else
            slot = RouteManager::Evening;

        string src_normalized = RouteManager::normalize(src);
        string dst_normalized = RouteManager::normalize(dst);
        auto available_flights = R.getFlightOptionsByTime(src_normalized, dst_normalized, slot, date, S);

        if (available_flights.empty())
        {
            cout << "No flight times found for that route and time slot.\n";
            return 0;
        }
        cout << "\nAvailable Flights from " << src << " to " << dst << " on " << date << " (Time Slot: " << slot << "):\n\n";

        int flight_count = 0;
        for (auto &f : available_flights)
        {
            // FOUND THE FLIGHT: Output the requested details!
            cout << "[" << ++flight_count << "] ";
            cout << "Flight ID: " << f.getFlightID()
                 << " | Time: " << f.getTime()
                 << " | Vacancies: " << f.getvacancies()
                 << " | price Flight: Rs." << f.getBaseFare() * (1 + f.getOccupancyRate()) << "\n";
        }

        if (flight_count == 0)
        {
            cout << "No matching flights found in loaded data for the selected date and time slot.\n";
            return 0;
        }
        // MAIN MENU LOOP
        while (true)
        {
            cout << "\n--- MAIN MENU ---\n";
            cout << "1. View Flights\n";
            cout << "2. Book Ticket\n";
            cout << "3. Cancel Ticket\n";
            cout << "4. View Booking History\n";
            cout << "5. Generate Boarding Pass\n";
            cout << "6. Logout\n";

            int choice = getValidatedInt("Enter your choice (1-6): ", 1, 6);

            // === OPTION 1 ===
            if (choice == 1)
            {
                S.listFlights();
                continue;
            }

            // === OPTION 2: BOOKING ===
            else if (choice == 2)
            {
                string flightID;
                cout << "Enter Flight ID: ";
                cin >> flightID;

                Flight *f = S.findFlight(flightID);
                if (!f)
                {
                    cout << "Flight not found.\n";
                    continue;
                }

                f->displaySeats();

                string tempName;
                int tempAge;
                char tempGender;
                int tempRow;
                char tempColChar;
                while (true)
                {
                    cout << "Enter Passenger Name: ";
                    cin >> tempName;
                    tempAge = getValidatedInt("Enter Age: ", 1, 120);
                    tempGender = getValidatedChar("Enter Gender (M/F): ", "MF");
                    tempRow = getValidatedInt("Enter Seat Row (1-40): ", 1, 40);
                    tempColChar = getValidatedChar("Enter Seat Column (A-F): ", "ABCDEF");

                    string confirm;
                    cout << "You entered:\n";
                    cout << "  Name: " << tempName << "\n";
                    cout << "  Age: " << tempAge << "\n";
                    cout << "  Gender: " << tempGender << "\n";
                    cout << "  Seat: " << tempRow << tempColChar << "\n";
                    cout << "Confirm booking? (yes/back): ";
                    cin >> confirm;

                    if (confirm == "yes")
                        break;
                    cout << "Re-enter your details.\n";
                }

                int tempCol = toupper(tempColChar) - 'A';

                if (!f->isSeatAvailable(tempRow - 1, tempCol))
                {
                    cout << "Seat already booked.\n";
                    continue;
                }

                Passenger p(tempName, passport_num, tempAge, tempGender);

                if (S.bookTicket(flightID, p, tempRow - 1, tempCol))
                {
                    cout << "Booking successful.\n";
                }
                else
                {
                    cout << "Booking failed.\n";
                }
                continue;
            }

            // === OPTION 3: CANCEL ===
            else if (choice == 3)
            {
                string flightID;
                cout << "Enter Flight ID to cancel: ";
                cin >> flightID;

                string confirm;
                cout << "Confirm cancellation? (yes/no): ";
                cin >> confirm;

                if (confirm != "yes")
                {
                    cout << "Cancelled.\n";
                    continue;
                }

                S.cancelTicket(flightID, passport_num);
            }

            // === OPTION 4: HISTORY ===
            else if (choice == 4)
            {
                S.viewPassengerHistory(passport_num);
            }

            // === OPTION 5: BOARDING PASS ===
            else if (choice == 5)
            {
                string flightID;
                cout << "Enter Flight ID: ";
                cin >> flightID;
                Flight *f = S.findFlight(flightID);
                if (!f)
                {
                    cout << "Flight not found.\n";
                    continue;
                }

                auto seat = S.getPassengerSeat(flightID, passport_num);
                if (seat.first == -1)
                {
                    cout << "No boarding pass found.\n";
                    continue;
                }
                auto all = S.getBookings();
                if (!all.count(flightID))
                {
                    cout << "No bookings for that flight\n";
                    continue;
                }
                auto bookings = all.at(flightID);
                for (auto p : bookings)
                {
                    if (p.getPassportNumber() == passport_num)
                    {
                        BoardingPass B;
                        B.generate(p, *f, seat.first, seat.second);
                        break;
                    }
                }
            }

            // === OPTION 6: LOGOUT ===
            else if (choice == 6)
            {
                cout << "Logged out. Goodbye!\n";
                S.save_Flights(fli);
                S.save_Data(boo);
                S.save_Pilots(pil);
                break;
            }
        }
    }
    return 0;
}