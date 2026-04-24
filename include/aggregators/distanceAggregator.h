#pragma once

#include "aggregators/iaggregator.h"

#include "valueObjects/duration.h"

class DistanceAggregator : public IAggregator<Distance>
{
    public:
        AggregatorResult<Distance> aggregate(const Trips& trips) const override;
};