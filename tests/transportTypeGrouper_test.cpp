#include <iostream>
#include <map>

#include "groupers/universalGrouper.h"
#include "groupers/tripGroupers.h"
#include "aggregators/distanceAggregator.h"
#include "aggregators/speedAggregator.h"
#include "parser/parserFactory.h"
#include "trips/trip.h"
#include "statistic.h"


int main()
{
    auto data = ParserFactory::createParserFromFolder("C:\\Users\\Felix\\Nextcloud\\Advanced SWE")->parse();

    auto groupedByTransportType = UniversalGrouper::groupTrips(data, TripGrouper::byTransportType());
    
    auto statisticByTransportType = Statistic(groupedByTransportType, SpeedAggregator());
    
    std::cout << "Statistic by Transport Type:" << std::endl;
    statisticByTransportType.sortByValue(false);
    std::cout << statisticByTransportType << std::endl;
    
    auto groupedByVisitedStations = UniversalGrouper::groupTrips(data, TripGrouper::byVisitedStations());
    /*for (const auto& [transportType, trips] : groupedByTransportType)
    {
        std::cout << "Transport Type: " << transportType << ", Count: " << DistanceAggregator().aggregate(trips).aggregationValue << std::endl;
    }

    for (const auto& [station, trips] : groupedByVisitedStations)
    {
        auto aggregationResult = CountAggregator().aggregate(trips);
        if(aggregationResult.aggregationValue < 50) continue;
        std::cout << "Station: " << station << ", Count: " << aggregationResult.aggregationValue << std::endl;
    }*/

    return 0;
}