#include "trips/regionalverkehr_traintrip.h"

std::string RegionalverkehrTrainTrip::getTransportName() const
{
    return "Regionalzug (" + mLineName + ")";
}

std::string RegionalverkehrTrainTrip::getTransportType() const
{
    return "Regionalzug";
}