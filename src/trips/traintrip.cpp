#include "trips/traintrip.h"

TrainTrip::TrainTrip(int id, const Station& origin, const Station& destination, int distance, int duration, const std::chrono::system_clock::time_point startTime, const TransportType& transportType, const std::string& lineName, const Operator& op) : Trip(id, origin, destination, distance, duration, startTime, transportType), mLineName(lineName), mOperator(op)
{

}

std::string TrainTrip::getLineName() const
{
    return mLineName;
}

Operator TrainTrip::getOperator() const
{
    return mOperator;
}


void TrainTrip::addStopover(const Station& station)
{
    mStopovers.push_back(station);
}

const std::vector<Station>& TrainTrip::getStopovers() const
{
    return mStopovers;
}

int TrainTrip::getStopoverCount() const
{
    return mStopovers.size();
}
std::string TrainTrip::getTransportName() const
{
    return getTransportType().toString() + " (" + mLineName + ")";
}