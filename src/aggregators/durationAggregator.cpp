#include "aggregators/durationAggregator.h"

AggregatorResult DurationAggregator::aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const
{
    int totalDuration = 0;
    for (const auto& trip : trips)
    {
        totalDuration += trip->getDuration();
    }
    return {totalDuration, static_cast<int>(trips.size())};
}