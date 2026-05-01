#include <cassert>

#include "parser/parserFactory.h"
#include "aggregators/distanceAggregator.h"
#include "aggregators/durationAggregator.h"
#include "aggregators/speedAggregator.h"

int main()
{
    auto parser = ParserFactory::createMockParser();

    auto trips = parser->parse();

    DistanceAggregator distanceAggregator;
    auto result = distanceAggregator.aggregate(trips);

    assert(result.aggregationValue == Distance::fromMeters(276600)); // Gesamtdistanz der Trips in Metern
    assert(result.aggregationCount == 5); // Anzahl der Trips

    DurationAggregator durationAggregator;
    auto result2 = durationAggregator.aggregate(trips);

    assert(result2.aggregationValue == Duration::fromMinutes(154)); // Gesamtdauer der Trips in Minuten
    assert(result2.aggregationCount == 5); // Anzahl der Trips

    SpeedAggregator speedAggregator;
    auto result3 = speedAggregator.aggregate(trips);

    assert(result3.aggregationValue.getSpeedInKmH() > 107.76 && result3.aggregationValue.getSpeedInKmH() < 107.77);
    assert(result3.aggregationCount == std::nullopt);
    return 0;
}