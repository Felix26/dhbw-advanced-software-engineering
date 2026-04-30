#include <cassert>

#include "groupers/universalGrouper.h"
#include "groupers/tripGroupers.h"
#include "parser/parserFactory.h"
#include "filters/universalFilter.h"
#include "filters/filter.h"

int main()
{
    auto parser = ParserFactory::createMockParser();
    auto trips = parser->parse();

    auto tripGrouper = TripGrouper::byTransportType();

    auto groupedTrips = UniversalGrouper::groupTrips(trips, tripGrouper);

    auto fernverkehrTrips = groupedTrips[TransportType::Fernverkehr];
    auto regionalverkehrTrips = groupedTrips[TransportType::Regionalverkehr];
    auto sBahnTrips = groupedTrips[TransportType::SBahn];
    auto tramTrips = groupedTrips[TransportType::Tram];
    auto busTrips = groupedTrips[TransportType::Bus];

    auto filteredFernverkehrTrips = fernverkehrTrips;
    auto filteredRegionalverkehrTrips = regionalverkehrTrips;
    auto filteredSBahnTrips = sBahnTrips;
    auto filteredTramTrips = tramTrips;
    auto filteredBusTrips = busTrips;

    UniversalFilter::filterTrips(filteredFernverkehrTrips, Filter::filterByTransportType(TransportType::Fernverkehr));
    UniversalFilter::filterTrips(filteredRegionalverkehrTrips, Filter::filterByTransportType(TransportType::Regionalverkehr));
    UniversalFilter::filterTrips(filteredSBahnTrips, Filter::filterByTransportType(TransportType::SBahn));
    UniversalFilter::filterTrips(filteredTramTrips, Filter::filterByTransportType(TransportType::Tram));
    UniversalFilter::filterTrips(filteredBusTrips, Filter::filterByTransportType(TransportType::Bus));

    assert(filteredFernverkehrTrips[0] == fernverkehrTrips[0]); // Check that the ICE trip is in the Fernverkehr group
    assert(filteredRegionalverkehrTrips[0] == regionalverkehrTrips[0]); // Check that the Regionalverkehr trip is in the Regionalverkehr group
    assert(filteredSBahnTrips[0] == sBahnTrips[0]); // Check that the S-Bahn trip is in the S-Bahn group
    assert(filteredTramTrips[0] == tramTrips[0]); // Check that the Tram trip is in the Tram group
    assert(filteredBusTrips[0] == busTrips[0]); // Check that the Bus trip is in the Bus group

    auto trainTrips = trips;
    UniversalFilter::filterTrips(trainTrips, Filter::onlyTrainTrips());
    assert(trainTrips.size() == 4); // Check that only the 4 train trips remain after filtering

    return 0;
}