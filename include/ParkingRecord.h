#ifndef PARKINGRECORD_H
#define PARKINGRECORD_H

#include <string>
#include <ctime>
#include "Enums.h"

/*
 * Immutable historical ledger record representing a closed and paid transaction.
 * Designed with strict read-only properties (no setters) ensuring auditing stability and reliability.
 */
class ParkingRecord {
private:
    std::string plateNumber;
    VehicleType type;
    std::time_t entryTime;
    std::time_t exitTime;
    std::string slotId;
    long long durationHours;
    double feePaid;

public:
    ParkingRecord(const std::string& plate, VehicleType t, std::time_t entry, 
                  std::time_t exit, const std::string& sId, long long duration, double fee);

    std::string getPlateNumber() const;
    VehicleType getType() const;
    std::time_t getEntryTime() const;
    std::time_t getExitTime() const;
    std::string getSlotId() const;
    long long getDurationHours() const;
    double getFeePaid() const;
};

#endif // PARKINGRECORD_H