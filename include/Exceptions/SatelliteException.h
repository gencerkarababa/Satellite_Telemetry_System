#pragma once

#include <stdexcept>
#include <string>

class SatelliteException : public std::runtime_error {
public:
    explicit SatelliteException(const std::string& message);
};