# Railway Reservation System in C++

## Project Overview

This is a simple Railway Reservation System developed using C++.  
The project demonstrates the concepts of:

- Object Oriented Programming (OOP)
- File Handling using Binary Files
- Classes and Objects
- Reservation Management System

The system allows users to:

- Add train records
- Display available trains
- Book train tickets
- Cancel reservations
- Display passenger details

---

## Features

### Train Management
- Add new train details
- Store train records in binary file
- Display all train information

### Reservation System
- Book tickets using train number
- Automatically decrease available seats
- Generate passenger reservation records

### Cancellation System
- Cancel reservation using PNR number
- Automatically increase seat availability after cancellation

### Passenger Records
- Display all booked passenger details

---

## Technologies Used

- C++
- File Handling
- Binary Files
- OOP Concepts

---

## Files Used

| File Name | Purpose |
|------------|---------|
| `train.dat` | Stores train records |
| `passenger.dat` | Stores passenger reservation records |
| `temp.dat` | Temporary file used during cancellation |

---

## Functions Included

| Function | Description |
|----------|-------------|
| `addTrainRecord()` | Add new train details |
| `displayTrains()` | Show all trains |
| `bookReservation()` | Book train ticket |
| `cancelReservation()` | Cancel booked ticket |
| `displayPassengers()` | Display passenger details |

---

## Sample Menu

```text
1.Add Train
2.Display Trains
3.Book Ticket
4.Cancel Ticket
5.Display Passengers
6.Exit
