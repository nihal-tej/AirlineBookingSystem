#ifndef FLIGHT_H
#define FLIGHT_H

#include <bits/stdc++.h>
using namespace std;

class Flight
{
    string flightId;
    string src, dest;
    string date, time;
    int rows, cols;
    int tot_seats;
    int booked_seats, num_vacancies;
    int basefare;
    double revenue;
    vector<vector<int>> seats; // 0 = free, 1 = booked
    vector<vector<double>> price;
    string pilotid;

public:
    Flight(string &id, string &pilid, string &s, string &d, string &dt, string &t, int &r, int &c, int &f, double &rev)
    {
        this->flightId = id;
        this->pilotid = pilid;
        this->src = s;
        this->dest = d;
        this->date = dt;
        this->time = t;
        this->rows = r;
        this->cols = c;
        this->basefare = f;
        this->revenue = rev;
        this->tot_seats = r * c;
        this->booked_seats = 0;
        this->num_vacancies = tot_seats;

        this->seats = vector<vector<int>>(rows, vector<int>(cols, 0));
        this->price = vector<vector<double>>(rows, vector<double>(cols, 0));
    }

    // -----------------------------------
    // Display seats
    // ---------------------------------
    void displaySeats() const
    {
        cout << "\nSeat Layout (0 = Free, 1 = Booked)\n\n   ";

        for (int j = 0; j < cols; j++)
            cout << char('A' + j) << " ";
        cout << "\n";

        for (int i = 0; i < rows; ++i)
        {
            cout << (i + 1) << " ";
            for (int j = 0; j < cols; ++j)
                cout << seats[i][j] << " ";
            cout << "\n";
        }
    }

    // -----------------------------------
    bool isSeatAvailable(int row, int col) const
    {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            return false;
        return seats[row][col] == 0;
    }

    // -----------------------------------
    void bookSeat(int row, int col, int y)
    {
        if (!isSeatAvailable(row, col))
            return;
        booked_seats++;
        num_vacancies--;
        seats[row][col] = 1;

        // Correct occupancy (0 to 1 scale)
        double occ = (double)booked_seats / tot_seats;
        price[row][col] = basefare * (1.0 + occ);
        if (y)
        {
            // add to revenue only when ticket booking ,not when loading of data
            revenue += price[row][col];
        }
        cout << price[row][col] << endl;
    }

    // -----------------------------------
    void freeSeat(int row, int col)
    {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            return;
        if (seats[row][col] == 1)
        {
            seats[row][col] = 0;
            revenue -= price[row][col];
            price[row][col] = 0;
            booked_seats--;
            num_vacancies++;
        }
    }

    // -----------------------------------
    int getTotalRows() const { return rows; }
    int getTotalCols() const { return cols; }
    string getPilotId() const
    {
        return pilotid;
    }
    string getFlightID() const { return flightId; } 
    string getSource() const { return src; }        
    string getDestination() const { return dest; }  
    string getdate() const { return date; }         
    string getTime() const { return time; }         

    int getBookedSeats() const { return booked_seats; }
    int getvacancies() const { return num_vacancies; }
    int getBaseFare() const { return basefare; }
    double getOccupancyRate() const
    {
        if (tot_seats == 0)
            return 0.0;
        return (double)booked_seats / tot_seats; 
    }

    double getRevenue() const
    {
        return revenue;
    }
};

#endif
