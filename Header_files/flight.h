#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

enum class SeatStatus
{
    Free,
    Booked
};
class Seat
{
    int row;
    char col;
    SeatStatus status;
    double price;
    std::string passengerPassport;
public:
    Seat()
    {
        row = 0;
        col = 'A';
        status = SeatStatus::Free;
        price = 0;
    }
    Seat(int r, char c)
    {
        row = r;
        col = c;
        status = SeatStatus::Free;
        price = 0;
    }
    bool isAvailable() const
    {
        return status == SeatStatus::Free;
    }
    void reserve(const std::string &passport, double seatPrice)
    {
        status = SeatStatus::Booked;
        passengerPassport = passport;
        price = seatPrice;
    }
    void freeSeat()
    {
        status = SeatStatus::Free;
        passengerPassport = "";
        price = 0;
    }
    double getPrice() const
    {
        return price;
    }
    SeatStatus getStatus() const
    {
        return status;
    }
    std::string getPassengerPassport() const
    {
        return passengerPassport;
    }
};

class Flight
{
    std::string flightId;
    std::string pilotId;
    std::string src;
    std::string dest;
    std::string date;
    std::string time;
    int rows;
    int cols;
    int totalSeats;
    int bookedSeats;
    int baseFare;
    double revenue;
    std::vector<std::vector<Seat>> seats;

public:
    Flight()
    {
        flightId="";
        pilotId="";
        src="";
        dest="";
        date="";
        time="";
        rows = 0;
        cols = 0;
        totalSeats = 0;
        bookedSeats = 0;
        baseFare = 0;
        revenue = 0;
    }
    Flight(const std::string &id,const std::string &pilId,const std::string &s,const std::string &d,const std::string &dt,
           const std::string &t,int r,int c,int fare,double rev)
    {
        if (r <= 0 || c <= 0)
            throw std::invalid_argument("Rows/Cols must be positive");
        if (fare < 0)
            throw std::invalid_argument("Base fare cannot be negative");
        flightId = id;
        pilotId = pilId;
        src = s;
        dest = d;
        date = dt;
        time = t;
        rows = r;
        cols = c;
        baseFare = fare;
        revenue = rev;
        totalSeats = rows * cols;
        bookedSeats = 0;
        seats.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                seats[i].push_back(Seat(i + 1, 'A' + j));
            }
        }
    }
    bool isSeatAvailable(int row, int col) const
    {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            return false;
        return seats[row][col].isAvailable();
    }
    double calculateSeatPrice() const
    {
        double occupancy = getOccupancyRate();
        return baseFare * (1.0 + occupancy);
    }
    bool reserveSeat(int row,int col, const std::string &passport,bool isLoading = false)
    {
        if (!isSeatAvailable(row, col))
            return false;
        double currentPrice = calculateSeatPrice();
        seats[row][col].reserve(passport, currentPrice);
        bookedSeats++;
        if (!isLoading)
            revenue += currentPrice;
        return true;
    }

    bool freeSeat(int row, int col)
    {
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            return false;
        if (seats[row][col].isAvailable())
            return false;
        revenue -= seats[row][col].getPrice();
        seats[row][col].freeSeat();
        bookedSeats--;
        return true;
    }
   
    int getTotalRows() const
    {
        return rows;
    }

    int getTotalCols() const
    {
        return cols;
    }

    std::string getPilotId() const
    {
        return pilotId;
    }

    std::string getFlightId() const
    {
        return flightId;
    }

    std::string getSource() const
    {
        return src;
    }

    std::string getDestination() const
    {
        return dest;
    }

    std::string getDate() const
    {
        return date;
    }

    std::string getTime() const
    {
        return time;
    }

    int getBookedSeats() const
    {
        return bookedSeats;
    }

    int getVacancies() const
    {
        return totalSeats - bookedSeats;
    }

    int getBaseFare() const
    {
        return baseFare;
    }

    double getOccupancyRate() const
    {
        if (totalSeats == 0)
            return 0.0;

        return 1.0 * bookedSeats / totalSeats;
    }

    double getRevenue() const
    {
        return revenue;
    }
   
    void displaySeats()
    {
        std::cout << "\nSeat Layout (0 = Free, 1 = Booked)\n\n   ";
        for (int j = 0; j < cols; j++)
            std::cout << char('A' + j) << " ";
        std::cout << "\n";
        for (int i = 0; i < rows; ++i)
        {
            std::cout << (i + 1) << " ";

            for (int j = 0; j < cols; ++j)
            {
                std::cout << (seats[i][j].isAvailable() ? 0 : 1) << " ";
            }

            std::cout << "\n";
        }
    }
};

#endif