#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Car class representing a single car
class Car {
private:
    string make;
    string model;
    string licensePlate;
    double latitude;
    double longitude;

public:
    Car(string make, string model, string licensePlate, double latitude, double longitude)
        : make(make), model(model), licensePlate(licensePlate), latitude(latitude), longitude(longitude) {}

    string getMake() const {
        return make;
    }

    string getModel() const {
        return model;
    }

    string getLicensePlate() const {
        return licensePlate;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }
};

// CarRentalSystem class representing the car rental system
class CarRentalSystem {
private:
    vector<Car> cars;

public:
    void addCar(const Car& car) {
        cars.push_back(car);
    }

    void displayAvailableCars() const {
        cout << "Available Cars:\n";
        for (const Car& car : cars) {
            cout << "Make: " << car.getMake() << ", Model: " << car.getModel() << ", License Plate: " << car.getLicensePlate() << endl;
        }
    }

    vector<Car> getCarsWithinRadius(double latitude, double longitude, double radius) const {
        vector<Car> carsWithinRadius;
        for (const Car& car : cars) {
            double distance = calculateDistance(latitude, longitude, car.getLatitude(), car.getLongitude());
            if (distance <= radius) {
                carsWithinRadius.push_back(car);
            }
        }
        return carsWithinRadius;
    }

private:
    double calculateDistance(double lat1, double lon1, double lat2, double lon2) const {
        // Calculate distance using Haversine formula or any other distance calculation algorithm
        // Implementation omitted for brevity
        return 0.0;
    }
};

// Function to read car data from a text file and populate the car rental system
void readCarDataFromFile(CarRentalSystem& carRentalSystem, const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    string make, model, licensePlate;
    double latitude, longitude;

    while (inputFile >> make >> model >> licensePlate >> latitude >> longitude) {
        Car car(make, model, licensePlate, latitude, longitude);
        carRentalSystem.addCar(car);
    }

    inputFile.close();
}

int main() {
    CarRentalSystem carRentalSystem;

    // Read car data from the text file
    string carDataFile = "car_data.txt";
    readCarDataFromFile(carRentalSystem, carDataFile);

    // Display available cars
    carRentalSystem.displayAvailableCars();

    // Example usage of getting cars within a certain radius
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    double radius = 10.0; // Example radius in kilometers

    vector<Car> carsWithinRadius = carRentalSystem.getCarsWithinRadius(latitude, longitude, radius);
    cout << "Cars within " << radius << " km radius of (" << latitude << ", " << longitude << "):\n";
    for (const Car& car : carsWithinRadius) {
        cout << "Make: " << car.getMake() << ", Model: " << car.getModel() << ", License Plate: " << car.getLicensePlate() << endl;
    }

    return 0;
}
