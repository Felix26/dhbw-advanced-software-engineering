#pragma once

#include <functional>

#include "trips/trip.h"
#include "valueObjects/transportType.h"

class TripGrouper
{
    public:
        static std::function<TransportType(const Trip&)> byTransportType();
        static std::function<Station(const Trip&)> byOrigin();
        static std::function<Station(const Trip&)> byDestination();
        static std::function<std::string(const Trip&)> byMonth();
        
        static std::function<std::vector<Station>(const Trip&)> byVisitedStations();
        static std::function<std::vector<Station>(const Trip&)> byPassedStops();

        static std::function<std::string(const Trip&)> byNone();
};