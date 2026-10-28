# RailEase
### Railway Ticketing Application in C++

RailEase is a console-based railway ticketing application developed in C++ as a Programming Fundamentals project. It provides a menu-driven interface for managing train ticket reservations, seat allocation, passenger records, and fare calculations.

## Features

- **Train Route Information:** Displays available train routes and fare details.
- **Seat Allocation:** Represents seat availability across multiple trains and travel classes.
- **Ticket Reservation:** Accepts passenger details and assigns tickets.
- **Ticket Cancellation:** Updates reservation records when a ticket is cancelled.
- **Ticket Lookup:** Retrieves information associated with booked tickets.
- **Fare Calculation:** Applies age-based discounts according to the defined fare policy.
- **Manager Dashboard:** Provides access to booking statistics and management functions.
- **File Handling:** Supports saving and loading booking records.

## Technical Concepts

- **Arrays:** Manage train seats and booking records using structured data.
- **Functions:** Divide the application into modular operations, improving readability and maintainability.
- **Conditional Statements:** Handle menu choices, booking conditions, access checks, and fare rules.
- **Loops:** Support repeated menu interactions and seat-related operations.
- **File Handling:** Preserve booking information between program executions.
- **Problem Solving:** Translate a real-world railway ticketing scenario into program logic, including seat availability, reservation processing, cancellation, and age-based fare calculations.

## Technologies Used

- **Language:** C++
- **Application Type:** Console-based
- **Development Focus:** Programming Fundamentals and procedural programming

## Getting Started

### Prerequisites

- C++ compiler, such as GCC/G++
- C++ IDE or terminal

### Compile and Run

1. Download or clone this repository.
2. Open the project directory in a terminal.
3. Compile the source file:

   ```bash
   g++ RailEase.cpp -o RailEase
   ```

4. Run the application.

   **Windows PowerShell:**

   ```powershell
   .\RailEase.exe
   ```

   **Linux/macOS:**

   ```bash
   ./RailEase
   ```

## Project Structure

```text
RailEase/
├── RailEase.cpp
├── README.md
└── .gitignore
```

