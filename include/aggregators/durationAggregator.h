#pragma once

#include "aggregators/iaggregator.h"

#include "valueObjects/duration.h"

class DurationAggregator : public IAggregator<Duration>
{
    public:
        AggregatorResult<Duration> aggregate(const Trips& trips) const override;
};