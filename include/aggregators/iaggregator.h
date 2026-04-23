#pragma once

#include <vector>
#include <memory>

#include "trips/trip.h"

template<typename T>
struct AggregatorResult
{
    T aggregationValue;
    int aggregationCount;
};

template<typename T>
class IAggregator
{
    public:
        virtual ~IAggregator() = default;

        virtual AggregatorResult<T> aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const = 0;
};