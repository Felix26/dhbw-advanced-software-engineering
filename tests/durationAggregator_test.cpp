#include <cassert>

#include "parser/parserFactory.h"
#include "aggregators/durationAggregator.h"

int main()
{
    auto parser = ParserFactory::createMockParser();

    auto trips = parser->parse();

    DurationAggregator durationAggregator;
    auto result = durationAggregator.aggregate(trips);

    assert(result.aggregationValue == Duration::fromMinutes(154)); // Gesamtdauer der Trips in Minuten
    assert(result.aggregationCount == 5); // Anzahl der Trips
    return 0;
}