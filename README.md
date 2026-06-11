# Smart Parking Management System

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support/17)
[![Build System](https://img.shields.io/badge/Build%20System-CMake%20%2B%20Ninja-orange.svg)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-green.svg)]()

An enterprise-grade, real-time context-aware command line operational system built to manage parking infrastructure allocations.

---

## Technical Highlights & Applied Pillars

### 1. Object-Oriented Software Engineering Principles
* **Encapsulation**: Private class properties are protected against untrusted state modification, utilizing read-only getters and structured internal validation methods.
* **Abstraction**: `Vehicle` functions as an abstract base class, exposing an interface wrapper signature while hiding low-level implementation details.
* **Inheritance**: `Motorcycle`, `Car`, and `Truck` cleanly derive common attributes from the base `Vehicle` definition.
* **Polymorphism**: Vehicle derived classes implement virtual functions based on Object type during vehicle parsing entry registration workflows.

### 2. Data Structures & Architectural Layout Efficiency Matrix
* **`std::vector<ParkingSlot>`**: Used for space allocation layouts; provides high cache locality for scanning operations.
* **`std::unordered_map<std::string, ActiveParkingVehicle>`**: Maps license plates directly to active sessions for fast $O(1)$ exit validation lookups.
* **`std::vector<ParkingRecord>`**: An append-only historical database tracker that preserves audit integrity.

---

## Quick Start Build & Execution Instructions

### System Environment Requirements
* C++17 compliant compiler (`gcc-9+`, `clang-9+`, `MSYS2 20260322+` or `MSVC 2019+`)
* CMake tools installation version `3.15+`
* Ninja Build execution tool binaries

#### MSYS2 UCRT64 Setup (Windows)

Recommended environment:

- MSYS2 UCRT64 shell
- Packages:

```bash
pacman -Syu
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

Verify:

```bash
g++ --version
cmake --version
ninja --version
```

### Build Pipeline Generation Commands
```bash
# Generate the compilation build matrix parameters using Ninja build targets
cmake -B build -G Ninja
```

### Compile the target solution components executable binary image
```bash
cmake --build build
```

### Running the Executable Binary Command
```bash
./build/SmartParkingSystem.exe
```

> windows
```powershell
build\SmartParkingSystem.exe
```

## Operational Workflow Reference Guide

- Initialize Slots (Option 1): Set up test spaces (e.g., RCA-FRONT-001, RCA-FRONT, Type 1 [Car]).
- Park a Vehicle (Option 3): Register a plate number (e.g., RAC123A or RAD123A). The allocation algorithm assigns the first matching available slot.
- Simulate Exit Processing (Option 4): Enter the plate number during exit processing. You can optionally simulate elapsed time blocks to verify calculation logic.
- Review Revenue Metrics (Option 9): Check the aggregated financial metrics from all completed transactions.

## Documentation

- [Architecture diagram](./docs/architecture.md)
- [Class diagram](./docs/class-diagram.md)
- [Data structures](./docs/dsa-justification.md)