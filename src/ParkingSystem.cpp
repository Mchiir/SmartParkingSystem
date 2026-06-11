/**
 * System Main interface
 */

#include "ParkingSystem.h"
#include "Vehicle.h"
#include "ParkingException.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <limits>

/*
 * Helper utility function to securely read strings
 */
std::string ParkingSystem::readStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin >> std::ws, value);
    return value;
}

/*
 * Helper utility function to securely read integers
 */
int ParkingSystem::readIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input numeric configuration format. Retry.\n";
    }
}

/*
 * Helper utility function to securely read currency fractions
 */
double ParkingSystem::readDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid currency notation. Retry.\n";
    }
}

/*
 * Configure Parking Slot
 * DSA Complexity: O(N) check for uniqueness, O(1) insertion to back of std::vector.
 */
void ParkingSystem::addParkingSlot() {
    std::string id = readStringInput("Enter Unique Slot ID (e.g., RCA-FRONT-001): ");
    if (id.empty()) throw ParkingException("Slot ID cannot be empty, verification failed.");

    for (const auto& slot : slots) {
        if (slot.getSlotId() == id) {
            throw ParkingException("Duplicate Slot ID mapping error: " + id + " already exists.");
        }
    }

    std::string zone = readStringInput("Enter Structural Zone Name (e.g., RCA-FRONT): ");
    if (zone.empty()) throw ParkingException("Zone declaration value cannot be empty.");

    std::cout << "Select Supported Vehicle Type (0: Motorcycle, 1: Car, 2: Truck): ";
    int typeChoice = readIntInput("Choice: ");
    if (typeChoice < 0 || typeChoice > 2) throw ParkingException("Invalid vehicle type classification.");

    VehicleType type = static_cast<VehicleType>(typeChoice);
    slots.emplace_back(id, zone, type);
    std::cout << "Slot successfully configured and registered.\n";
}

/*
 * Update Parking Slot
 * DSA Complexity: O(N) structural sweep.
 */
void ParkingSystem::updateParkingSlot() {
    std::string id = readStringInput("Enter Target Slot ID to Update: ");
    auto it = std::find_if(slots.begin(), slots.end(), [&id](const ParkingSlot& s) {
        return s.getSlotId() == id;
    });

    if (it == slots.end()) throw ParkingException("Target Slot configuration not found.");

    std::string newZone = readStringInput("Enter New Zone Name: ");
    if (newZone.empty()) throw ParkingException("Zone declaration value cannot be empty.");

    int typeChoice = readIntInput("Select New Supported Vehicle Type (0: Motorcycle, 1: Car, 2: Truck): ");
    if (typeChoice < 0 || typeChoice > 2) throw ParkingException("Invalid vehicle type configuration.");

    it->setZone(newZone);
    it->setSupportedType(static_cast<VehicleType>(typeChoice));
    std::cout << "Slot data safely updated.\n";
}

/*
 * Register Vehicle Entry
 * DSA Complexity: Slot allocation selection is O(N) sequential/linear search;
 * Map persistence insertion is O(1).
 */
void ParkingSystem::registerVehicleEntry() {
    std::string plate = readStringInput("Enter Vehicle Registration Plate Number: ");
    if (plate.empty()) throw ParkingException("Plate registration entry cannot be blank.");

    // Validation check preventing duplicate entries
    if (activeVehicles.find(plate) != activeVehicles.end()) {
        throw ParkingException("Validation Error: Vehicle with plate " + plate + " is already active inside system.");
    }

    int typeChoice = readIntInput("Select Vehicle Registration Category (0: Motorcycle, 1: Car, 2: Truck): ");
    if (typeChoice < 0 || typeChoice > 2) throw ParkingException("Invalid vehicle type.");
    VehicleType vehicleType = static_cast<VehicleType>(typeChoice);

    // --- Runtime Polymorphism Demonstration Code Block ---
    Vehicle* polyVehicle = nullptr;
    if (vehicleType == VehicleType::MOTORCYCLE) polyVehicle = new Motorcycle(plate);
    else if (vehicleType == VehicleType::CAR)       polyVehicle = new Car(plate);
    else if (vehicleType == VehicleType::TRUCK)     polyVehicle = new Truck(plate);

    if (polyVehicle) {
        std::cout << "\n[System Task] Mapping incoming vehicle allocation for entry: " 
                  << polyVehicle->getTypeName() << " (" << polyVehicle->getPlateNumber() << ")\n";
        delete polyVehicle; // Clean up allocations instantly; runtime trace resolved.
    }
    // --------------------------------------------------------

    // Sequential/linear Allocation Algorithm: Match first available compatible target slot
    ParkingSlot* allocatedSlot = nullptr;
    for (auto& slot : slots) {
        if (slot.getSupportedType() == vehicleType && slot.getStatus() == SlotStatus::AVAILABLE) {
            allocatedSlot = &slot;
            break;
        }
    }

    if (!allocatedSlot) {
        std::cout << "Allocation Notice: No available " << vehicleTypeToString(vehicleType) << " entry slots ready.\n";
        return;
    }

    std::time_t entryTime = std::time(nullptr);
    allocatedSlot->setStatus(SlotStatus::OCCUPIED); // Update status flag

    // Maintain tracking registry state
    activeVehicles[plate] = ActiveParkingVehicle(plate, vehicleType, entryTime, allocatedSlot->getSlotId());
    std::cout << "Success: Assigned Slot ID " << allocatedSlot->getSlotId() << " in Zone " << allocatedSlot->getZone() << ".\n";
}

/*
 * Process Vehicle Exit
 * DSA Complexity: Lookup: O(1) via unordered_map; History tracking: O(1) append.
 */
void ParkingSystem::processVehicleExit() {
    std::string plate = readStringInput("Enter Exiting Vehicle Plate Number: ");
    auto it = activeVehicles.find(plate);
    if (it == activeVehicles.end()) {
        throw ParkingException("Processing error: Active vehicle entry mapping not found.");
    }

    const ActiveParkingVehicle& active = it->second;
    std::time_t entryTime = active.getEntryTime();
    std::time_t exitTime = std::time(nullptr);

    // calculate difference in seconds
    double differenceSeconds = std::difftime(exitTime, entryTime);
    if (differenceSeconds < 0) differenceSeconds = 0;

    // Convert seconds to minutes for ceiling/rounding
    double minutes = differenceSeconds / 60.0;
    
    /*
     * custom hours spent input
     */
    int mockHours = readIntInput("Enter duration hours spent for billing (Otherwise Enter 0 for authentic/actual real-time duration): ");
    
    long long billedHours = 0;
    if (mockHours > 0) {
        billedHours = mockHours;
    } else {
        billedHours = static_cast<long long>(std::ceil(minutes / 60.0));
        if (billedHours == 0) billedHours = 1; // 0.xxx -> 1
    }

    // determine rate to use in fee calculation
    double calculationRate = 0.0;
    switch (active.getType()) {
        case VehicleType::MOTORCYCLE: calculationRate = motorcycleRate; break;
        case VehicleType::CAR:        calculationRate = carRate;        break;
        case VehicleType::TRUCK:      calculationRate = truckRate;      break;
    }

    double finalFee = billedHours * calculationRate;

    // Release allocated parking unit slot
    std::string assignedSlotId = active.getAllocatedSlotId();
    for (auto& slot : slots) {
        if (slot.getSlotId() == assignedSlotId) {
            slot.setStatus(SlotStatus::AVAILABLE);
            break;
        }
    }

    // Commit historical logging instance
    history.emplace_back(active.getPlateNumber(), active.getType(), entryTime, exitTime, assignedSlotId, billedHours, finalFee);

    // Display summary output
    std::cout << "\n--- VEHICLE EXIT SUMMARY ---\n";
    std::cout << "Plate Number  : " << active.getPlateNumber() << "\n";
    std::cout << "Vehicle Type  : " << vehicleTypeToString(active.getType()) << "\n";
    std::cout << "Assigned Slot : " << assignedSlotId << "\n";
    std::cout << "Total Hours   : " << billedHours << " Hour(s)\n";
    std::cout << "Parking Fee   : " << std::fixed << std::setprecision(0) << finalFee << " RWF\n";

    // Drop tracking reference record cleanly from structural mapping cache
    activeVehicles.erase(it);
}

/*
 * Show Available Slots
 * DSA Complexity: O(N) parking unit evaluation.
 */
void ParkingSystem::displayAvailableSlots() const {
    std::cout << "\n--- Available Parking Slots ---\n";
    bool found = false;
    for (const auto& slot : slots) {
        if (slot.getStatus() == SlotStatus::AVAILABLE) {
            std::cout << "Slot ID: " << slot.getSlotId() << " | Zone: " << slot.getZone() 
                      << " | Allowed Type: " << vehicleTypeToString(slot.getSupportedType()) << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No slots are currently available.\n";
}

/*
 * Show Parked Vehicles
 * DSA Complexity: O(N) mapping element iterations.
 */
void ParkingSystem::displayParkedVehicles() const {
    std::cout << "\n--- Registered Active Vehicles ---\n";
    if (activeVehicles.empty()) {
        std::cout << "No vehicles are currently parked.\n";
        return;
    }
    for (const auto& [plate, vehicle] : activeVehicles) {
        std::cout << "Plate: " << plate << " | Type: " << vehicleTypeToString(vehicle.getType())
                  << " | Occupying Slot: " << vehicle.getAllocatedSlotId() << "\n";
    }
}

/*
 * Show All Slots
 * Complete parking unit breakdown overview.
 */
void ParkingSystem::displayAllSlots() const {
    std::cout << "\n--- All Parking Slots ---\n";
    if (slots.empty()) {
        std::cout << "No slots configured in memory yet.\n";
        return;
    }
    for (const auto& slot : slots) {
        std::cout << "Slot ID: " << slot.getSlotId() << " | Zone: " << slot.getZone() 
                  << " | Category: " << vehicleTypeToString(slot.getSupportedType()) 
                  << " | Status: " << (slot.getStatus() == SlotStatus::AVAILABLE ? "AVAILABLE" : "OCCUPIED") << "\n";
    }
}

/*
 * Show Vehicle History
 * Traverses historical ledger vector logs.
 */
void ParkingSystem::displayVehicleHistory() const {
    std::cout << "\n--- Vehicle History Records ---\n";
    if (history.empty()) {
        std::cout << "No Any Vehicle History Records found.\n";
        return;
    }
    for (const auto& rec : history) {
        std::cout << "Plate: " << rec.getPlateNumber() << " | Type: " << vehicleTypeToString(rec.getType())
                  << " | Slot: " << rec.getSlotId() << " | Duration: " << rec.getDurationHours() 
                  << " Hrs | Paid: " << rec.getFeePaid() << " RWF\n";
    }
}

/*
 * Show Daily Revenue
 * Calculates transaction aggregates across Vehicle history records.
 * DSA Complexity: O(N)
 */
void ParkingSystem::displayDailyRevenue() const {
    double totalRevenue = 0.0;
    size_t transactionsCount = history.size();

    for (const auto& record : history) {
        totalRevenue += record.getFeePaid();
    }

    std::cout << "\n--- DAILY REVENUE REPORT ---\n";
    std::cout << "Total Revenue Generated   : " << std::fixed << std::setprecision(0) << totalRevenue << " RWF\n";
    std::cout << "Completed Transactions    : " << transactionsCount << "\n";
}

/*
 * Update Parking Prices
 * only affects future bills
 */
void ParkingSystem::updateParkingRates() {
    double mRate = readDoubleInput("Enter target configuration fee rate for Motorcycle (RWF/Hr): ");
    double cRate = readDoubleInput("Enter target configuration fee rate for Car (RWF/Hr): ");
    double tRate = readDoubleInput("Enter target configuration fee rate for Truck (RWF/Hr): ");

    if (mRate < 0 || cRate < 0 || tRate < 0) {
        throw ParkingException("Validation failure: Rate can not be zero or less.");
    }

    motorcycleRate = mRate;
    carRate = cRate;
    truckRate = tRate;
    std::cout << "Pricing successfully updated.\n";
}

/*
 * Main Interface for the system
 */
void ParkingSystem::menu() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- SMART PARKING MANAGEMENT SYSTEM ---\n";
        std::cout << "1. Configure Parking Slot\n";
        std::cout << "2. Update Parking Slot\n";
        std::cout << "3. Register Vehicle Entry\n";
        std::cout << "4. Process Vehicle Exit\n\n";
        std::cout << "5. Show Available Slots\n";
        std::cout << "6. Show Parked Vehicles\n";
        std::cout << "7. Show All Slots\n\n";
        std::cout << "8. Show Vehicle History\n";
        std::cout << "9. Show Daily Revenue\n\n";
        std::cout << "10. Update Parking Prices\n";
        std::cout << "0. Exit\n";
        
        choice = readIntInput("Choice: ");

        try {
            switch (choice) {
                case 1:  addParkingSlot(); break;
                case 2:  updateParkingSlot(); break;
                case 3:  registerVehicleEntry(); break;
                case 4:  processVehicleExit(); break;
                case 5:  displayAvailableSlots(); break;
                case 6:  displayParkedVehicles(); break;
                case 7:  displayAllSlots(); break;
                case 8:  displayVehicleHistory(); break;
                case 9:  displayDailyRevenue(); break;
                case 10: updateParkingRates(); break;
                case 0:  std::cout << "Terminating Smart Parking Management System Engine...\n"; break;
                default: std::cout << "Invalid selection. Please choose a valid menu number.\n"; break;
            }
        }
        catch (const ParkingException& ex) {
            std::cout << "\n[APPLICATION ERROR] " << ex.what() << "\n";
        }
        catch (const std::exception& ex) {
            std::cout << "\n[SYSTEM CRITICAL RUNTIME EXCEPTION] " << ex.what() << "\n";
        }
    }
}