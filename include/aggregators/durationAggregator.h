#pragma once

#include "aggregators/iaggregator.h"

class DurationAggregator : public IAggregator<int>
{
    public:
        AggregatorResult<int> aggregate(const Trips& trips) const override;
};