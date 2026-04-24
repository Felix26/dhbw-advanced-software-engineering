#include <iostream>
#include <map>

#include "groupers/universalGrouper.h"
#include "groupers/tripGroupers.h"
#include "aggregators/distanceAggregator.h"
#include "parser/parserFactory.h"
#include "trips/trip.h"


int main()
{
    auto data = ParserFactory::createParserFromFile("../data/testdata.json")->parse();

    auto groupedByTransportType = UniversalGrouper::groupTrips(data, TripGrouper::byTransportType());

    for (const auto& [transportType, trips] : groupedByTransportType)
    {
        std::cout << "Transport Type: " << transportType << ", Count: " << DistanceAggregator().aggregate(trips).aggregationValue << std::endl;
    }

    return 0;
}