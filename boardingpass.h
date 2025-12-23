#include <iostream>
#include <string>
#include "passenger.h"
#include "flight.h"

class BoardingPass
{
public:
    void generate(Passenger &p, const Flight &f, int &row, int &col)
    {
        std::cout << "\n=========================================\n";
        std::cout << "            BOARDING PASS\n";
        std::cout << "=========================================\n";

        std::cout << "Passenger Name : " << p.getName() << "\n";
        std::cout << "Aadhaar        : " << p.getPassportNumber() << "\n";

        std::cout << "\nFlight ID      : " << f.getFlightID() << "\n";
        std::cout << "From           : " << f.getSource() << "\n";
        std::cout << "To             : " << f.getDestination() << "\n";
        std::cout << "Departure Time : " << f.getTime() << "\n";

        std::cout << "\nSeat           : Row " << row << ", Column " << col << "\n";

        std::cout << "=========================================\n";
        std::cout << "         Have a Pleasant Journey!\n";
        std::cout << "=========================================\n\n";
    }
};
