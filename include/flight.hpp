#pragma once

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
    Seat();

    Seat(int r, char c);

    bool isAvailable() const;
    double getPrice() const;
    void reserve(const std::string &passport, double seatPrice);
    void freeSeat();

    SeatStatus getStatus() const;

    std::string getPassengerPassport() const;
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
    Flight();
    Flight(const std::string &id, const std::string &pilId, const std::string &s, const std::string &d, const std::string &dt,
           const std::string &t, int r, int c, int fare, double rev);
    bool isSeatAvailable(int row, int col) const;
    double calculateSeatPrice() const;
    bool reserveSeat(int row, int col, const std::string &passport, bool isLoading = false);

    bool freeSeat(int row, int col);

    int getTotalRows() const;

    int getTotalCols() const;

    std::string getPilotId() const;

    std::string getFlightId() const;

    std::string getSource() const;

    std::string getDestination() const;

    std::string getDate() const;

    std::string getTime() const;
    int getBookedSeats() const;

    int getVacancies() const;

    int getBaseFare() const;

    double getOccupancyRate() const;

    double getRevenue() const;

    void displaySeats();
};
