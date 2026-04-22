#include "fernverkehr_traintrip.h"

std::string FernverkehrTrainTrip::getTransportType() const
{
    return "Fernverkehrszug (" + mLineName + ")";
}
