#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <thread>
#include <ctime>

using namespace std;

const int max_veh = 100;
const int max_violations = 100;
const int max_intersections = 10;

struct Vehicle
{
    int id;
    string owner;
    string type;
    string licensePlate;
    string registrationDate;
};

struct Violation
{
    int id;
    int vehicleId;
    string type;
    string dateTime;
    double fineAmount;
};

Vehicle vehicles[max_veh];
Violation violations[max_violations];
int vehicleCount = 0;
int violationCount = 0;

enum TrafficLightState
{
    RED,
    YELLOW,
    GREEN
};
TrafficLightState intersections[max_intersections];
int timers[max_intersections];

int trafficDensity[max_intersections];

void adminDashboard();
void manageTrafficLights();
void registerVehicle();
void trackViolations();
void viewTrafficReports();
void emergencyVehicleAssistance();
void realTimeTrafficMonitoring();
void searchMenu();
void searchVehicle();

void saveVehiclesToFile();
void loadVehiclesFromFile();
void saveViolationsToFile();
void loadViolationsFromFile();

int main()
{
    loadVehiclesFromFile();
    loadViolationsFromFile();
    adminDashboard();
    return 0;
}

void adminDashboard()
{
    int choice;

    while (true)
    {
        cout << "--- Admin Dashboard ---" << endl;
        cout << "1. Manage Traffic Lights" << endl;
        cout << "2. Register Vehicles" << endl;
        cout << "3. Track Violations" << endl;
        cout << "4. View Traffic Reports" << endl;
        cout << "5. Emergency Vehicle Assistance" << endl;
        cout << "6. Live Traffic Monitoring" << endl;
        cout << "7. Search Vehicles" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            manageTrafficLights();
            break;
        case 2:
            registerVehicle();
            break;
        case 3:
            trackViolations();
            break;
        case 4:
            viewTrafficReports();
            break;
        case 5:
            emergencyVehicleAssistance();
            break;
        case 6:
            realTimeTrafficMonitoring();
            break;
        case 7:
            searchMenu();
            break;
        case 8:
            saveVehiclesToFile();
            saveViolationsToFile();
            cout << "Exiting program..." << endl;
            return;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}

void manageTrafficLights()
{
    cout << "--- Traffic Light Management ---" << endl;

    for (int i = 0; i < max_intersections; i++)
    {
        intersections[i] = RED;
        timers[i] = 10;
    }

    cout << "Simulating traffic light states..." << endl;

    while (true)
    {
        for (int i = 0; i < max_intersections; i++)
        {
            if (intersections[i] == RED)
            {
                intersections[i] = GREEN;
            }
            else if (intersections[i] == GREEN)
            {
                intersections[i] = YELLOW;
            }
            else if (intersections[i] == YELLOW)
            {
                intersections[i] = RED;
            }

            string state = (intersections[i] == RED) ? "RED" : (intersections[i] == GREEN) ? "GREEN"
                                                                                           : "YELLOW";

            cout << "Intersection " << i + 1 << ": " << state << endl;
        }

        this_thread::sleep_for(chrono::seconds(5));
        cout << "Press 0 to stop simulation: ";
        int stop;
        cin >> stop;
        if (stop == 0)
            break;
    }
}
//Coded by Talha
void registerVehicle()
{
    if (vehicleCount >= max_veh)
    {
        cout << "Vehicle storage is full!" << endl;
        return;
    }

    cout << "--- Register Vehicle ---" << endl;
    Vehicle newVehicle;
    newVehicle.id = vehicleCount + 1;
    cout << "Enter owner name: ";
    cin.ignore();
    getline(cin, newVehicle.owner);
    cout << "Enter vehicle type: ";
    cin >> newVehicle.type;
    cout << "Enter license plate: ";
    cin >> newVehicle.licensePlate;
    cout << "Enter registration date (DD/MM/YYYY): ";
    cin >> newVehicle.registrationDate;

    vehicles[vehicleCount++] = newVehicle;
    cout << "Vehicle registered successfully!" << endl;
}

void realTimeTrafficMonitoring()
{
    cout << "--- Live Traffic Monitoring ---" << endl;

    while (true)
    {
        for (int i = 0; i < max_intersections; i++)
        {
            trafficDensity[i] = rand() % 3;
        }

        cout << "Current Traffic Status:" << endl;
        for (int i = 0; i < max_intersections; i++)
        {
            string density = (trafficDensity[i] == 0) ? "Low" : (trafficDensity[i] == 1) ? "Moderate"
                                                                                         : "High";
            cout << "Intersection " << i + 1 << ": " << density << endl;
        }

        this_thread::sleep_for(chrono::seconds(5));

        cout << "Press 0 to stop live monitoring: ";
        int stop;
        cin >> stop;
        if (stop == 0)
            break;
    }
}

void searchMenu()
{
    int choice;
    cout << "--- Search Vehicles ---" << endl;
    cout << "1. Search by Vehicle ID" << endl;
    cout << "2. Search by Owner Name" << endl;
    cout << "3. Search by License Plate" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        searchVehicle();
        break;
    case 2:
        searchVehicle();
        break;
    case 3:
        searchVehicle();
        break;
    default:
        cout << "Invalid choice. Returning to the dashboard." << endl;
    }
}
//Editted by Abdullah
void searchVehicle()
{
    int choice;
    cout << "Search by: " << endl;
    cout << "1. Vehicle ID" << endl;
    cout << "2. Owner Name" << endl;
    cout << "3. License Plate" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        int searchID;
        cout << "Enter Vehicle ID: ";
        cin >> searchID;

        bool found = false;
        for (int i = 0; i < vehicleCount; i++)
        {
            if (vehicles[i].id == searchID)
            {
                cout << "Vehicle Found: " << endl;
                cout << "ID: " << vehicles[i].id << endl;
                cout << "Owner: " << vehicles[i].owner << endl;
                cout << "Type: " << vehicles[i].type << endl;
                cout << "License Plate: " << vehicles[i].licensePlate << endl;
                cout << "Registration Date: " << vehicles[i].registrationDate << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Vehicle not found." << endl;
    }
    else if (choice == 2)
    {
        string searchName;
        cout << "Enter Owner Name: ";
        getline(cin, searchName);

        bool found = false;
        for (int i = 0; i < vehicleCount; i++)
        {
            if (vehicles[i].owner == searchName)
            {
                cout << "Vehicle Found: " << endl;
                cout << "ID: " << vehicles[i].id << endl;
                cout << "Owner: " << vehicles[i].owner << endl;
                cout << "Type: " << vehicles[i].type << endl;
                cout << "License Plate: " << vehicles[i].licensePlate << endl;
                cout << "Registration Date: " << vehicles[i].registrationDate << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Vehicle not found." << endl;
    }
    else if (choice == 3)
    {
        string searchPlate;
        cout << "Enter License Plate: ";
        getline(cin, searchPlate);

        bool found = false;
        for (int i = 0; i < vehicleCount; i++)
        {
            if (vehicles[i].licensePlate == searchPlate)
            {
                cout << "Vehicle Found: " << endl;
                cout << "ID: " << vehicles[i].id << endl;
                cout << "Owner: " << vehicles[i].owner << endl;
                cout << "Type: " << vehicles[i].type << endl;
                cout << "License Plate: " << vehicles[i].licensePlate << endl;
                cout << "Registration Date: " << vehicles[i].registrationDate << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Vehicle not found." << endl;
    }
    else
    {
        cout << "Invalid search option." << endl;
    }
}

void saveVehiclesToFile()
{
    ofstream file("vehicles.txt");
    for (int i = 0; i < vehicleCount; i++)
    {
        file << vehicles[i].id << " "
             << vehicles[i].owner << " "
             << vehicles[i].type << " "
             << vehicles[i].licensePlate << " "
             << vehicles[i].registrationDate << endl;
    }
    file.close();
}

void loadVehiclesFromFile()
{
    ifstream file("vehicles.txt");
    vehicleCount = 0;
    while (file >> vehicles[vehicleCount].id)
    {
        file.ignore();
        getline(file, vehicles[vehicleCount].owner, ' ');
        file >> vehicles[vehicleCount].type >> vehicles[vehicleCount].licensePlate >> vehicles[vehicleCount].registrationDate;
        vehicleCount++;
    }
    file.close();
}

void trackViolations()
{
    if (violationCount >= max_violations)
    {
        cout << "Violation storage is full!" << endl;
        return;
    }

    cout << "--- Track Violation ---" << endl;
    Violation newViolation;
    newViolation.id = violationCount + 1;
    cout << "Enter vehicle ID: ";
    cin >> newViolation.vehicleId;
    cout << "Enter violation type: ";
    cin >> newViolation.type;
    cout << "Enter date and time (DD/MM/YYYY HH:MM): ";
    cin.ignore();
    getline(cin, newViolation.dateTime);
    cout << "Enter fine amount: ";
    cin >> newViolation.fineAmount;

    violations[violationCount++] = newViolation;
    cout << "Violation recorded successfully!" << endl;
}

void saveViolationsToFile()
{
    ofstream file("violations.txt");
    for (int i = 0; i < violationCount; i++)
    {
        file << violations[i].id << " "
             << violations[i].vehicleId << " "
             << violations[i].type << " "
             << violations[i].dateTime << " "
             << violations[i].fineAmount<<endl;
    }
    file.close();
}

void loadViolationsFromFile()
{
    ifstream file("violations.txt");
    violationCount = 0;
    while (file >> violations[violationCount].id)
    {
        file >> violations[violationCount].vehicleId;
        file.ignore();
        getline(file, violations[violationCount].type, ' ');
        getline(file, violations[violationCount].dateTime, ' ');
        file >> violations[violationCount].fineAmount;
        violationCount++;
    }
    file.close();
}

void viewTrafficReports()
{
    cout << "--- Traffic Reports ---" << endl;

    cout << "1. Total Vehicles Registered: " << vehicleCount << endl;

    cout << "2. Violations Summary:" << endl;
    int overSpeedingCount = 0, signalJumpingCount = 0, illegalParkingCount = 0;
    double totalFines = 0;

    for (int i = 0; i < violationCount; i++)
    {
        totalFines += violations[i].fineAmount;
        if (violations[i].type == "Over-Speeding")
            overSpeedingCount++;
        else if (violations[i].type == "Signal Jumping")
            signalJumpingCount++;
        else if (violations[i].type == "Illegal Parking")
            illegalParkingCount++;
    }

    cout << "   a. Over-Speeding Violations: " << overSpeedingCount << endl;
    cout << "   b. Signal Jumping Violations: " << signalJumpingCount << endl;
    cout << "   c. Illegal Parking Violations: " << illegalParkingCount << endl;
    cout << "   d. Total Fines Collected: $" << fixed << setprecision(2) << totalFines << endl;

    cout << "3. Traffic Density (Simulation):" << endl;
    for (int i = 0; i < max_intersections; i++)
    {
        string density = (timers[i] < 5) ? "Low" : (timers[i] < 10) ? "Moderate"
                                                                    : "High";
        cout << "   Intersection " << i + 1 << ": " << density << endl;
    }

    cout << "Reports generated successfully!" << endl;
}

void emergencyVehicleAssistance()
{
    cout << "--- Emergency Vehicle Assistance ---" << endl;

    int start, destination;
    cout << "Enter starting intersection (1 to " << max_intersections << "): ";
    cin >> start;
    cout << "Enter destination intersection (1 to " << max_intersections << "): ";
    cin >> destination;

    if (start < 1 || start > max_intersections || destination < 1 || destination > max_intersections)
    {
        cout << "Invalid intersections. Please enter values between 1 and " << max_intersections << "." << endl;
        return;
    }

    cout << "Prioritizing traffic lights along the route..." << endl;

    for (int i = start - 1; i < destination; i++)
    {
        intersections[i] = GREEN;
        cout << "Intersection " << i + 1 << " light turned GREEN for emergency vehicle." << endl;
    }

    cout << "Emergency vehicle assistance completed." << endl;
}
