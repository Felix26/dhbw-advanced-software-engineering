#pragma once

#include <vector>
#include <memory>

#include "trips/trip.h"

struct AggregatorResult
{
    int aggregationValue;
    int aggregationCount;
};

class IAggregator
{
    public:
        virtual ~IAggregator() = default;

        virtual AggregatorResult aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const = 0;
};