#include "aggregators/speedAggregator.h"

#include <iostream>

#include "aggregators/durationAggregator.h"
#include "aggregators/distanceAggregator.h"

AggregatorResult<double> SpeedAggregator::aggregate(const std::vector<std::shared_ptr<Trip>> &trips) const
{
    DistanceAggregator distanceAggregator;
    DurationAggregator durationAggregator;

    auto distanceResult = distanceAggregator.aggregate(trips);
    auto durationResult = durationAggregator.aggregate(trips);

    if(distanceResult.aggregationCount == 0 || distanceResult.aggregationCount != durationResult.aggregationCount)
    {
        std::cerr << "Warning: No trips or mismatch in counts for distance and duration aggregation." << std::endl;
        return {0.0, 0}; // No trips or mismatch in counts, return 0 speed and output warning
    }

    // Calculate speed as distance divided by duration
    double speed = static_cast<double>(distanceResult.aggregationValue) / static_cast<double>(durationResult.aggregationValue);
    return {speed, distanceResult.aggregationCount};
}