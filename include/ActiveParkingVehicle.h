#ifndef ACTIVEPARKINGVEHICLE_H
#define ACTIVEPARKINGVEHICLE_H

#include <string>
#include <ctime>
#include "Enums.h"

/*
 * Encapsulates the tracking parameters for a live vehicle entry.
 * No setter, to retain exact record properties and shield from state variation during operational pricing adjustments.
 */
class ActiveParkingVehicle {
private:
    std::string plateNumber;
    VehicleType type;
    std::time_t entryTime;
    std::string allocatedSlotId;

public:
    // Required default constructor for std::unordered_map dynamic generation buckets
    ActiveParkingVehicle();
    
    ActiveParkingVehicle(const std::string& plate, VehicleType t, std::time_t entry, const std::string& slotId);

    std::string getPlateNumber() const;
    VehicleType getType() const;
    std::time_t getEntryTime() const;
    std::string getAllocatedSlotId() const;
};

#endif // ACTIVEPARKINGVEHICLE_H