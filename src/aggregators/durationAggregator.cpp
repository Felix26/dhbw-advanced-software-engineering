#include "aggregators/durationAggregator.h"

#include "valueObjects/duration.h"

AggregatorResult<Duration> DurationAggregator::aggregate(const Trips& trips) const
{
    Duration totalDuration = Duration::fromMinutes(0);
    for (const auto& trip : trips)
    {
        totalDuration += trip->getDuration();
    }
    return {totalDuration, static_cast<int>(trips.size())};
}