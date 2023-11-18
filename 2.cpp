#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

struct Airport
{
    string name;
    double latitude;
    double longitude;

    Airport(const string &n, double lat, double lon) : name(n), latitude(lat), longitude(lon) {}
};

struct AirportDistance
{
    Airport airport;
    double distance;

    AirportDistance(const Airport &a, double d) : airport(a), distance(d) {}

    bool operator>(const AirportDistance &other) const
    {
        return distance > other.distance;
    }
};

double calculateDistance(double lat1, double lon1, double lat2, double lon2)
{
    const double EarthRadiusKm = 6371.0;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EarthRadiusKm * c;
}

double calculateCabPrice(double distance)
{
    // Replace this with your cab price calculation logic
    // For example, you can assume a basic rate and a rate per kilometer
    // Adjust these values according to your pricing model.
    const double basicRate = 50.0; // Basic rate in Rs
    const double ratePerKm = 10.0; // Rate per kilometer in Rs

    double price = basicRate + (distance * ratePerKm);
    return price;
}

Airport findNearestAirport(const vector<Airport> &airports, double userLatitude, double userLongitude)
{
    priority_queue<AirportDistance, vector<AirportDistance>, greater<AirportDistance>> minHeap;

    for (const Airport &airport : airports)
    {
        double distance = calculateDistance(userLatitude, userLongitude, airport.latitude, airport.longitude);
        minHeap.push(AirportDistance(airport, distance));
    }

    return minHeap.top().airport;
}

int main()
{
    vector<Airport> airports;

    // Add airports to the list with their names, latitude, and longitude
    airports.push_back(Airport("Delhi", 28.6141, 77.2022));
    airports.push_back(Airport("Mumbai", 19.0895, 72.8656));
    airports.push_back(Airport("Bangalore", 13.1989, 77.7068));
    airports.push_back(Airport("Chennai", 13.0827, 80.2707));
    airports.push_back(Airport("Kolkata", 22.6534, 88.4467));
    airports.push_back(Airport("Hyderabad", 17.2403, 78.4294));
    airports.push_back(Airport("Pune", 18.5793, 73.9089));
    airports.push_back(Airport("Jaipur", 26.8289, 75.8056));
    airports.push_back(Airport("Lucknow", 26.7655, 80.8854));
    airports.push_back(Airport("Ahmedabad", 23.0734, 72.6266));
    airports.push_back(Airport("Bhopal", 27.5064, 8.2284));
    airports.push_back(Airport("Patna", 25.5954, 85.0921));
    airports.push_back(Airport("Indore", 22.7280, 75.8041));
    airports.push_back(Airport("Chandigarh", 30.6680, 76.7860));
    airports.push_back(Airport("Goa", 15.3803, 73.8350));
    airports.push_back(Airport("Agra", 27.1618, 77.9707));
    airports.push_back(Airport("Varanasi", 25.4507, 82.8560));
    airports.push_back(Airport("Kochi", 10.1518, 76.3930));
    airports.push_back(Airport("Amritsar", 31.7056, 74.8073));
    airports.push_back(Airport("Ranchi", 23.3174, 85.3255));
    // Add more airports here...

    double userLatitude, userLongitude;
    cout << "Enter your current location (latitude and longitude): ";
    cin >> userLatitude >> userLongitude;

    Airport nearestAirport = findNearestAirport(airports, userLatitude, userLongitude);

    cout << "Nearest airport to your location is: " << nearestAirport.name << endl;

    double distance = calculateDistance(userLatitude, userLongitude, nearestAirport.latitude, nearestAirport.longitude);
    cout << "Distance to the airport: " << distance << " kilometers" << endl;

    double cabPrice = calculateCabPrice(distance);
    cout << "Estimated cab price to the nearest airport: Rs" << cabPrice << endl;

    return 0;
}
