#include "station.h"

bool Station::operator==(const Station &other) const
{
    return this->mID == other.mID;
}

std::ostream &operator<<(std::ostream &os, const Station &station)
{
    os << station.getName();
    return os;
}