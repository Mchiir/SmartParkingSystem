/**
 * Parking Payments Record base class implementation
 */

#include "ParkingRecord.h"

ParkingRecord::ParkingRecord(const std::string& plate, VehicleType t, std::time_t entry, 
                             std::time_t exit, const std::string& sId, long long duration, double fee)
    : plateNumber(plate), type(t), entryTime(entry), exitTime(exit), 
      slotId(sId), durationHours(duration), feePaid(fee) {}

std::string ParkingRecord::getPlateNumber() const { return plateNumber; }
VehicleType ParkingRecord::getType() const { return type; }
std::time_t ParkingRecord::getEntryTime() const { return entryTime; }
std::time_t ParkingRecord::getExitTime() const { return exitTime; }
std::string ParkingRecord::getSlotId() const { return slotId; }
long long ParkingRecord::getDurationHours() const { return durationHours; }
double ParkingRecord::getFeePaid() const { return feePaid; }