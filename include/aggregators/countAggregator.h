#pragma once

#include "aggregators/iaggregator.h"
#include "valueObjects/count.h"

class CountAggregator : public IAggregator<Count>
{
    public:
        AggregatorResult<Count> aggregate(const Trips& trips) const override;
};