cmake_minimum_required(VERSION 3.15)
project(SmartParkingSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compiler warnings for code quality preservation
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Vehicle.cpp
    src/ParkingSlot.cpp
    src/ActiveParkingVehicle.cpp
    src/ParkingRecord.cpp
    src/ParkingSystem.cpp
)

add_executable(SmartParkingSystem ${SOURCES})