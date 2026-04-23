#pragma once

#include "iaggregator.h"

// Calculates the average speed across all trips (total distance / total duration)
class SpeedAggregator : public IAggregator<double>
{
    public:
        AggregatorResult<double> aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const override;
};