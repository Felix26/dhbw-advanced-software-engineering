#include <cassert>

#include "groupers/universalGrouper.h"
#include "groupers/tripGroupers.h"
#include "parser/parserFactory.h"

#include "aggregators/distanceAggregator.h"

#include "statistic.h"

int main()
{
    auto parser = ParserFactory::createMockParser();
    auto trips = parser->parse();

    auto tripGrouper = TripGrouper::byTransportType();
    auto visitedStationsGrouper = TripGrouper::byVisitedStations();
    auto byPassedStopsGrouper = TripGrouper::byPassedStops();

    auto groupedByTransportType = UniversalGrouper::groupTrips(trips, tripGrouper);
    auto groupedByVisitedStations = UniversalGrouper::groupTrips(trips, visitedStationsGrouper);
    auto groupedByPassedStops = UniversalGrouper::groupTrips(trips, byPassedStopsGrouper);

    auto statisticByTransportType = Statistic(groupedByTransportType, DistanceAggregator());
    auto statisticByVisitedStations = Statistic(groupedByVisitedStations, DistanceAggregator());
    auto statisticByPassedStops = Statistic(groupedByPassedStops, DistanceAggregator());

    statisticByTransportType.sortByValue();
    statisticByVisitedStations.sortByValue();

    auto transportData = statisticByTransportType.getData();
    auto visitedStationsData = statisticByVisitedStations.getData();
    auto passedStopsData = statisticByPassedStops.getData();

    assert(transportData.size() == 5); // 5 different transport types in the mock data
    assert(visitedStationsData.size() == 6); // 6 different visited stations
    assert(passedStopsData.size() == 8); // 8 different passed stops

    assert(transportData[0].second.aggregationValue.getDistanceInMeters() == 200000); // Total distance for Fernverkehr
    assert(transportData[1].second.aggregationValue.getDistanceInMeters() == 63000); // Total distance for Regionalverkehr
    assert(transportData[2].second.aggregationValue.getDistanceInMeters() == 12000); // Total distance for S-Bahn
    assert(transportData[3].second.aggregationValue.getDistanceInMeters() == 800); // Total distance for Tram
    assert(transportData[4].second.aggregationValue.getDistanceInMeters() == 800); // Total distance for Bus

    assert(visitedStationsData[0].second.aggregationValue.getDistanceInMeters() == 275000); // Total distance for Freiburg (Breisgau) Hbf
    assert(visitedStationsData[1].second.aggregationValue.getDistanceInMeters() == 200000); // Total distance for Mannheim Hbf
    assert(visitedStationsData[2].second.aggregationValue.getDistanceInMeters() == 63000); // Total distance for Offenburg
    assert(visitedStationsData[3].second.aggregationValue.getDistanceInMeters() == 12000); // Total distance for Denzlingen
    assert(visitedStationsData[4].second.aggregationValue.getDistanceInMeters() == 1600); // Total distance for Bertoldsbrunnen
    assert(visitedStationsData[5].second.aggregationValue.getDistanceInMeters() == 1600); // Total distance for Stadttheater
}