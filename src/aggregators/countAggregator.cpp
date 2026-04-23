#include "aggregators/countAggregator.h"

AggregatorResult<int> CountAggregator::aggregate(const Trips& trips) const
{
    return {static_cast<int>(trips.size()), static_cast<int>(trips.size())};
}