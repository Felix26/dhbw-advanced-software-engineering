#include "aggregators/durationAggregator.h"

AggregatorResult<int> DurationAggregator::aggregate(const Trips& trips) const
{
    int totalDuration = 0;
    for (const auto& trip : trips)
    {
        totalDuration += trip->getDuration();
    }
    return {totalDuration, static_cast<int>(trips.size())};
}