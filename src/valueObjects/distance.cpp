#include "valueObjects/distance.h"

#include <iomanip>

#include "valueObjects/speed.h"
#include "valueObjects/duration.h"

Distance::Distance(double distance) : mDistance(distance) {}

Distance Distance::fromMeters(double meters)
{
    return Distance(meters);
}

double Distance::getDistanceInMeters() const
{
    return mDistance;
}


Distance Distance::operator+(const Distance &other) const
{
    return Distance(this->mDistance + other.mDistance);
}

Distance &Distance::operator+=(const Distance &other)
{
    this->mDistance += other.mDistance;
    return *this;
}

Distance Distance::operator-(const Distance &other) const
{
    return Distance(this->mDistance - other.mDistance);
}

Distance &Distance::operator-=(const Distance &other)
{
    this->mDistance -= other.mDistance;
    return *this;
}

Distance Distance::operator*(double factor) const
{
    return Distance(this->mDistance * factor);
}

Distance &Distance::operator*=(double factor)
{
    this->mDistance *= factor;
    return *this;
}

Distance Distance::operator/(double divisor) const
{
    return Distance(this->mDistance / divisor);
}

Distance &Distance::operator/=(double divisor)
{
    this->mDistance /= divisor;
    return *this;
}

Speed Distance::operator/(const Duration &duration) const
{
    double speedInMetersPerSecond = this->mDistance / duration.getDurationInSeconds();
    return Speed(speedInMetersPerSecond);
}

double Distance::operator/(const Distance &other) const
{
    return this->mDistance / other.mDistance;
}

std::string Distance::getValueTypeName()
{
    return "Distanz";
}

std::ostream &operator<<(std::ostream &os, const Distance &distance)
{
    if(distance.getDistanceInMeters() >= 1000)
    {
        os << std::setprecision(2) << std::fixed << distance.getDistanceInMeters() / 1000 << " km";
    }
    else
    {
        os << std::setprecision(0) << std::fixed << distance.getDistanceInMeters() << " m";
    }
    return os;
}