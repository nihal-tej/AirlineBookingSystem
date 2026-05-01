#ifndef LOGIN_MAN_H
#define LOGIN_MAN_H
#include <string>
#include <iostream>
#include "admin.h"
#include "booking_system.h"

class LoginManager
{
public:
    // ADMIN LOGIN
    bool loginAsAdmin()
    {
        string password;
        cout << "Enter Admin Password:" << endl;
        cin >> password;

        // simple hardcoded password
        if (password == "admin@123")
        {
            cout << "Admin login successful.\n";
            return true;
        }

        cout << "Invalid admin password.\n";
        return false;
    }
    bool isvalidpilot(const string &pi, BookingSystem &S)
    {
        return S.check_pilot(pi);
    }
    void viewdetails(BookingSystem &system, const string &plid)
    {

        const auto &pilots = system.getpilots();
        if (pilots.count(plid))
        {

            cout << "\nPilot Name:" << pilots.at(plid).getpilotname() << "\n";
            cout << "Passport Number:" << pilots.at(plid).getpilotpassportnumber() << "\n";
            cout << "Age:" << pilots.at(plid).getpilotage() << "\n";
            cout << "Gender:" << pilots.at(plid).getpilotgender() << "\n";
            cout << "---------------------------------------\n";
        }
        else
        {
            cout << "Pilot not found with pilot ID" << plid << endl;
        }
    }
    bool loginAspilot(const string &pilid, BookingSystem &S)
    {
        if (!isvalidpilot(pilid, S))
        {
            cout << "Invalid pilot ID\n";
            return false;
        }

        string password;
        cout << "Enter Pilot Password: ";
        cin >> password;

        if (password == S.getloginpassword(pilid))
        {
            cout << "Pilot login successful.\n";

            while (true)
            {
                cout << "\n============ PILOT PANEL ============\n";
                cout << "1. View assigned flights details (route, time, passengers count)\n";
                cout << "2. Save Data\n";
                cout << "3. pilot information" << endl;
                cout << "4. Exit Pilot Panel\n";
                cout << "Enter choice: ";

                int choice;
                cin >> choice;

                string k = "pilots.txt";

                switch (choice)
                {
                case 1:
                    viewschedule(S, pilid);
                    break;

                case 2:

                    cout << "Data saved.\n";
                    break;
                case 3:

                    viewdetails(S, pilid);
                    break;
                case 4:

                    cout << "Exiting pilot panel.\n";
                    return true;

                default:
                    cout << "Invalid option.\n";
                }
            }
        }

        cout << "Invalid Pilot password.\n";
        return false;
    }
    // PASSENGER LOGIN USING PASSPORT
    bool loginAsPassenger(const string &passport)
    {
        if (!isValidpassport(passport))
        {
            cout << "Invalid passport number!\n";
            return false;
        }
        return true;
    }
    bool isValidpassport(const string &passport)
    {
        if (passport.size() != 12)
            return false;

        for (char c : passport)
            if (!isdigit(c))
                return false;

        return true;
    }
    void viewschedule(BookingSystem &system, const string &pil)
    {
        auto pilots = system.getpilotsch(pil);

        if (pilots.empty())
        {
            cout << "No flights loaded.\n";
            return;
        }
        string st;
        cout << "Enter the schedule on which you want schedule:" << endl;
        cin >> st;
        cout << "Date:" << st << endl;
        int h = 0;
        for (auto &f : pilots)
        {
            if (f.first != st)
                continue;
            vector<pair<string, tuple<string, string, string, string>>> v;
            auto &t = f.second;
            h++;
            cout << "\nFlight: " << get<2>(t) << "\n";
            cout << "Route: " << get<0>(t) << "->" << get<1>(t) << "\n";
            cout << "Time: " << get<3>(t) << "\n";
            cout << "---------------------------------------\n";
        }
        if (h == 0)
            cout << "No schedule on this day" << endl;
    }
};
#endif