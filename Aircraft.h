#pragma once
#include "Shared.h"

// base class
class Entity {
protected:
    string id;
public:
    Entity(string entityID);
    virtual ~Entity();
    string getID() const;
};

//intermediate base class
// virtual inheritance to prevent diamond problem
class FlyingObject : virtual public Entity {
protected:
    int altitude;
public:
    FlyingObject(string id, int alt);
};

//intermediate base class
class TrackableObject : virtual public Entity {
protected:
    Location<> loc;
public:
    TrackableObject(string id, double x, double y);
};

//abstract class
//multiple inheritance
// creates diamond problem as the two base class came from entity class
class Aircraft : public FlyingObject, public TrackableObject {
protected:
    int fuelLevel;
    double heading;
    double speed;
public:
    //static member
    static string weatherCondition;
    static void changeWeather(string newWeather);

    Aircraft(string id, int alt, double x, double y, int fuel, double hdg, double spd);

    //runtime polymorphism
    //pure virtual function
    virtual void updateStatus() = 0;
    void updateDetails(int newAlt, double newX, double newY, int newFuel);
    Aircraft* refuel(int amount);
    bool operator==(const Aircraft& other);
    friend ostream& operator<<(ostream& os, const Aircraft& ac);

    int getAltitude() const;
    int getFuel() const;
    double getX() const;
    double getY() const;
    double getHeading() const;
    double getSpeed() const;
};

//child class
class CommercialPlane : public Aircraft {
public:
    CommercialPlane(string id, int alt, double x, double y, int fuel, double hdg, double spd);
    void updateStatus() override;

    //Compile-time Polymorphism ( function overloading)
    void changeAltitude();
    void changeAltitude(int newAlt);
};

//child class
class SmartDrone : public Aircraft {
public:
    SmartDrone(string id, int alt, double x, double y, int fuel, double hdg, double spd);
    void updateStatus() override;
};
