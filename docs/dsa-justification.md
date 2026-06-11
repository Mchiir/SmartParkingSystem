# Data Structures and Algorithms Used

This engine relies on standard library memory layouts to enforce real-time performance guarantees under heavy concurrency contexts.

### 1. Vector Resizable Continuous Buffer Storage Layout (`std::vector<ParkingSlot>`)
* **Usage Context**: Holds tracking entities for system space definitions.
* **Complexity Performance Matrix**: 
  * Append Initialization: $O(1)$ amortized allocation tracking.
  * Structural Scanning/Updates: $O(N)$ sequential operations.
* **Why used?**: for input efficiency and resizable properties

### 2. Amortized Constant Hash Hash-Map Lookup (`std::unordered_map<std::string, ActiveParkingVehicle>`)
* **Usage Context**: Real-time registry indexing tracking currently parked vehicles via unique license registration keys.
* **Complexity Performance Matrix**: 
  * Registry Check/Lookup: $O(1)$ average computational overhead.
  * Node Drops/Eviction operations: $O(1)$ memory mapping transformations.
* **Why used?**: Efficient to lookups and manipulations

### 3. Append-Only Secure Record Vector Array (`std::vector<ParkingRecord>`)
* **Usage Context**: Audit logging history tracker for transaction validation.
* **Complexity Performance Matrix**: 
  * Log Write Entry: $O(1)$ constant write operations.
  * Global Sweep Analysis: $O(N)$ full system evaluations.
* **Why used?**: for input efficiency and resizable properties