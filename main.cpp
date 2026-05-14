#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <typeinfo>
#include <queue>
#include <limits>
#include <windows.h>
#include "Aircraft.h"

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[1;31m";
const string GREEN = "\033[1;92m";
const string YELLOW = "\033[1;93m";
const string CYAN = "\033[1;96m";
const string WHITE = "\033[37m";
const string BG_BLUE = "\033[104m";
const string BLINK = "\033[1;5m";
const string BLACK = "\033[30m";
const string PURPLE = "\033[1;95m";

void clearScreen() { system("cls"); }
void delayInSeconds(int seconds) { Sleep(seconds * 1000); }

int getIntInput(string prompt) {
    int input; cout << prompt;
    while (!(cin >> input)) {
        cout << RED << "[ERROR] Invalid input. Enter a whole number: " << RESET;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

double getDoubleInput(string prompt) {
    double input; cout << prompt;
    while (!(cin >> input)) {
        cout << RED << "[ERROR] Invalid input. Enter a decimal: " << RESET;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}


string getDirectionArrow(double heading) {
    while (heading < 0) heading += 360;
    while (heading >= 360) heading -= 360;

    if (heading >= 315 || heading < 45) return "▲";
    else if (heading >= 45 && heading < 135) return "►";
    else if (heading >= 135 && heading < 225) return "▼";
    else return "◄";
}


void drawVisualRadar(const vector<Aircraft*>& airspace) {
    const int GRID_SIZE = 20;
    string grid[GRID_SIZE][GRID_SIZE];

    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            if (i == GRID_SIZE / 2 && j == GRID_SIZE / 2) grid[i][j] = "+";
            else grid[i][j] = ".";
        }
    }

    for (Aircraft* a : airspace) {
        int x = static_cast<int>(a->getX() / 10);
        int y = static_cast<int>(a->getY() / 10);
        if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
            grid[y][x] = getDirectionArrow(a->getHeading());
        }
    }

    cout << CYAN << "\n        LIVE RADAR FEED (Arrows show heading)\n" << RESET;
    cout << "    -------------------------------------------\n";

    for(int i = 0; i < GRID_SIZE; i++) {
        int yAxisValue = i * 10;
        if (yAxisValue < 10) cout << YELLOW << "  " << yAxisValue << RESET << " |";
        else if (yAxisValue < 100) cout << YELLOW << " " << yAxisValue << RESET << " |";
        else cout << YELLOW << yAxisValue << RESET << " |";

        for(int j = 0; j < GRID_SIZE; j++) {
            bool drawn = false;
            for (Aircraft* a : airspace) {
                if (static_cast<int>(a->getX()/10) == j && static_cast<int>(a->getY()/10) == i) {
                    if (dynamic_cast<CommercialPlane*>(a))
                        cout << BG_BLUE << PURPLE << BLINK << " " << grid[i][j] << RESET;
                    else
                        cout << BG_BLUE << YELLOW << BLINK << " " << grid[i][j] << RESET;

                    drawn = true; break;
                }
            }
            if (!drawn) {
                if (grid[i][j] == "+")
                    cout << BG_BLUE << BLACK << " +" << RESET;
                else
                    cout << BG_BLUE << WHITE << " ." << RESET;
            }
        }
        cout << " |\n";
    }
    cout << "    -------------------------------------------\n";
    cout << YELLOW << "      0       40      80      120     160   190\n\n" << RESET;
}



void removeAircraft(vector<Aircraft*>& airspace, string targetID) {
    for (auto it = airspace.begin(); it != airspace.end(); ) {
        if ((*it)->getID() == targetID) {
            delete *it;
            it = airspace.erase(it);
            cout << RED << "\n[!] Aircraft " << targetID << " has left the airspace/radar." << RESET << "\n";
            return;
        } else {
            ++it;
        }
    }
    cout << YELLOW << "\n[!] Aircraft " << targetID << " not found on radar.\n" << RESET;
}
// ==========================================


bool authenticateUser() {
    string username, password, u, p;
    int choice;

    while (true) {
        clearScreen();
        cout << CYAN << "=========================================\n";
        cout << "      AEROFLOW OS - SECURITY GATEWAY     \n";
        cout << "=========================================\n" << RESET;
        cout << "1. Login\n2. Register\n3. Exit Program\n";
        choice = getIntInput("Select option: ");

        if (choice == 1) {
            cout << "\n--- LOGIN ---\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            ifstream userFile("users.txt");
            bool loggedIn = false;
            while (userFile >> u >> p) {
                if (u == username && p == password) { loggedIn = true; break; }
            }
            userFile.close();

            if (loggedIn) {
                cout << GREEN << "\n[ACCESS GRANTED] Welcome, " << username << ".\n" << RESET;
                delayInSeconds(2);
                return true;
            } else {
                cout << RED << "\n[ACCESS DENIED] Incorrect credentials.\n" << RESET;
                delayInSeconds(2);
            }
        }
        else if (choice == 2) {
            cout << "\n--- REGISTER ---\n";
            cout << "Create Username (No spaces): "; cin >> username;
            cout << "Create Password (No spaces): "; cin >> password;
            ofstream userFile("users.txt", ios::app);
            userFile << username << " " << password << "\n";
            userFile.close();
            cout << GREEN << "\nRegistration successful! You can now login.\n" << RESET;
            delayInSeconds(2);
        }
        else if (choice == 3) return false;
    }
}

void loadPreviousData(vector<Aircraft*>& airspace) {
    ifstream inFile("airspace_data.txt");
    if (!inFile) return;
    int type, alt, fuel; double x, y, hdg, spd; string id;
    while (inFile >> type >> id >> alt >> x >> y >> fuel >> hdg >> spd) {
        if (type == 1) airspace.push_back(new CommercialPlane(id, alt, x, y, fuel, hdg, spd));
        else if (type == 2) airspace.push_back(new SmartDrone(id, alt, x, y, fuel, hdg, spd));
    }
    inFile.close();
}

void saveCurrentData(const vector<Aircraft*>& airspace) {
    ofstream outFile("airspace_data.txt");
    for (Aircraft* a : airspace) {
        if (dynamic_cast<CommercialPlane*>(a)) outFile << "1 "; else outFile << "2 ";
        outFile << a->getID() << " " << a->getAltitude() << " " << a->getX() << " "
                << a->getY() << " " << a->getFuel() << " " << a->getHeading() << " " << a->getSpeed() << "\n";
    }
    outFile.close();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    if (!authenticateUser()) return 0;

    vector<Aircraft*> airspace;
    queue<Aircraft*> emergencyQueue;
    loadPreviousData(airspace);
    bool running = true;

    while (running) {
        clearScreen();

        // FEATURE: System Logging Template Demonstration
        cout << "[LOG] System active. Monitoring airspace...\n";

        cout << CYAN << "=========================================\n";
        cout << "        AEROFLOW CONTROL TOWER MENU      \n";
        cout << "=========================================\n" << RESET;

        if (Aircraft::weatherCondition == "STORM") cout << " Weather: " << RED << "STORM" << RESET;
        else cout << " Weather: " << GREEN << "CLEAR" << RESET;

        cout << " | Planes in Air: " << airspace.size() << "\n-----------------------------------------\n";


        cout << " 1. Add Commercial Plane\n 2. Add Smart Drone\n 3. View Airspace Database\n 4. Update Aircraft Data\n 5. Change Global Weather\n 6. Run Radar Scan (Advance Time)\n 7. Process Landing Queue\n 8. Remove Aircraft\n 9. Save & Logout\n";
        cout << CYAN << "=========================================\n" << RESET;

        int choice = getIntInput("Enter command: ");
        clearScreen();

        switch (choice) {
            case 1: {
                cout << "--- ADD COMMERCIAL PLANE ---\n";
                string id; cout << "Enter Flight ID: "; cin >> id;
                int alt = getIntInput("Enter Altitude (ft): ");
                double x = getDoubleInput("Enter X Coord (0-200): ");
                double y = getDoubleInput("Enter Y Coord (0-200): ");
                double hdg = getDoubleInput("Enter Heading (0-360 degrees): ");
                double spd = getDoubleInput("Enter Speed (Units per scan): ");
                int fuel = getIntInput("Enter Fuel (0-100): ");
                airspace.push_back(new CommercialPlane(id, alt, x, y, fuel, hdg, spd));
                cout << GREEN << "\n[SUCCESS] Added to airspace.\n" << RESET; delayInSeconds(1); break;
            }
            case 2: {
                cout << "--- ADD SMART DRONE ---\n";
                string id; cout << "Enter Drone ID: "; cin >> id;
                int alt = getIntInput("Enter Altitude (ft): ");
                double x = getDoubleInput("Enter X Coord (0-200): ");
                double y = getDoubleInput("Enter Y Coord (0-200): ");
                double hdg = getDoubleInput("Enter Heading (0-360 degrees): ");
                double spd = getDoubleInput("Enter Speed (Units per scan): ");
                int fuel = getIntInput("Enter Battery (0-100): ");
                airspace.push_back(new SmartDrone(id, alt, x, y, fuel, hdg, spd));
                cout << GREEN << "\n[SUCCESS] Drone deployed.\n" << RESET; delayInSeconds(1); break;
            }
            case 3: {
                cout << "--- AIRSPACE DATABASE ---\n";
                if (airspace.empty()) cout << "Database is empty.\n";
                else for (Aircraft* a : airspace) cout << *a << endl;
                system("pause"); break;
            }
            case 4: {
                cout << "--- UPDATE AIRCRAFT DATA ---\n";
                if (airspace.empty()) { cout << "No planes available.\n"; system("pause"); break; }
                string targetID; cout << "Enter exact ID to modify: "; cin >> targetID;
                bool found = false;
                for (Aircraft* a : airspace) {
                    if (a->getID() == targetID) {
                        found = true;
                        int nAlt = getIntInput("New Altitude: ");
                        double nX = getDoubleInput("New X Pos: ");
                        double nY = getDoubleInput("New Y Pos: ");
                        int nFuel = getIntInput("New Fuel Level: ");
                        a->updateDetails(nAlt, nX, nY, nFuel);
                        cout << GREEN << "\n[SUCCESS] Data updated!\n" << RESET;
                        break;
                    }
                }
                if (!found) cout << RED << "\n[ERROR] Plane ID not found.\n" << RESET;
                system("pause"); break;
            }
            case 5: {
                cout << "--- WEATHER CONTROL ---\n";
                int wChoice = getIntInput("1. CLEAR\n2. STORM\nSelect: ");
                if (wChoice == 1) Aircraft::changeWeather("CLEAR");
                else if (wChoice == 2) Aircraft::changeWeather("STORM");
                cout << GREEN << "Weather updated.\n" << RESET;
                delayInSeconds(1); break;
            }
            case 6: {
                cout << CYAN << "--- INITIATING RADAR SCAN (ADVANCING TIME) ---\n" << RESET;

                for(size_t i = 0; i < airspace.size(); ) {
                    Aircraft* current = airspace[i];
                    try {
                        current->updateStatus();
                        i++;
                    }
                    catch (const FuelException& e) {
                        cout << RED << "   -> [EMERGENCY ALARM] " << e.what() << " ID: " << current->getID() << "\n" << RESET;
                        emergencyQueue.push(current);
                        airspace.erase(airspace.begin() + i);
                    }
                }

                drawVisualRadar(airspace);

                for(size_t i = 0; i < airspace.size(); ++i) {
                    Aircraft* current = airspace[i];
                    cout << "Tracking: " << *current << "\n";

                    if (i < airspace.size() - 1 && *current == *airspace[i+1]) {
                        cout << RED << "   -> [CRITICAL] COLLISION RISK DETECTED between "
                             << current->getID() << " and " << airspace[i+1]->getID() << "!\n" << RESET;
                    }
                }

                system("pause");
                break;
            }
            case 7: {
                cout << "--- EMERGENCY QUEUE ---\n";
                if (emergencyQueue.empty()) cout << "No emergencies.\n";
                while (!emergencyQueue.empty()) {
                    Aircraft* p = emergencyQueue.front();
                    cout << YELLOW << "Landing cleared for: " << p->getID() << ". Refueling...\n" << RESET;
                    delayInSeconds(1);
                    p->refuel(100);
                    airspace.push_back(p);
                    emergencyQueue.pop();
                    cout << GREEN << p->getID() << " safely returned to airspace.\n" << RESET;
                }
                system("pause"); break;
            }

            case 8: {
                cout << "--- REMOVE AIRCRAFT ---\n";
                if (airspace.empty()) {
                    cout << "Airspace is already empty.\n";
                    system("pause"); break;
                }
                string targetID;
                cout << "Enter exact ID to remove: "; cin >> targetID;
                removeAircraft(airspace, targetID);
                system("pause"); break;
            }

            case 9: {
                cout << "Saving data to disk...\n";
                delayInSeconds(1);
                saveCurrentData(airspace);
                cout << GREEN << "Safe shutdown complete.\n" << RESET;
                running = false;
                break;
            }
            default: {
                cout << RED << "Invalid Command!\n" << RESET;
                delayInSeconds(1);
                break;
            }
        }
    }

    for(Aircraft* a : airspace) delete a;
    while(!emergencyQueue.empty()) { delete emergencyQueue.front(); emergencyQueue.pop(); }
    return 0;
}
