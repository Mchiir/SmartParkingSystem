#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <variant>
#include <optional>

// ============================================================================
// 1. STRONGLY TYPED ENUMS & DATA STRUCTURES (FP STATE RECORDS)
// ============================================================================

enum class VehicleType {
    MOTORCYCLE,
    CAR,
    TRUCK
};

enum class SlotStatus {
    AVAILABLE,
    OCCUPIED
};

/*
 * In Functional Programming, structures act as immutable or mutable data records.
 * They hold pure data layout representation without encapsulating hidden behavior.
 */

struct ParkingSlot {
    std::string slotId;
    std::string zone;
    VehicleType supportedType;
    SlotStatus status;
};

struct ActiveParkingVehicle {
    std::string plateNumber;
    VehicleType type;
    std::time_t entryTime;
    std::string allocatedSlotId;
};

struct ParkingRecord {
    std::string plateNumber;
    VehicleType type;
    std::time_t entryTime;
    std::time_t exitTime;
    std::string slotId;
    long long durationHours;
    double feePaid;
};

// Application Global State Container Bundle
struct ParkingSystemState {
    std::vector<ParkingSlot> slots;
    std::unordered_map<std::string, ActiveParkingVehicle> activeVehicles;
    std::vector<ParkingRecord> history;
    double motorcycleRate = 500.0;
    double carRate = 1000.0;
    double truckRate = 2000.0;
};

// ============================================================================
// 2. FUNCTION PROTOTYPES (EXPLICIT STATE PASSING INTERFACES)
// ============================================================================

// Pure Utility & State Transformation Functions
std::string vehicleTypeToString(VehicleType type);
double getRateForType(VehicleType type, const ParkingSystemState& state);

// Input Validation & Processing Functions
std::string readString(const std::string& prompt);
int readInt(const std::string& prompt);
double readDouble(const std::string& prompt);

// Core System Domain Pure/Impure Mutation Functions
void addParkingSlot(ParkingSystemState& state);
void updateParkingSlot(ParkingSystemState& state);
void registerVehicleEntry(ParkingSystemState& state);
void processVehicleExit(ParkingSystemState& state);
void updateParkingRates(ParkingSystemState& state);

// View & Projection Queries (Const State References)
void displayAvailableSlots(const ParkingSystemState& state);
void displayParkedVehicles(const ParkingSystemState& state);
void displayAllSlots(const ParkingSystemState& state);
void displayVehicleHistory(const ParkingSystemState& state);
void displayDailyRevenue(const ParkingSystemState& state);

// Main Execution Context Loop
void executionLoop();

// ============================================================================
// 3. MAIN ENTRY POINT
// ============================================================================

int main() {
    // Standard execution loop launch context
    executionLoop();
    return 0;
}

// ============================================================================
// 4. FUNCTION DEFINITIONS
// ============================================================================

/*
 * High-order execution dispatcher managing system pipeline orchestration.
 * Threading global state record cleanly through standard execution scopes.
 */
void executionLoop() {
    ParkingSystemState state; // Root application state instantiation
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n====================================\n";
        std::cout << " SMART PARKING SYSTEM (FUNCTIONAL)\n";
        std::cout << "====================================\n";
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
        std::cout << "====================================\n";

        choice = readInt("Choice: ");

        // Explicit try-catch wrapping block preventing system down-time crashes
        try {
            switch (choice) {
                case 1:  addParkingSlot(state); break;
                case 2:  updateParkingSlot(state); break;
                case 3:  registerVehicleEntry(state); break;
                case 4:  processVehicleExit(state); break;
                case 5:  displayAvailableSlots(state); break;
                case 6:  displayParkedVehicles(state); break;
                case 7:  displayAllSlots(state); break;
                case 8:  displayVehicleHistory(state); break;
                case 9:  displayDailyRevenue(state); break;
                case 10: updateParkingRates(state); break;
                case 0:  std::cout << "Shutting down functional tracking matrix engine...\n"; break;
                default: std::cout << "Invalid structural menu selection map.\n"; break;
            }
        }
        catch (const std::runtime_error& err) {
            std::cout << "\n[FUNCTIONAL ERROR ACTION CANCELLED] " << err.what() << "\n";
        }
    }
}

/*
 * Pure helper mapper transforming enum parameters to readable output text strings.
 */
std::string vehicleTypeToString(VehicleType type) {
    switch (type) {
        case VehicleType::MOTORCYCLE: return "Motorcycle";
        case VehicleType::CAR:        return "Car";
        case VehicleType::TRUCK:      return "Truck";
    }
    return "Unknown";
}

/*
 * Pure query mapping expression retrieving configuration rates out of the context snapshot.
 */
double getRateForType(VehicleType type, const ParkingSystemState& state) {
    switch (type) {
        case VehicleType::MOTORCYCLE: return state.motorcycleRate;
        case VehicleType::CAR:        return state.carRate;
        case VehicleType::TRUCK:      return state.truckRate;
    }
    return 0.0;
}

// --- Dynamic IO Functional Data Parsers ---

std::string readString(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::getline(std::cin >> std::ws, val); // Consume leading whitespace buffers safely
    return val;
}

int readInt(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear(); // Clear stream failure flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid notation. Integer parameters required.\n";
    }
}

double readDouble(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid notation. Numerical currency float value format required.\n";
    }
}

// --- Domain Function Realizations ---

/*
 * State transformer function updating the vector buffer space layout.
 * DSA: O(N) linear search traversal check to ensure slot uniqueness.
 */
void addParkingSlot(ParkingSystemState& state) {
    std::string id = readString("Enter Unique Slot ID: ");
    if (id.empty()) throw std::runtime_error("Validation exception: Slot ID mapping criteria unmet.");

    // Lambda predicate checking layout for unique key criteria matching
    auto duplicate = std::any_of(state.slots.begin(), state.slots.end(), [&id](const ParkingSlot& s) {
        return s.slotId == id;
    });
    if (duplicate) throw std::runtime_error("Key conflict: Target structural element mapping already present.");

    std::string zone = readString("Enter Structural Zone Name: ");
    if (zone.empty()) throw std::runtime_error("Validation exception: Zone identifier cannot evaluate blank.");

    int typeChoice = readInt("Select Allowed Vehicle Type (0: Motorcycle, 1: Car, 2: Truck): ");
    if (typeChoice < 0 || typeChoice > 2) throw std::runtime_error("Out of range mapping identifier definition.");

    // Direct mutative state push matching procedural array adjustments
    state.slots.push_back(ParkingSlot{id, zone, static_cast<VehicleType>(typeChoice), SlotStatus::AVAILABLE});
    std::cout << "Structural allocation unit successfully loaded into context matrix.\n";
}

/*
 * State transformer search-and-mutate function modifying inline attributes.
 * DSA: O(N) sequential search evaluation.
 */
void updateParkingSlot(ParkingSystemState& state) {
    std::string id = readString("Enter Target Slot ID to Update: ");
    
    auto it = std::find_if(state.slots.begin(), state.slots.end(), [&id](const ParkingSlot& s) {
        return s.slotId == id;
    });
    if (it == state.slots.end()) throw std::runtime_error("Resource verification exception: Target layout missing.");

    std::string newZone = readString("Enter New Zone Name: ");
    int typeChoice = readInt("Select New Supported Vehicle Type (0: Motorcycle, 1: Car, 2: Truck): ");
    if (typeChoice < 0 || typeChoice > 2) throw std::runtime_error("Type mapping assignment parameter failed.");

    it->zone = newZone;
    it->supportedType = static_cast<VehicleType>(typeChoice); // Pure inline assignment mapping
    std::cout << "Structural state successfully updated.\n";
}

/*
 * Registry tracking transformer function.
 * DSA: O(1) average lookup checking hash index cache constraints; O(N) sequential slot search.
 */
void registerVehicleEntry(ParkingSystemState& state) {
    std::string plate = readString("Enter Vehicle Registration Plate Number: ");
    if (plate.empty()) throw std::runtime_error("Validation exception: License plate registration mismatch.");

    // Query hash collection map directly for duplicate records checking
    if (state.activeVehicles.find(plate) != state.activeVehicles.end()) {
        throw std::runtime_error("State restriction: Registration sequence active on localized tracker.");
    }

    int typeChoice = readInt("Select Vehicle Category (0: Motorcycle, 1: Car, 2: Truck): ");
    if (typeChoice < 0 || typeChoice > 2) throw std::runtime_error("Invalid classification assignment.");
    VehicleType vType = static_cast<VehicleType>(typeChoice);

    // Sequential matching search iteration loop mapping first structural hit
    ParkingSlot* assignedSlot = nullptr;
    for (auto& slot : state.slots) {
        if (slot.supportedType == vType && slot.status == SlotStatus::AVAILABLE) {
            assignedSlot = &slot;
            break;
        }
    }

    if (!assignedSlot) {
        std::cout << "System Allocation Alert: No available matching physical slots available.\n";
        return;
    }

    // Mutate internal state parameters 
    assignedSlot->status = SlotStatus::OCCUPIED; // Flag item segment locked
    std::time_t entryTime = std::time(nullptr);

    // Structural write entry tracking update using explicit functional mappings
    state.activeVehicles[plate] = ActiveParkingVehicle{plate, vType, entryTime, assignedSlot->slotId};
    std::cout << "Session registered. Resource matched to Slot: " << assignedSlot->slotId << "\n";
}

/*
 * Ledger mutation tracking transaction process engine.
 * DSA: O(1) map search retrieval lookup, O(1) historical append write execution log tracking.
 */
void processVehicleExit(ParkingSystemState& state) {
    std::string plate = readString("Enter Exiting Vehicle Plate Number: ");
    
    auto it = state.activeVehicles.find(plate);
    if (it == state.activeVehicles.end()) {
        throw std::runtime_error("Lookup processing error: Registry tracking index missing entry segment.");
    }

    const ActiveParkingVehicle& session = it->second;
    std::time_t exitTime = std::time(nullptr);

    // Core duration calculation using functional primitives
    double deltaSeconds = std::difftime(exitTime, session.entryTime);
    if (deltaSeconds < 0) deltaSeconds = 0;
    double continuousMinutes = deltaSeconds / 60.0;

    int mockHours = readInt("Simulate elapsed duration hours for billing (Enter 0 for authentic real-time duration): ");
    long long processedHours = 0;

    if (mockHours > 0) {
        processedHours = mockHours;
    } else {
        processedHours = static_cast<long long>(std::ceil(continuousMinutes / 60.0));
        if (processedHours == 0) processedHours = 1; // Floor billing unit parameter requirement
    }

    // Fee calculation logic passing lookup metrics downstream
    double calculationRate = getRateForType(session.type, state);
    double calculatedFee = processedHours * calculationRate;

    // Release layout allocations back to standard tracking maps
    std::string targetSlotId = session.allocatedSlotId;
    auto slotIt = std::find_if(state.slots.begin(), state.slots.end(), [&targetSlotId](const ParkingSlot& s) {
        return s.slotId == targetSlotId;
    });
    if (slotIt != state.slots.end()) {
        slotIt->status = SlotStatus::AVAILABLE; // Flag item tracking slot unlocked safely
    }

    // Append finalized transaction metadata record onto the system ledger array state 
    state.history.push_back(ParkingRecord{
        session.plateNumber, session.type, session.entryTime, exitTime, targetSlotId, processedHours, calculatedFee
    });

    std::cout << "\n====================================\n";
    std::cout << "   TRANSACTION RECEIPT (FUNCTIONAL)\n";
    std::cout << "====================================\n";
    std::cout << "Plate Registry : " << session.plateNumber << "\n";
    std::cout << "Vehicle Type   : " << vehicleTypeToString(session.type) << "\n";
    std::cout << "Billed Units   : " << processedHours << " Hour(s)\n";
    std::cout << "Total Cost     : " << std::fixed << std::setprecision(0) << calculatedFee << " RWF\n";
    std::cout << "====================================\n";

    // Evict tracking entity item record node out of active map cache layer
    state.activeVehicles.erase(it);
}

/*
 * Live state pricing matrix baseline context variables configuration transformation modifier.
 */
void updateParkingRates(ParkingSystemState& state) {
    double mRate = readDouble("Enter Motorcycle configuration price (RWF/Hr): ");
    double cRate = readDouble("Enter Car configuration price (RWF/Hr): ");
    double tRate = readDouble("Enter Truck configuration price (RWF/Hr): ");

    if (mRate < 0 || cRate < 0 || tRate < 0) {
        throw std::runtime_error("Validation exception: Configuration cost limits cannot scale negative.");
    }

    state.motorcycleRate = mRate;
    state.carRate = cRate;
    state.truckRate = tRate; // Context parameters updated without altering history values
    std::cout << "Operational baseline context configurations reassigned.\n";
}

// --- View Projection & Data Query Operations (Const Snapshot Reads) ---

/*
 * Iterates state definitions filtering vacant components.
 * DSA: O(N) sequential pass evaluation constraint.
 */
void displayAvailableSlots(const ParkingSystemState& state) {
    std::cout << "\n--- Vacant Structural Allotment Layouts ---\n";
    bool matched = false;
    for (const auto& slot : state.slots) {
        if (slot.status == SlotStatus::AVAILABLE) {
            std::cout << "Slot ID: " << slot.slotId << " | Sector Zone: " << slot.zone 
                      << " | Matching Form: " << vehicleTypeToString(slot.supportedType) << "\n";
            matched = true;
        }
    }
    if (!matched) std::cout << "All structured parking resources currently occupied.\n";
}

/*
 * Iterates map index values directly parsing memory allocations layout definitions.
 */
void displayParkedVehicles(const ParkingSystemState& state) {
    std::cout << "\n--- Tracked Inside Active Sessions Registry ---\n";
    if (state.activeVehicles.empty()) {
        std::cout << "No entity units registered context data fields tracking lines.\n";
        return;
    }
    for (const auto& [plate, vehicle] : state.activeVehicles) {
        std::cout << "Plate Target: " << plate << " | Type Variant: " << vehicleTypeToString(vehicle.type)
                  << " | Bound Location: " << vehicle.allocatedSlotId << "\n";
    }
}

/*
 * Global sweep structural tracking trace analyzer.
 */
void displayAllSlots(const ParkingSystemState& state) {
    std::cout << "\n--- Comprehensive Layout Space Matrix Review ---\n";
    if (state.slots.empty()) {
        std::cout << "Zero tracking resources configured setup blocks inside system state layers.\n";
        return;
    }
    for (const auto& slot : state.slots) {
        std::cout << "Slot Key: " << slot.slotId << " | Region Zone: " << slot.zone 
                  << " | Core Format: " << vehicleTypeToString(slot.supportedType) 
                  << " | Phase: " << (slot.status == SlotStatus::AVAILABLE ? "AVAILABLE" : "OCCUPIED") << "\n";
    }
}

/*
 * Reads historic ledger state.
 */
void displayVehicleHistory(const ParkingSystemState& state) {
    std::cout << "\n--- Auditing Archival System Ledger Review ---\n";
    if (state.history.empty()) {
        std::cout << "Audit trace log database tracking matrices are clear.\n";
        return;
    }
    for (const auto& log : state.history) {
        std::cout << "Plate Trace: " << log.plateNumber << " | Variant: " << vehicleTypeToString(log.type)
                  << " | Location Key: " << log.slotId << " | Elapsed Metric: " << log.durationHours 
                  << " Hrs | Settled Balance: " << log.feePaid << " RWF\n";
    }
}

/*
 * High-order reduction fold utility analyzing aggregate metrics over collection sequences.
 * DSA: O(N) evaluation time framework loop tracking sequences.
 */
void displayDailyRevenue(const ParkingSystemState& state) {
    double totalAccumulatedRevenue = 0.0;
    size_t transactionsLedgerCount = state.history.size();

    // Functional accumulation logic equivalent to a reduction stream fold operation
    for (const auto& accountingRecord : state.history) {
        totalAccumulatedRevenue += accountingRecord.feePaid;
    }

    std::cout << "\n====================================\n";
    std::cout << "   METRICS REVENUE AUDITING REPORT\n";
    std::cout << "====================================\n";
    std::cout << "Aggregated Gross Returns  : " << std::fixed << std::setprecision(0) << totalAccumulatedRevenue << " RWF\n";
    std::cout << "Processed Transactions    : " << transactionsLedgerCount << "\n";
    std::cout << "====================================\n";
}