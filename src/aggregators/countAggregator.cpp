#include "aggregators/countAggregator.h"

AggregatorResult<int> CountAggregator::aggregate(const Trips& trips) const
{
    return {static_cast<int>(trips.size()), std::nullopt}; // Return count with no count, as it's not meaningful for count
}