#pragma once

#include "igrouper.h"
#include <map>
#include <string>

class TransportTypeGrouper : public IGrouper
{
    public:
        ~TransportTypeGrouper() override = default;

        TripBuckets groupTrips(const Trips& trips) const override;
};