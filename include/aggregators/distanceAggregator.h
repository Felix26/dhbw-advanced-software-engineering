#pragma once

#include "aggregators/iaggregator.h"

class DistanceAggregator : public IAggregator<int>
{
    public:
        AggregatorResult<int> aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const override;
};