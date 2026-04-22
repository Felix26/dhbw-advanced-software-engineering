#include "tram_traintrip.h"

std::string TramTrainTrip::getTransportType() const
{
    return "Tram (" + mLineName + ")";
}