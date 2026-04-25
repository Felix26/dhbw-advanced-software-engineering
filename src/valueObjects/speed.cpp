#include "valueObjects/speed.h"

#include <iomanip>

Speed::Speed(double speed) : mSpeed(speed) {}

std::ostream &operator<<(std::ostream &os, const Speed &speed)
{
    os << std::fixed << std::setprecision(2) << speed.getSpeedInKmH() << " km/h";
    return os;
}

double Speed::getSpeedInKmH() const
{
    return mSpeed * 3.6; // Convert m/s to km/h
}