#include "trips/tram_traintrip.h"

std::string TramTrainTrip::getTransportName() const
{
    return "Tram (" + mLineName + ")";
}

std::string TramTrainTrip::getTransportType() const
{
    return "Tram";
}