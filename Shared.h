#pragma once
#include <iostream>
#include <exception>
#include <string>

using namespace std;

// FEATURE: Exception Handling
class FuelException : public exception {
public:
    const char* what() const throw() {
        return "CRITICAL WARNING: Fuel critically low! Routing to emergency queue.";
    }
};

// FEATURE: Class Template with Default Template parameter
template <typename T = double>
class Location {
public:
    T x, y;
    Location(T xVal = 0, T yVal = 0) : x(xVal), y(yVal) {}
};

// FEATURE: Function Template
template <typename T>
void printLog(T message) {
    cout << "[SYSTEM LOG]: " << message << "\n";
}
