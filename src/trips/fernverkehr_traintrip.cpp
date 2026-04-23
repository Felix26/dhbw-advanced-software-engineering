#include "trips/fernverkehr_traintrip.h"

std::string FernverkehrTrainTrip::getTransportName() const
{
    return "Fernverkehrszug (" + mLineName + ")";
}

std::string FernverkehrTrainTrip::getTransportType() const
{
    return "Fernverkehrszug";
}
