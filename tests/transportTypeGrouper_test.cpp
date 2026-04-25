#include <iostream>
#include <map>

#include "groupers/universalGrouper.h"
#include "groupers/tripGroupers.h"
#include "aggregators/distanceAggregator.h"
#include "aggregators/countAggregator.h"
#include "parser/parserFactory.h"
#include "trips/trip.h"
#include "statistic.h"
#include "filters/universalFilter.h"
#include "filters/filter.h"


int main()
{
    auto data = ParserFactory::createParserFromFolder("C:\\Users\\Felix\\Nextcloud\\Advanced SWE")->parse();

    UniversalFilter::filterTrips(data, Filter::onlyTrainTrips());

    auto groupedByTransportType = UniversalGrouper::groupTrips(data, TripGrouper::byTransportType());
    auto groupedByVisitedStations = UniversalGrouper::groupTrips(data, TripGrouper::byVisitedStations());
    auto groupedByMonth = UniversalGrouper::groupTrips(data, TripGrouper::byMonth());
    
    //auto statisticByTransportType = Statistic(groupedByMonth, DistanceAggregator());
    auto statisticByTransportType = Statistic(data, DistanceAggregator());
    
    std::cout << "Statistic by Transport Type:" << std::endl;
    statisticByTransportType.sortByKey();
    std::cout << statisticByTransportType << std::endl;
    
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