#pragma once

#include "iaggregator.h"

#include "valueObjects/speed.h"

// Calculates the average speed across all trips (total distance / total duration)
class SpeedAggregator : public IAggregator<Speed>
{
    public:
        AggregatorResult<Speed> aggregate(const Trips& trips) const override;
};