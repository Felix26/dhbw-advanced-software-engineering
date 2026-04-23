#pragma once

#include <functional>

#include "trips/trip.h"

class TripGrouper
{
    public:
        static std::function<std::string(const Trip&)> byTransportType();
};