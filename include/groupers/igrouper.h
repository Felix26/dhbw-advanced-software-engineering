#pragma once

#include <vector>
#include <memory>
#include <map>

#include "trips/trip.h"

using TripBuckets = std::map<std::string, Trips>;

class IGrouper
{
    public:
        virtual ~IGrouper() = default;

        virtual TripBuckets groupTrips(const Trips& trips) const = 0;
};