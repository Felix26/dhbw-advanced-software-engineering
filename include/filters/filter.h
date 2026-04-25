#pragma once

#include <functional>

#include "trips/trip.h"
#include "valueObjects/transportType.h"

class Filter
{
    public:
        static std::function<bool(const Trip&)> filterByTransportType(const TransportType transportType);
        static std::function<bool(const Trip&)> filterByYear(int year);

        static std::function<bool(const Trip&)> onlyTrainTrips();
        
};