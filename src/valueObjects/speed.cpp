#include "valueObjects/speed.h"

Speed::Speed(double speed) : mSpeed(speed) {}

std::ostream &operator<<(std::ostream &os, const Speed &speed)
{
    os << speed.mSpeed * 3.6 << " km/h";
    return os;
}