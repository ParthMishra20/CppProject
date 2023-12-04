#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

class Flight {
public:
    Flight(const std::string& number, const std::string& destination, const std::string& departureTime)
        : number(number), destination(destination), departureTime(departureTime) {}

    std::string getNumber() const { return number; }
    std::string getDestination() const { return destination; }
    std::string getDepartureTime() const { return departureTime; }

private:
    std::string number;
    std::string destination;
    std::string departureTime;
};

class AirportManagementSystem {
public:
    void run() {
        initializeFlights();
        while (true) {
            displayMenu();
            int choice = getChoice();
            processChoice(choice);
        }
    }

private:
    std::vector<Flight> bookedFlights;

    void initializeFlights() {
        // Pre-populate bookedFlights for testing
        bookedFlights.push_back(Flight("ABC123", "New York", "12:00 PM"));
        bookedFlights.push_back(Flight("DEF456", "Los Angeles", "02:30 PM"));
        bookedFlights.push_back(Flight("GHI789", "Chicago", "04:45 PM"));
    }

    void displayMenu() {
        std::cout << "Airport Management System\n";
        std::cout << "1. Book a Flight\n";
        std::cout << "2. Check Flight Status\n";
        std::cout << "3. Cancel Flight\n";
        std::cout << "4. Exit\n";
    }

    int getChoice() {
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        return choice;
    }

    void processChoice(int choice) {
        switch (choice) {
            case 1:
                bookFlight();
                break;
            case 2:
                checkFlightStatus();
                break;
            case 3:
                cancelFlight();
                break;
            case 4:
                std::cout << "Exiting...\n";
                exit(0);
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    void bookFlight() {
        std::string passengerName, destination;
        std::cout << "Enter passenger name: ";
        std::cin.ignore();
        std::getline(std::cin, passengerName);
        std::cout << "Enter destination: ";
        std::getline(std::cin, destination);

        std::string flightNumber = generateRandomFlightNumber();
        bookedFlights.push_back(Flight(flightNumber, destination, "TBD"));

        std::cout << "Flight booked for " << passengerName << " to " << destination << "\n";
        std::cout << "Your Flight Number is: " << flightNumber << "\n";
    }

    void checkFlightStatus() {
        std::string flightNumber;
        std::cout << "Enter flight number: ";
        std::cin >> flightNumber;

        auto it = std::find_if(bookedFlights.begin(), bookedFlights.end(),
                               [flightNumber](const Flight& flight) { return flight.getNumber() == flightNumber; });

        if (it != bookedFlights.end()) {
            std::cout << "Flight " << it->getNumber() << " to " << it->getDestination()
                      << " is on time. Departure Time: " << it->getDepartureTime() << "\n";
        } else {
            std::cout << "Invalid flight number.\n";
        }
    }

    void cancelFlight() {
        std::string flightNumber;
        std::cout << "Enter flight number: ";
        std::cin >> flightNumber;

        auto it = std::find_if(bookedFlights.begin(), bookedFlights.end(),
                               [flightNumber](const Flight& flight) { return flight.getNumber() == flightNumber; });

        if (it != bookedFlights.end()) {
            bookedFlights.erase(it);
            std::cout << "Flight " << it->getNumber() << " to " << it->getDestination() << " has been canceled.\n";
        } else {
            std::cout << "Invalid flight number.\n";
        }
    }

    std::string generateRandomFlightNumber() {
        return "XYZ" + std::to_string(rand() % 1000);
    }
};

int main() {
    std::srand(std::time(0)); // Seed for random number generation
    AirportManagementSystem airportSystem;
    airportSystem.run();
    return 0;
}
