#include "aggregators/countAggregator.h"

AggregatorResult<int> CountAggregator::aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const
{
    return {static_cast<int>(trips.size()), static_cast<int>(trips.size())};
}