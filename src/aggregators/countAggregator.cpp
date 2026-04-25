#include "aggregators/countAggregator.h"

AggregatorResult<Count> CountAggregator::aggregate(const Trips& trips) const
{
    return {Count(trips.size()), std::nullopt}; // Return count with no count, as it's not meaningful for count
}