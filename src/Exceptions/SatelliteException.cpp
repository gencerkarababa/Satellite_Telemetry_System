#include "Exceptions/SatelliteException.h"

SatelliteException::SatelliteException(const std::string& message)
    : std::runtime_error(message) {
}