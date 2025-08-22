# Movie Booking System

Movie Booking System is a console-based C++ project designed to simulate the management of a cinema system. It allows users to create accounts, log in, select movies, choose showtimes, and purchase tickets. The application also supports user categories (such as students or seniors) that enable discounts on ticket prices. Admin users can manage movies by adding new films, modifying prices, and updating schedules. The system features balance management, simulated payments via Card or PayPal, and maintains transaction histories. Data is persisted using CSV files, and the application employs object-oriented programming principles such as inheritance, polymorphism, and the singleton pattern to provide a structured and scalable solution.

---

## Features

1. **User Authentication and Account Management**
   - Create new accounts (User/Admin)
   - Log in
   - Delete account
   - Log out

2. **Movie Management**
   - View the list of movies
   - Add new movies (Admin only)
   - Modify movie prices (Admin)
   - Modify movie schedule (Admin)
   - Select a movie and view available showtimes

3. **Ticket Purchasing**
   - Select a movie and a showtime
   - Choose a seat (seat availability is tracked)
   - Apply discounts based on user category (e.g., student or senior)

4. **User Categories**
   - Students and seniors can validate their category
   - Discounts are applied automatically for validated users

5. **Balance Management**
   - Add funds to user balance via Card or PayPal
   - View transaction history
   - Ensure sufficient funds before purchasing tickets

6. **Payment Integration**
   - Simulated payments using Card or PayPal
   - Input validation for card number, CVV, and PayPal credentials

---

## Technologies Used

- **C++17**
- CSV file handling with [csv.hpp](https://github.com/ben-strasser/fast-cpp-csv-parser)
- Password hashing with **BLAKE2b**
- Object-oriented programming (classes, inheritance, polymorphism)
- Singleton pattern for the main application

---

## About

This project was developed by Gabriel Ștefan as part of the Object-Oriented Programming course at the University of Bucharest.
