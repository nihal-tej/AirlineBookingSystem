# ✈️ AirlineBookingSystem

A **C++ console-based Airline Booking System** implementing a real-world airline reservation workflow with **Admin, Pilot, and Passenger roles**.  
The project demonstrates **Object-Oriented Programming, STL usage, file handling, and role-based access control**.

---

## 🚀 Features

### 👤 Role-Based Login
- **Admin**
- **Pilot**
- **Passenger**

---

### 🛠 Admin Panel
- Add new flights
- Add pilots
- View all system data
- Persistent storage of:
  - Flights
  - Pilots
  - Bookings

---

### 🧍 Passenger Services
- Login using **passport number**
- Search flights by:
  - Source
  - Destination
  - Date
  - Time slot (Morning / Afternoon / Evening)
- View available seats (seat matrix)
- Select seat and book ticket
- Cancel ticket
- View booking history
- Generate boarding pass

---

### 👨‍✈️ Pilot Panel
- Secure login using **Pilot ID & password**
- View assigned flight schedules by date
- See route and timing details

---

### ✈️ Flight Management
- Seat-wise booking (Row & Column)
- Real-time vacancy tracking
- Dynamic pricing based on occupancy rate

---

### 💾 Persistent Storage (File Handling)
Data is stored and loaded automatically using text files:
- `flights.txt`
- `pilots.txt`
- `bookings.txt`

---

## 🧱 Project Structure

