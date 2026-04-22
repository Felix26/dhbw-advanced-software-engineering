#include "regionalverkehr_traintrip.h"

std::string RegionalverkehrTrainTrip::getTransportType() const
{
    return "Regionalzug (" + mLineName + ")";
}