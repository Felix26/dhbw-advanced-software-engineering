#include <cassert>
#include <iostream>

#include "parser/parserFactory.h"
#include "aggregators/speedAggregator.h"

int main()
{
    auto parser = ParserFactory::createMockParser();

    auto trips = parser->parse();

    SpeedAggregator speedAggregator;
    auto result = speedAggregator.aggregate(trips);

    assert(result.aggregationValue.getSpeedInKmH() > 107.76 && result.aggregationValue.getSpeedInKmH() < 107.77);
    assert(result.aggregationCount == std::nullopt);
    return 0;
}