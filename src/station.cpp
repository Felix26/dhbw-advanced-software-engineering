#include "station.h"

bool Station::operator==(const Station &other) const
{
    return this->mID == other.mID;
}
