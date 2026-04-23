#include "trips/u-bahn_traintrip.h"

std::string UBahnTrainTrip::getTransportName() const
{
    return "U-Bahn (" + mLineName + ")";
}

std::string UBahnTrainTrip::getTransportType() const
{
    return "U-Bahn";
}