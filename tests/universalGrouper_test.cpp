#include <cassert>

#include "groupers/universalGrouper.h"
#include "groupers/tripGroupers.h"
#include "parser/parserFactory.h"


int main()
{
    auto parser = ParserFactory::createMockParser();
    auto trips = parser->parse();

    auto tripGrouper = TripGrouper::byNone();

    auto groupedTrips = UniversalGrouper::groupTrips(trips, tripGrouper);

    assert(groupedTrips.size() == 1); // All trips grouped together

    auto &allTrips = groupedTrips.begin()->second;
    assert(allTrips.size() == 5); // All 5 trips in the mock data

    std::sort(allTrips.begin(), allTrips.end(), [](const std::shared_ptr<Trip>& a, const std::shared_ptr<Trip>& b) {
        return a->getId() < b->getId();
    });

    std::sort(trips.begin(), trips.end(), [](const std::shared_ptr<Trip>& a, const std::shared_ptr<Trip>& b) {
        return a->getId() < b->getId();
    });

    for(uint8_t i = 0; i < allTrips.size(); i++)
    {
        assert(allTrips[i] == trips[i]); // Check that all expected trips are present
    }

    return 0;
}