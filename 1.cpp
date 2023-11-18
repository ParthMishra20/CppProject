#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<string>

using namespace std;

// Dictionary of Indian cities and their respective airport codes
map<string, string> cityCodes = {
    {"Delhi", "DEL"},
    {"Mumbai", "BOM"},
    {"Bangalore", "BLR"},
    {"Chennai", "MAA"},
    {"Kolkata", "CCU"},
    {"Hyderabad", "HYD"},
    {"Pune", "PNQ"},
    {"Jaipur", "JAI"},
    {"Lucknow", "LKO"},
    {"Ahmedabad", "AMD"},
    {"Bhopal", "BHO"},
    {"Patna", "PAT"},
    {"Indore", "IDR"},
    {"Chandigarh", "IXC"},
    {"Goa", "GOI"},
    {"Agra", "AGR"},
    {"Varanasi", "VNS"},
    {"Kochi", "COK"},
    {"Amritsar", "ATQ"},
    {"Ranchi", "IXR"}
    // Add more cities here
};


// Sample flights between cities with random flight names and timings
map<string, vector<pair<string, string>>> flights = {
    {"DEL", {{"BOM", "Flight 101 (10:00 AM)"}, {"BLR", "Flight 102 (11:30 AM)"}, {"MAA", "Flight 103 (1:00 PM)"}, {"CCU", "Flight 104 (2:30 PM)"}, {"HYD", "Flight 105 (4:00 PM)"}}},
    {"BOM", {{"DEL", "Flight 201 (9:30 AM)"}, {"BLR", "Flight 202 (12:00 PM)"}, {"HYD", "Flight 203 (2:15 PM)"}}},
    {"BLR", {{"DEL", "Flight 301 (10:15 AM)"}, {"BOM", "Flight 302 (1:45 PM)"}, {"MAA", "Flight 303 (3:30 PM)"}, {"HYD", "Flight 304 (5:45 PM)"}}},
    {"MAA", {{"DEL", "Flight 401 (2:30 PM)"}, {"BLR", "Flight 402 (4:15 PM)"}, {"HYD", "Flight 403 (6:30 PM)"}}},
    {"CCU", {{"DEL", "Flight 501 (3:00 PM)"}, {"BOM", "Flight 502 (5:45 PM)"}, {"BLR", "Flight 503 (7:30 PM)"}}},
    {"HYD", {{"DEL", "Flight 601 (4:45 PM)"}, {"BOM", "Flight 602 (6:30 PM)"}, {"MAA", "Flight 603 (8:15 PM)"}}},
    {"PNQ", {{"DEL", "Flight 701 (6:15 PM)"}, {"BLR", "Flight 702 (8:00 PM)"}, {"JAI", "Flight 703 (9:45 PM)"}}},
    {"JAI", {{"DEL", "Flight 801 (7:30 AM)"}, {"PNQ", "Flight 802 (9:15 AM)"}, {"LKO", "Flight 803 (11:00 AM)"}}},
    {"LKO", {{"DEL", "Flight 901 (8:45 AM)"}, {"JAI", "Flight 902 (10:30 AM)"}, {"AMD", "Flight 903 (12:15 PM)"}}},
    {"AMD", {{"DEL", "Flight 1001 (10:00 AM)"}, {"LKO", "Flight 1002 (11:45 AM)"}, {"BHO", "Flight 1003 (1:30 PM)"}}},
    {"BHO", {{"DEL", "Flight 1101 (11:15 AM)"}, {"AMD", "Flight 1102 (1:00 PM)"}, {"PAT", "Flight 1103 (2:45 PM)"}}},
    {"PAT", {{"DEL", "Flight 1201 (12:30 PM)"}, {"BHO", "Flight 1202 (2:15 PM)"}, {"IDR", "Flight 1203 (4:00 PM)"}}},
    {"IDR", {{"DEL", "Flight 1301 (1:45 PM)"}, {"BHO", "Flight 1302 (3:30 PM)"}, {"CCU", "Flight 1303 (5:15 PM)"}}},
    {"IXC", {{"DEL", "Flight 1401 (3:00 PM)"}, {"GOI", "Flight 1402 (4:45 PM)"}, {"AGR", "Flight 1403 (6:30 PM)"}}},
    {"GOI", {{"DEL", "Flight 1501 (4:15 PM)"}, {"IXC", "Flight 1502 (6:00 PM)"}, {"VNS", "Flight 1503 (7:45 PM)"}}},
    {"AGR", {{"DEL", "Flight 1601 (5:30 PM)"}, {"GOI", "Flight 1602 (7:15 PM)"}, {"COK", "Flight 1603 (9:00 PM)"}}},
    {"VNS", {{"DEL", "Flight 1701 (6:45 PM)"}, {"GOI", "Flight 1702 (8:30 PM)"}, {"ATQ", "Flight 1703 (10:15 PM)"}}},
    {"COK", {{"DEL", "Flight 1801 (8:00 PM)"}, {"AGR", "Flight 1802 (9:45 PM)"}, {"IXR", "Flight 1803 (11:30 PM)"}}},
    {"ATQ", {{"DEL", "Flight 1901 (9:15 PM)"}, {"COK", "Flight 1902 (11:00 PM)"}, {"Ranchi", "Flight 1903 (12:45 AM)"}}},
    {"IXR", {{"DEL", "Flight 2001 (10:30 PM)"}, {"ATQ", "Flight 2002 (12:15 AM)"}, {"PNQ", "Flight 2003 (2:00 AM)"}}}
    // Add more flights here
};
// Queue implementation
template <class T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const T& value) {
        Node* newNode = new Node{value, nullptr};
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
        if (front == nullptr) {
            rear = nullptr;
        }
    }

    T getFront() const {
        if (!isEmpty()) {
            return front->data;
        }
        return T();
    }
};

// Linked List implementation
template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(const T& value) {
        Node* newNode = new Node{value, nullptr};
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

string getDate() {
    string date;
    cout << "Enter the date of travel/booking (YYYY-MM-DD): ";
    cin >> date;
    // Additional validation for date format can be added here
    return date;
}

void bookDirectFlight(const string& source, const string& destination, const string& flightName, const string& travelDate) {
    string name, mobileNumber, email;

    cout << "Please provide your details before booking the flight:" << endl;
    cout << "Enter your name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);

    cout << "Enter your mobile number: ";
    cin >> mobileNumber;

    cout << "Enter your email: ";
    cin >> email;

    cout << "Direct flight available from " << source << " to " << destination << ": " << flightName << endl;
    cout << "Would you like to book this flight? (Y/N): ";
    char choice;
    cin >> choice;
    if (toupper(choice) == 'Y') {
        // Add logic to book the direct flight here
        cout << "Your flight has been booked from " << source << " to " << destination << " with " << flightName << " on " << travelDate << ". Enjoy your journey!" << endl;
        cout << "Passenger Details: " << endl;
        cout << "Name: " << name << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Email: " << email << endl;
    } else {
        cout << "Booking canceled." << endl;
    }
}

// Function to book a connecting flight after collecting user information
void bookConnectingFlight(const string& source, const string& destination, const vector<pair<string, string>>& availableFlights, const string& travelDate) {
    string name, mobileNumber, email;

    cout << "Please provide your details before booking the flight:" << endl;
    cout << "Enter your name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);

    cout << "Enter your mobile number: ";
    cin >> mobileNumber;

    cout << "Enter your email: ";
    cin >> email;

    cout << "No direct flights available from " << source << " to " << destination << "." << endl;
    cout << "Suggested connecting flights: " << endl;
    int choice = 1;
    for (const auto& flight : availableFlights) {
        cout << choice << ". " << source << " -> " << flight.first << " (" << flight.second << ")" << endl;
        choice++;
    }
    cout << "Select a flight (1-" << availableFlights.size() << "): ";
    int selectedChoice;
    cin >> selectedChoice;
    if (selectedChoice >= 1 && selectedChoice <= availableFlights.size()) {
        const auto& selectedFlight = availableFlights[selectedChoice - 1];
        cout << "Would you like to book this flight? (Y/N): ";
        char choice;
        cin >> choice;
        if (toupper(choice) == 'Y') {
            cout << "Your connecting flight has been booked from " << source << " to " << selectedFlight.first << " with " << selectedFlight.second << " on " << travelDate << ". Enjoy your journey!" << endl;
            cout << "Passenger Details: " << endl;
            cout << "Name: " << name << endl;
            cout << "Mobile Number: " << mobileNumber << endl;
            cout << "Email: " << email << endl;
        } else {
            cout << "Booking canceled." << endl;
        }
    } else {
        cout << "Invalid choice. Booking canceled." << endl;
    }
}
int main() {
    string source, destination, travelDate;
    cout << "Enter your home city: ";
    cin >> source;
    
    cout << "Enter your destination city: ";
    cin >> destination;
    
    travelDate = getDate();

    // Validate source and destination cities
    if (cityCodes.find(source) != cityCodes.end() && cityCodes.find(destination) != cityCodes.end()) {
        string sourceCode = cityCodes[source];
        string destinationCode = cityCodes[destination];

        // Check if flights are available from the source city
        if (flights.find(sourceCode) != flights.end()) {
            vector<pair<string, string>> availableFlights = flights[sourceCode];
            bool directFlightAvailable = false;

            for (auto flight : availableFlights) {
                if (flight.first == destinationCode) {
                    directFlightAvailable = true;
                    bookDirectFlight(source, destination, flight.second, travelDate);
                    break;
                }
            }

            if (!directFlightAvailable) {
                bookConnectingFlight(source, destination, availableFlights, travelDate);
            }
        } else {
            cout << "No flights available from " << source << " to " << destination << "." << endl;
        }
    } else {
        cout << "Invalid source or destination city." << endl;
    }

    return 0;
}
