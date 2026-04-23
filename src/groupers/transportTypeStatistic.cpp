#include "groupers/transportTypeGrouper.h"

TripBuckets TransportTypeGrouper::groupTrips(const Trips& trips) const
{
    TripBuckets tripBuckets;

    for (const auto& trip : trips)
    {
        std::string transportType = trip->getTransportType();
        tripBuckets[transportType].emplace_back(trip);
    }

    return tripBuckets;
}