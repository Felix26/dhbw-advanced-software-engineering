#include "aggregators/speedAggregator.h"

#include <iostream>

#include "aggregators/durationAggregator.h"
#include "aggregators/distanceAggregator.h"
#include "valueObjects/speed.h"
#include "valueObjects/duration.h"
#include "valueObjects/distance.h"

AggregatorResult<Speed> SpeedAggregator::aggregate(const Trips &trips) const
{
    DistanceAggregator distanceAggregator;
    DurationAggregator durationAggregator;

    auto distanceResult = distanceAggregator.aggregate(trips); // distance in meters
    auto durationResult = durationAggregator.aggregate(trips); // duration in minutes

    if(distanceResult.aggregationCount == 0 || distanceResult.aggregationCount != durationResult.aggregationCount)
    {
        std::cerr << "Warning: No trips or mismatch in counts for distance and duration aggregation." << std::endl;
        return {Distance::fromMeters(0) / Duration::fromMinutes(1), 0}; // No trips or mismatch in counts, return 0 speed and output warning
    }

    // Calculate speed as distance divided by duration
    Speed speed = distanceResult.aggregationValue / durationResult.aggregationValue;
    return {speed, std::nullopt}; // Return speed with no count, as it's not meaningful for average speed
}