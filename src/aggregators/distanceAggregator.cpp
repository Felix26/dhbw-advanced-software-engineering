#include "aggregators/distanceAggregator.h"

#include "valueObjects/distance.h"

AggregatorResult<Distance> DistanceAggregator::aggregate(const Trips& trips) const
{
    Distance totalDistance = Distance::fromMeters(0);
    for (const auto& trip : trips)
    {
        totalDistance += trip->getDistance();
    }
    return {Distance(totalDistance), static_cast<int>(trips.size())};
}