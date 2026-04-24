#include "valueObjects/speed.h"

Speed::Speed(double speed) : mSpeed(speed) {}

std::ostream &operator<<(std::ostream &os, const Speed &speed)
{
    os << speed.mSpeed * 3.6 << " km/h";
    return os;
}

double Speed::getSpeedInKmH() const
{
    return mSpeed * 3.6; // Convert m/s to km/h
}