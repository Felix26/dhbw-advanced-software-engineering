#include <cassert>

#include "groupers/universalGrouper.h"
#include "groupers/tripGroupers.h"
#include "parser/parserFactory.h"


int main()
{
    auto parser = ParserFactory::createMockParser();
    auto trips = parser->parse();

    auto tripGrouper = TripGrouper::byTransportType();

    auto groupedTrips = UniversalGrouper::groupTrips(trips, tripGrouper);

    assert(groupedTrips.size() == 5); // 5 different transport types in the mock data
    assert(groupedTrips[TransportType::Fernverkehr].size() == 1); // 1 ICE trip
    assert(groupedTrips[TransportType::Regionalverkehr].size() == 1); // 1 RE7 trip
    assert(groupedTrips[TransportType::SBahn].size() == 1); // 1 S4 trip
    assert(groupedTrips[TransportType::Tram].size() == 1); // 1 Tram trip
    assert(groupedTrips[TransportType::Bus].size() == 1); // 1 Bus trip

    return 0;
}