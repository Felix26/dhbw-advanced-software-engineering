#include "valueObjects/station.h"

bool Station::operator==(const Station &other) const
{
    return this->mName == other.mName;
}

std::string Station::getKeyTypeName()
{
    return "Station";
}

std::ostream &operator<<(std::ostream &os, const Station &station)
{
    os << station.getName();
    return os;
}