from pathlib import Path

def create_project_structure():
    # base root directory
    root = Path("./")

    # all explicit file paths relative to the root
    files = [
        root / "CMakeLists.txt",
        root / "README.md",
        # Include Headers
        root / "include" / "Enums.h",
        root / "include" / "Vehicle.h",
        root / "include" / "ParkingSlot.h",
        root / "include" / "ActiveParkingVehicle.h",
        root / "include" / "ParkingRecord.h",
        root / "include" / "ParkingException.h",
        root / "include" / "ParkingSystem.h",
        # Source Files
        root / "src" / "main.cpp",
        root / "src" / "Vehicle.cpp",
        root / "src" / "ParkingSlot.cpp",
        root / "src" / "ActiveParkingVehicle.cpp",
        root / "src" / "ParkingRecord.cpp",
        root / "src" / "ParkingSystem.cpp",
        # Documentation
        root / "docs" / "architecture.md",
        root / "docs" / "class-diagram.md",
        root / "docs" / "dsa-justification.md",
    ]

    print(f"Creating project structure under: {root.resolve()}")

    for file_path in files:
        # parent automatically extracts the subdirectories needed for the file
        file_path.parent.mkdir(parents=True, exist_ok=True)
        
        # Create an empty file (or leave it untouched if it already exists)
        file_path.touch()
        print(f"  [+] Created: {file_path}")

    print("\nSuccess! 'SmartParkingSystem' structure is fully generated.")

if __name__ == "__main__":
    create_project_structure()