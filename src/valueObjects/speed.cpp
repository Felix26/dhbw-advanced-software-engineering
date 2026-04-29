#include "valueObjects/speed.h"

#include <iomanip>

Speed::Speed(double speed) : mSpeed(speed) {}

double Speed::operator/(const Speed &other) const
{
    return this->mSpeed / other.mSpeed;
}

std::ostream &operator<<(std::ostream &os, const Speed &speed)
{
    os << std::fixed << std::setprecision(2) << speed.getSpeedInKmH() << " km/h";
    return os;
}

double Speed::getSpeedInKmH() const
{
    return mSpeed * 3.6; // Convert m/s to km/h
}

std::string Speed::getValueTypeName()
{
    return "Geschwindigkeit";
}

Speed Speed::operator+=(const Speed &other)
{
    this->mSpeed += other.mSpeed;
    return *this;
}

Speed Speed::operator/(double divisor) const
{
    return Speed(mSpeed / divisor);
}
