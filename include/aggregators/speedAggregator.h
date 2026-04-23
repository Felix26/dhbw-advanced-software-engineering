#pragma once

#include "iaggregator.h"

// Calculates the average speed across all trips (total distance / total duration)
class SpeedAggregator : public IAggregator<double>
{
    public:
        AggregatorResult<double> aggregate(const Trips& trips) const override;
};