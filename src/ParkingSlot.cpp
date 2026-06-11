/**
 * ParkingSlot base class implementation
 */

#include "ParkingSlot.h"

ParkingSlot::ParkingSlot(const std::string& id, const std::string& z, VehicleType type)
    : slotId(id), zone(z), supportedType(type), status(SlotStatus::AVAILABLE) {}

std::string ParkingSlot::getSlotId() const { return slotId; }
std::string ParkingSlot::getZone() const { return zone; }
VehicleType ParkingSlot::getSupportedType() const { return supportedType; }
SlotStatus ParkingSlot::getStatus() const { return status; }

void ParkingSlot::setStatus(SlotStatus newStatus) { status = newStatus; }
void ParkingSlot::setZone(const std::string& newZone) { zone = newZone; }
void ParkingSlot::setSupportedType(VehicleType newType) { supportedType = newType; }