classDiagram
    %% --- LAYERS SETUP ---
    %% Presentation / Controller
    class Main {
        +main() int
    }
    class AdminView {
        -routeManager: RouteManager*
        -bookingSystem: BookingSystem*
        +showMenu() void
        +addFlightConsole() void
        +viewAllBookings() void
    }
    class PilotView {
        -routeManager: RouteManager*
        +showMenu() void
        +updateFlightStatusConsole() void
    }

    %% Business Logic / Service Managers
    class LoginManager {
        +verifyCredentials(user, pass) bool
        +getCurrentUserRole() string
    }
    class RouteManager {
        -flights: vector<Flight>
        +loadRoutesFromFile() void
        +addFlight(Flight) void
        +getFlights() vector<Flight>
    }
    class BookingSystem {
        -storage: Storage*
        +bookTicket(passengerId, flightId, seatNo) bool
        +cancelTicket(bookingId) bool
    }

    %% Domain Entities / Models
    class Flight {
        +flightId: string
        +source: string
        +destination: string
        +seats: vector<Seat>
        +pilot: Pilot
        +scheduleTime: string
    }
    class Passenger {
        +passengerId: string
        +name: string
        +passportNo: string
        +bookingHistory: vector<string>
    }
    class Pilot {
        +pilotId: string
        +name: string
        +licenseNo: string
        +assignedFlights: vector<string>
    }
    class Seat {
        +seatNo: string
        +isReserved: bool
        +type: string
    }

    %% Infrastructure / Utilities
    class Storage {
        +readData(fileName: string) vector<string>
        +writeData(fileName: string, data: string) void
        +appendData(fileName: string, data: string) void
    }
    class TimeUtil {
        +parseTimeString(timeStr: string) int
        +isOverlapping(time1: string, time2: string) bool
    }
    class BoardingPassPrinter {
        +printTicket(passenger: Passenger, flight: Flight, seat: Seat) void
    }

    %% --- RELATIONSHIPS / DEPENDENCIES ---
    %% Execution flow from Main
    Main --> LoginManager : Uses for Auth
    Main --> AdminView : Spawns if Admin
    Main --> PilotView : Spawns if Pilot

    %% Views driving the Managers
    AdminView --> RouteManager : Calls logic
    AdminView --> BookingSystem : Calls logic
    PilotView --> RouteManager : Updates schedules

    %% Managers driving the Domain
    RouteManager --> Flight : Aggregates/Manages
    BookingSystem --> Flight : Modifies status
    BookingSystem --> Passenger : Registers/Associates
    BookingSystem --> BoardingPassPrinter : Triggers printing

    %% Component compositions
    Flight "1" *-- "*" Seat : Contains
    Flight "1" *-- "1" Pilot : Assigned to

    %% Infrastructure cross-cutting dependencies
    RouteManager ..> Storage : Persists to files
    BookingSystem ..> Storage : Persists to files
    RouteManager ..> TimeUtil : Validates schedule conflicts