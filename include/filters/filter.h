#pragma once

#include <functional>

#include "trips/trip.h"
#include "valueObjects/transportType.h"

using TripFilterFunction = std::function<bool(const Trip&)>;

class Filter
{
    public:
        static TripFilterFunction filterByTransportType(const TransportType transportType);
        static TripFilterFunction filterByYear(int year);

        static TripFilterFunction onlyTrainTrips();
        
};