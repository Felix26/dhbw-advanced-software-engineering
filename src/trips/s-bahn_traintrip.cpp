#include "trips/s-bahn_traintrip.h"

std::string SBahnTrainTrip::getTransportType() const
{
    return "S-Bahn (" + mLineName + ")";
}