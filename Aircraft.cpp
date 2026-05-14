#include "Aircraft.h"
#include <cmath>

const double PI = 3.14159265358979323846;

string Aircraft::weatherCondition = "CLEAR";
void Aircraft::changeWeather(string newWeather) { weatherCondition = newWeather; }

//constructor
Entity::Entity(string entityID) : id(entityID) {}
//destructor
Entity::~Entity() {}
string Entity::getID() const { return id; }

//Constructor Initialization List(:) [directly set value to the variable of base class]
FlyingObject::FlyingObject(string id, int alt) : Entity(id), altitude(alt) {}
TrackableObject::TrackableObject(string id, double x, double y) : Entity(id), loc(x, y) {}

Aircraft::Aircraft(string id, int alt, double x, double y, int fuel, double hdg, double spd)
    : Entity(id), FlyingObject(id, alt), TrackableObject(id, x, y), fuelLevel(fuel), heading(hdg), speed(spd) {}

void Aircraft::updateDetails(int newAlt, double newX, double newY, int newFuel) {
    this->altitude = newAlt; this->loc.x = newX; this->loc.y = newY; this->fuelLevel = newFuel;
}

Aircraft* Aircraft::refuel(int amount) {
    this->fuelLevel += amount;
    if (this->fuelLevel > 100) this->fuelLevel = 100;
    return this;
}

//operator overloading
bool Aircraft::operator==(const Aircraft& other) { return this->altitude == other.altitude; }

ostream& operator<<(ostream& os, const Aircraft& ac) {
    os << "[" << ac.id << "] Alt: " << ac.altitude
       << "ft | Pos: (" << ac.loc.x << ", " << ac.loc.y
       << ") | Hdg: " << ac.heading << " deg | Spd: " << ac.speed
       << " | Fuel: " << ac.fuelLevel << "%";
    return os;
}

int Aircraft::getAltitude() const { return altitude; }
int Aircraft::getFuel() const { return fuelLevel; }
double Aircraft::getX() const { return loc.x; }
double Aircraft::getY() const { return loc.y; }
double Aircraft::getHeading() const { return heading; }
double Aircraft::getSpeed() const { return speed; }

//polymorphism
CommercialPlane::CommercialPlane(string id, int alt, double x, double y, int fuel, double hdg, double spd)
    : Entity(id), Aircraft(id, alt, x, y, fuel, hdg, spd) {}

void CommercialPlane::updateStatus() {
    double rad = heading * (PI / 180.0);
    loc.x += speed * sin(rad);
    loc.y += -speed * cos(rad);

    //ternary operator
    fuelLevel -= (Aircraft::weatherCondition == "STORM") ? 16 : 8;
    //if fuel less than 10% then throws exception
    if (fuelLevel <= 10) throw FuelException();
}

//function overloading
void CommercialPlane::changeAltitude() { altitude += 500; }
void CommercialPlane::changeAltitude(int newAlt) { altitude = newAlt; }

SmartDrone::SmartDrone(string id, int alt, double x, double y, int fuel, double hdg, double spd)
    : Entity(id), Aircraft(id, alt, x, y, fuel, hdg, spd) {}

    //overriding updateStatus
void SmartDrone::updateStatus() {
    double rad = heading * (PI / 180.0);
    loc.x += speed * sin(rad);
    loc.y += -speed * cos(rad);

    fuelLevel -= (Aircraft::weatherCondition == "STORM") ? 4 : 2;
    if (fuelLevel <= 5) throw FuelException();
}
