# Airline Booking System - High Level Design (HLD)

## 1. Overview

The Airline Booking System is a console-based application developed using Object-Oriented Programming (OOP) principles in C++. The system allows administrators to manage flights and pilots, passengers to search and book flights, and pilots to view their schedules. All application data is handeled using text files.

The architecture follows a layered, modular design where each component has a single responsibility.
---
## 2.Scope

The Airline Booking System is designed for managing domestic airline operations through a console-based application. It provides separate interfaces for administrators, pilots, and passengers while supporting flight management, ticket booking, cancellation, boarding pass generation, and persistent storage using text files.
---

## 3. Objectives

- Manage flights and pilots.
- Allow passengers to search and book flights.
- Support ticket cancellation.
- Generate boarding passes.
- Maintain booking history.
- Maintain consistency of application data between executions.
---
## 4.Assumptions

- The system is intended for a single-user console environment.
- Data is stored locally using text files.
- Authentication is based on predefined credentials.
- Internet connectivity is not required.
- Concurrent access is not supported,only 1 user and 1 role can be accessed once.
---

# 5. Actors

## Administrator

- Login
- Add Flight
- Remove Flight
- Add Pilot
- Remove Pilot
- View Flight Statistics
- View Bookings
- View Pilot Details

---

## Pilot

- Login
- View Assigned Schedule
- View Personal Details

---

## Passenger

- Login
- Search Flights
- Book Ticket
- Cancel Ticket
- Generate Boarding Pass
- View Booking History

---

# 6. System Architecture

                        +----------------------+
                        |       main.cpp       |
                        |                      |
                        +----------+-----------+
                                   |
                                   |
                        +----------V-----------+  
                        |    LoginManager      |  
                        |                      |   
                        +----------+-----------+  
                                   |                  
                            +------V------+           
                            | InputUtils  |
                            |             |
                            +-------------+
                                   |                                          
          +------------------------V-------------------------+
          |                        |                         |
          |                        |                         |
 +--------V---------+     +--------V---------+     +---------V--------+
 |    AdminView     |     |   PilotView      |     |  PassengerView   |
 |                  |     |                  |     |                  |
 +--------+---------+     +--------+---------+     +--------+---------+
          |                        |                        |
          +------------------------+------------------------+
                                              |
                                              |
                +-----------+       +---------V----------------+   
                | TimeUtils |       |      BookingSystem       |   
                +-----------+       +--------------------------+   
                    |                        |         |       
                    +------------------------+         +-----------------------------------+
                                 |                                      |                  |
                                 |                                 +----V------+    +------V----+
                                 |                                 | Passenger |    |   Pilot   |
               +-------------------------------------+             +-----------+    +-----------+
               |                                     |                   |
               |                                     |                   |
      +--------V---------+              +------------V----+         +----V-----------------+
      |  RouteManager    |              | BookingStorage  |         | BoardingPassPrinter  |
      +------------------+              +-----------------+         +----------------------+
               |                                   |
      +--------+                         +---------+
      |                                  |                  
      v                                  |
+-----------+                     +------V---------+ 
|  Flight   |                     |   Text files   |
+-----------+                     |                |
      |                           +----------------+
+-----V-----+
|   Seat    |
+-----------+
---
## 7.System Layers

### Presentation Layer

- AdminView
- PassengerView
- PilotView

### Business Layer

- BookingSystem
- RouteManager
- LoginManager

### Persistence Layer

- BookingStorage

### Domain Layer

- Flight
- Seat
- Passenger
- Pilot

### Utility Layer

- TimeUtils
- InputUtils
- BoardingPassPrinter

---

# 8. Module Description

## BookingSystem

### Responsibility

Acts as the central business logic of the application.

### Handles

- Flight Management
- Pilot Management
- Ticket Booking
- Ticket Cancellation
- Passenger History
- Seat Allocation

---

## Flight

### Responsibility

Represents an airline flight.

### Maintains

- Flight Details
- Seat Layout
- Seat Availability
- Revenue
- Occupancy

---

## Seat

### Responsibility

Represents a seat inside a flight.

### Maintains

- Seat Number
- Booking Status
- Passenger Passport
- Seat Price

---

## Passenger

### Responsibility

Stores passenger information.

### Maintains

- Name
- Passport Number
- Age
- Gender

---

## Pilot

### Responsibility

Stores pilot information.

### Maintains

- Pilot ID
- Personal Details
- Login Credentials

---

## BookingStorage

### Responsibility

Provides persistent storage for the application.

### Operations

- Save Flights
- Load Flights
- Save Pilots
- Load Pilots
- Save Bookings
- Load Bookings
- Save Booking History
- Load Booking History

---

## LoginManager

### Responsibility

Authenticates users.

### Supports

- Admin Login
- Pilot Login
- Passenger Login

---

## RouteManager

### Responsibility

Provides flight search functionality.

### Supports

- Search by Source
- Search by Destination
- Search by Date
- Filter by Time Slot

---

## AdminView

### Responsibility

Provides administrator interface.

### Supports

- Flight Statistics
- Booking Reports
- Pilot Management
- Flight Management

---

## PilotView

### Responsibility

Provides pilot interface.

### Supports

- View Schedule
- View Personal Details

---

## BoardingPassPrinter

### Responsibility

Generates formatted boarding passes.

---

## TimeUtils

### Responsibility

Provides current timestamp generation for booking history.

---

# 9. Data Storage

The application stores persistent data using text files.

| File               | Description                                 |
| ------------------ | ------------------------------------------- |
| flights.txt        | Stores flight details and configuration     |
| bookings.txt       | Stores booking records with seat allocation |
| pilots.txt         | Stores pilot information                    |
| bookinghistory.txt | Stores booking and cancellation history     |



---
# 10. Major Workflows

## Passenger Booking

```
Passenger
    │
    ▼
Search Flights
    │
    ▼
Route Manager
    │
    ▼
Booking System
    │
    ▼
Flight
    │
    ▼
Seat Reservation
    │
    ▼
Booking Storage
```

---

## Ticket Cancellation

```
Passenger
    │
    ▼
Booking System
    │
    ▼
Flight
    │
    ▼
Release Seat
    │
    ▼
Update Booking History
    │
    ▼
Booking Storage
```

---

## Add Flight

```
Administrator
    │
    ▼
Admin View
    │
    ▼
Booking System
    │
    ▼
Flight Object
    │
    ▼
Booking Storage
```

---

## Pilot Login

```
Pilot
    │
    ▼
Login Manager
    │
    ▼
Booking System
    │
    ▼
Pilot View
```

---

# 11. Component Interaction

```
AdminView
     │
     ▼
BookingSystem
     │
     ├──────────── Flight
     │
     ├──────────── Passenger
     │
     ├──────────── Pilot
     │
     ├──────────── BookingStorage
     │
     ├──────────── RouteManager
     │
     └──────────── TimeUtils
```

---

# 12. Design Principles

The system follows several object-oriented design principles:

### Single Responsibility Principle

Each class performs one well-defined task, such as BookingStorage handling persistence and RouteManager handling flight search.

### Encapsulation

All business data is encapsulated within domain classes and accessed through public interfaces.
---
## 13. Limitations

- Text-file storage is not suitable for large datasets.
- No concurrent booking support.
- Console interface only.
- No payment processing.
- No network-based authentication.
---

# 14. Future Enhancements

- Replace text-file storage with MySQL or PostgreSQL.
- Introduce Repository and Service layers.
- Add payment gateway integration.
- Implement seat classes (Economy, Business, First Class).
- Add multi-city and connecting flights.
- Build a GUI or web application.
- Add REST APIs for external integration.
- Support concurrent bookings with proper synchronization.

---

# 15. Technologies Used

- C++17
- Object-Oriented Programming
- STL Containers
- File Handling
- Modular Project Structure (.hpp/.cpp)
