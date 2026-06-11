/**
 * Vehicle base class and derived classes implementations
 */

#include "Vehicle.h"

Vehicle::Vehicle(const std::string& plate, VehicleType t) 
    : plateNumber(plate), type(t) {}

std::string Vehicle::getPlateNumber() const { return plateNumber; }
VehicleType Vehicle::getType() const { return type; }

Motorcycle::Motorcycle(const std::string& plate) : Vehicle(plate, VehicleType::MOTORCYCLE) {}
std::string Motorcycle::getTypeName() const { return "Motorcycle"; }

Car::Car(const std::string& plate) : Vehicle(plate, VehicleType::CAR) {}
std::string Car::getTypeName() const { return "Car"; }

Truck::Truck(const std::string& plate) : Vehicle(plate, VehicleType::TRUCK) {}
std::string Truck::getTypeName() const { return "Truck"; }