/**
 * ActiveParkingVehicle base class implementation
 */

#include "ActiveParkingVehicle.h"

ActiveParkingVehicle::ActiveParkingVehicle() 
    : plateNumber(""), type(VehicleType::CAR), entryTime(0), allocatedSlotId("") {}

ActiveParkingVehicle::ActiveParkingVehicle(const std::string& plate, VehicleType t, std::time_t entry, const std::string& slotId)
    : plateNumber(plate), type(t), entryTime(entry), allocatedSlotId(slotId) {}

std::string ActiveParkingVehicle::getPlateNumber() const { return plateNumber; }
VehicleType ActiveParkingVehicle::getType() const { return type; }
std::time_t ActiveParkingVehicle::getEntryTime() const { return entryTime; }
std::string ActiveParkingVehicle::getAllocatedSlotId() const { return allocatedSlotId; }