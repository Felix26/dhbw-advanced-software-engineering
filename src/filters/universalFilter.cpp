#include "filters/universalFilter.h"

void UniversalFilter::filterTrips(Trips &trips, const std::function<bool(const Trip&)> &filterFunc)
{
    std::erase_if(trips, [&filterFunc](const std::shared_ptr<Trip>& trip)
        {
            return !filterFunc(*trip);
        });
}