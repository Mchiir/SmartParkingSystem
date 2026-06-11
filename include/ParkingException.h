#ifndef PARKINGEXCEPTION_H
#define PARKINGEXCEPTION_H

#include <stdexcept>
#include <string>

/*
 * Custom runtime application exception layer.
 * Isolates standard C++ runtime exceptions from specific smart parking system domain failures.
 * i.e it's a domain-specific exception
 */
class ParkingException : public std::runtime_error {
public:
    explicit ParkingException(const std::string& message) 
        : std::runtime_error(message) {}
};

#endif // PARKINGEXCEPTION_H