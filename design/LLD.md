# Airline Booking System - Low Level Design (LLD)

---

# 1. Introduction

## Purpose

This document describes the Low-Level Design (LLD) of the Airline Booking System. It explains the internal implementation of the system, class responsibilities, object relationships, data structures, algorithms, and major workflows.

Unlike the High-Level Design (HLD), which focuses on the overall architecture, this document describes how the application is implemented at the class and component level.

---

# 2. Design Goals

The system is designed with the following goals:

- Follow Object-Oriented Programming principles.
- Separate presentation, business logic, persistence, and utility modules.
- Promote modularity and maintainability.
- Reduce coupling between components.
- Improve code reusability.
- Support future scalability.

---

# 3. Class Overview

The system consists of the following classes.

| Class | Responsibility |
|--------|---------------|
| BookingSystem | Core business logic |
| Flight | Stores flight information |
| Seat | Represents individual seats |
| Passenger | Stores passenger information |
| Pilot | Stores pilot information |
| BookingStorage | File persistence |
| RouteManager | Flight searching |
| LoginManager | Authentication |
| AdminView | Administrator interface |
| PassengerView | Passenger interface |
| PilotView | Pilot interface |
| BoardingPassPrinter | Boarding pass generation |
| TimeUtils | Timestamp generation |
| InputUtils | Input validation |

---

# 4. Class Details

---

# BookingSystem

## Responsibility

Acts as the central business layer responsible for managing the complete airline booking process.

## Attributes

- flights
- bookings
- bookedPassports
- passengerSeatMap
- passengerHistory
- pilots
- pilotFlights
- pilotData
- pilotIds

## Public Methods

### Flight Management

- addFlight()
- removeFlight()
- findFlight()

### Pilot Management

- addPilot()
- removePilot()
- checkPilot()

### Passenger Management

- findPassenger()
- getPassengerSeat()

### Ticket Management

- bookTicket()
- cancelTicket()

### Getter Functions

- getFlights()
- getBookings()
- getPassengerHistory()
- getPilotSchedule()
- getPassengerSeatMap()

## Collaborating Classes

- Flight
- Passenger
- Pilot
- BookingStorage
- TimeUtils

---

# Flight

## Responsibility

Represents an airline flight.

## Attributes

- Flight ID
- Pilot ID
- Source
- Destination
- Date
- Time
- Total Rows
- Total Columns
- Base Fare
- Revenue
- Seats

## Public Methods

- reserveSeat()
- freeSeat()
- isSeatAvailable()
- calculateSeatPrice()
- displaySeats()

---

# Seat

## Responsibility

Represents an individual seat.

## Attributes

- Row
- Column
- Seat Status
- Price
- Passenger Passport

## Public Methods

- reserve()
- freeSeat()
- isAvailable()
- getPrice()
- getStatus()

---

# Passenger

## Responsibility

Stores passenger information.

## Attributes

- Name
- Passport Number
- Age
- Gender

## Public Methods

Getter methods only.

---

# Pilot

## Responsibility

Stores pilot information.

## Attributes

- Pilot ID
- Name
- Passport Number
- Age
- Gender
- Password

## Public Methods

Getter methods only.

---

# RouteManager

## Responsibility

Searches flights according to passenger requirements.

## Supported Filters

- Source
- Destination
- Date
- Morning Flights
- Afternoon Flights
- Evening Flights

## Public Methods

- getFlightOptionsByTime()

---

# BookingStorage

## Responsibility

Stores application data into text files and restores it during application startup.

## Files Managed

- flights.txt
- bookings.txt
- pilots.txt
- bookinghistory.txt

## Public Methods

### Flights

- saveFlights()
- loadFlights()

### Bookings

- saveBookings()
- loadBookings()

### Pilots

- savePilots()
- loadPilots()

### Booking History

- saveHistory()
- loadHistory()

---

# LoginManager

## Responsibility

Provides authentication for all users.

## Public Methods

- loginAsAdmin()
- loginAsPilot()
- loginAsPassenger()

---

# AdminView

## Responsibility

Provides administrator operations.

## Features

- Add Flight
- Remove Flight
- Add Pilot
- Remove Pilot
- View Flight Statistics
- View Occupancy
- View Revenue
- View All Bookings
- View Pilot Details

---

# PassengerView

## Responsibility

Provides passenger operations.

## Features

- View Flights
- Search Flights
- Book Ticket
- Cancel Ticket
- Generate Boarding Pass
- View Booking History

---

# PilotView

## Responsibility

Provides pilot operations.

## Features

- View Personal Details
- View Assigned Schedule

---

# BoardingPassPrinter

## Responsibility

Generates formatted boarding passes for confirmed bookings.

## Public Methods

- generate()

---

# TimeUtils

## Responsibility

Generates current timestamps used in booking history.

## Public Methods

- getCurrentTime()

---

# InputUtils

## Responsibility

Provides validated console input.

## Public Methods

- clearInputStream()
- getValidatedInt()
- getValidatedChar()
- getValidatedString()

---

# 5. Relationships

## BookingSystem

Aggregates

- Flight
- Passenger
- Pilot

Uses

- BookingStorage
- TimeUtils

---

## Flight

Composes

- Seat

---

## PassengerView

Uses

- BookingSystem
- RouteManager
- BoardingPassPrinter

---

## AdminView

Uses

- BookingSystem

---

## PilotView

Uses

- BookingSystem

---

## LoginManager

Provides authentication before granting access to

- AdminView
- PassengerView
- PilotView

---

## BookingStorage

Stores data managed by BookingSystem.

---

# 6. Data Structures

| Data Structure | Purpose |
|---------------|---------|
| unordered_map | Flight lookup, Pilot lookup, Seat mapping |
| map | Booking history, Passenger bookings |
| unordered_set | Prevent duplicate passenger bookings |
| vector | Seat storage, Passenger lists |
| pair | Seat coordinates |
| tuple | Pilot schedule |

---

# 7. Major Algorithms

## Flight Search

Input

- Source
- Destination
- Date
- Time Slot

Process

- Traverse flights
- Match source
- Match destination
- Match date
- Match time slot

Output

Available flights

Complexity

O(F), F-->Number of flights

---

## Ticket Booking

Steps

1. Find Flight
2. Verify Seat Availability
3. Reserve Seat
4. Store Passenger
5. Update Seat Map
6. Update Booking History

Complexity

O(1) average, All are unordered_maps

---

## Ticket Cancellation

Steps

1. Locate Flight
2. Find Passenger
3. Release Seat
4. Remove Booking
5. Update Booking History

Complexity

O(P),P--->number of Passengers in flight

---

## Boarding Pass Generation

Steps

1. Find Flight
2. Find Passenger
3. Get Seat Number
4. Generate Boarding Pass

Complexity

O(P), In a flight we need traverse all passenger ,verify then generate Boarding pass

---

## Load Data

Application Startup

```
Load Pilots

↓

Load Flights

↓

Load Bookings

↓

Load History
```

---

## Save Data

Application Exit

```
Save Flights

↓

Save Bookings

↓

Save Pilots

↓

Save History
```

---

# 8. Sequence Flow

## Login

```
User

↓

LoginManager

↓

Authentication

↓

Corresponding View
```

---

## Booking Ticket

```
Passenger

↓

PassengerView

↓

RouteManager

↓

BookingSystem

↓

Flight

↓

Seat

↓

BookingStorage
```

---

## Cancel Ticket

```
Passenger

↓

PassengerView

↓

BookingSystem

↓

Flight

↓

Seat

↓

BookingStorage
```

---

## Add Flight

```
Administrator

↓

AdminView

↓

BookingSystem

↓

Flight

↓

BookingStorage
```

---

## Generate Boarding Pass

```
Passenger

↓

PassengerView

↓

BookingSystem

↓

BoardingPassPrinter
```

---

# 9. Error Handling

The system handles the following scenarios.

- Invalid Login
- Flight Not Found
- Pilot Not Found
- Passenger Not Found
- Seat Already Reserved
- Invalid Seat Number
- Duplicate Booking
- Missing Data Files
- Invalid User Input
- Improper ticket cancellation

---

# 10. Design Decisions

## Why BookingSystem?

Acts as the single business layer to avoid duplicating business logic across multiple views.

---

## Why BookingStorage?

Separates persistence from business logic.

---

## Why RouteManager?

Separates searching logic from booking logic.

---

## Why View Classes?

Each actor has an independent user interface.

- AdminView
- PassengerView
- PilotView

This improves modularity and maintainability and also Readability.

---

## Why Utility Classes?

Utility classes avoid duplicate code.

- TimeUtils
- InputUtils

---

# 11. Time Complexity

| Operation | Complexity |
|------------|------------|
| Find Flight | O(1) Average |
| Add Flight | O(1) Average |
| Remove Flight | O(1) Average |
| Book Ticket | O(1) Average |
| Cancel Ticket | O(P) |
| Search Flights | O(F) |
| Generate Boarding Pass | O(P) |
| Save Data | O(N) |
| Load Data | O(N) |

Where

- F = Number of Flights
- P = Number of Passengers in a Flight
- N = Total Records

---

# 12. Object-Oriented Principles

The project follows:

- Encapsulation
- Abstraction
- Modularity
- Single Responsibility Principle (SRP)
- Separation of Concerns
- High Cohesion
- Low Coupling

---

# 13. Future Improvements

- Database Integration (MySQL/PostgreSQL)
- Repository Pattern
- Service Layer
- Payment Gateway
- Flight Rescheduling
- Dynamic Seat Pricing
- Email Notifications
- REST APIs
- GUI/Desktop Application
- Web Application
- Concurrent Booking Support
- Unit Testing
- Logging Framework