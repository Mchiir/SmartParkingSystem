#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include "ParkingSlot.h"
#include "ActiveParkingVehicle.h"
#include "ParkingRecord.h"

/*
 * Central Domain Orchestrator managing core in-memory state engines, allocations, and configurations.
 */
class ParkingSystem {
private:
    // Core DSA Structures
    std::vector<ParkingSlot> slots;
    std::unordered_map<std::string, ActiveParkingVehicle> activeVehicles; 
    std::vector<ParkingRecord> history;

    // Pricing rates state initial configurations (RWF/Hour)
    double motorcycleRate{500.0};
    double carRate{1000.0};
    double truckRate{2000.0};

    // Clean structural helper functions for parsing user inputs safely
    bool isValidPlateNumber(const std::string& plate);
    std::string readStringInput(const std::string& prompt);
    int readIntInput(const std::string& prompt);
    double readDoubleInput(const std::string& prompt);

public:
    ParkingSystem() = default;

    // Business System Functions
    void addParkingSlot();
    void updateParkingSlot();
    void registerVehicleEntry();
    void processVehicleExit();
    void updateParkingRates();
    void displayAvailableSlots() const;
    void displayParkedVehicles() const;
    void displayVehicleHistory() const;
    void displayDailyRevenue() const;
    void displayAllSlots() const;
    
    // Core Interface Runner Loop
    void menu();
};

#endif // PARKINGSYSTEM_H