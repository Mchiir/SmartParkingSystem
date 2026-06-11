#ifndef ENUMS_H
#define ENUMS_H

#include <string>

/*
 * Strongly typed enums for type safety, avoiding implicit integer conversions and prevents logical bugs in system tracking.
 */

enum class VehicleType
{
    MOTORCYCLE,
    CAR,
    TRUCK
};

enum class SlotStatus
{
    AVAILABLE,
    OCCUPIED
};

// Helper utility to safely convert Enums to printable human-readable strings
inline std::string vehicleTypeToString(VehicleType type) {
    switch (type) {
        case VehicleType::MOTORCYCLE: return "Motorcycle";
        case VehicleType::CAR:        return "Car";
        case VehicleType::TRUCK:      return "Truck";
    }
    return "Unknown";
}

#endif // ENUMS_H