#include <cassert>

#include "parser/parserFactory.h"
#include "aggregators/distanceAggregator.h"

int main()
{
    auto parser = ParserFactory::createMockParser();

    auto trips = parser->parse();

    DistanceAggregator distanceAggregator;
    auto result = distanceAggregator.aggregate(trips);

    assert(result.aggregationValue == 276600); // Gesamtdistanz der Trips in Metern
    assert(result.aggregationCount == 5); // Anzahl der Trips
    return 0;
}