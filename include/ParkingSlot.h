#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include <string>
#include "Enums.h"

/*
 * OOP Principle: Encapsulation
 * Represents a small singular parking unit resource within a specific zone.
 */
class ParkingSlot {
private:
    std::string slotId;
    std::string zone;
    VehicleType supportedType;
    SlotStatus status;

public:
    ParkingSlot(const std::string& id, const std::string& z, VehicleType type);

    std::string getSlotId() const;
    std::string getZone() const;
    VehicleType getSupportedType() const;
    SlotStatus getStatus() const;

    void setStatus(SlotStatus newStatus);
    void setZone(const std::string& newZone);
    void setSupportedType(VehicleType newType);
};

#endif // PARKINGSLOT_H