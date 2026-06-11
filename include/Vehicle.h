#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "Enums.h"

/*
 * OOP Principle: Abstraction & Encapsulation
 * Abstract base class defining fundamental vehicle characteristics.
 * Derived classes instantiate runtime polymorphism through virtual methods.
 */
class Vehicle {
protected:
    std::string plateNumber;
    VehicleType type;

public:
    Vehicle(const std::string& plate, VehicleType t);
    virtual ~Vehicle() = default; // Essential for safe polymorphic deletion

    // Public getters enforcing clean data exposure boundaries
    std::string getPlateNumber() const;
    VehicleType getType() const;

    // Pure virtual function enforcing runtime polymorphism across child implementations
    virtual std::string getTypeName() const = 0;
};

// Derived specialized vehicle types showcasing Object Inheritance
class Motorcycle : public Vehicle {
public:
    Motorcycle(const std::string& plate);
    std::string getTypeName() const override;
};

class Car : public Vehicle {
public:
    Car(const std::string& plate);
    std::string getTypeName() const override;
};

class Truck : public Vehicle {
public:
    Truck(const std::string& plate);
    std::string getTypeName() const override;
};

#endif // VEHICLE_H