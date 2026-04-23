#pragma once

#include "aggregators/iaggregator.h"

class DurationAggregator : public IAggregator
{
    public:
        AggregatorResult aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const override;
};