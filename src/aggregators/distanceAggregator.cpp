#include "aggregators/distanceAggregator.h"

AggregatorResult<int> DistanceAggregator::aggregate(const std::vector<std::shared_ptr<Trip>>& trips) const
{
    int totalDistance = 0;
    for (const auto& trip : trips)
    {
        totalDistance += trip->getDistance();
    }
    return {totalDistance, static_cast<int>(trips.size())};
}