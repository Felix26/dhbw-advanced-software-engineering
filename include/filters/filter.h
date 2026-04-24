#pragma once

#include <functional>

#include "trips/trip.h"
#include "valueObjects/transportType.h"

class Filter
{
    public:
        static std::function<bool(const Trip&)> filterByTransportType(Trips &trips, const TransportType transportType);
        static std::function<bool(const Trip&)> filterByYear(Trips &trips, int year);

        static std::function<bool(const Trip&)> onlyTrainTrips(Trips &trips);
        
};