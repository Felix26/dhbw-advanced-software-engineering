#include "bustrip.h"

BusTrip::BusTrip(int id, const Station& origin, const Station& destination, int distance,  const std::string& busNumber) : Trip(id, origin, destination, distance), mBusNumber(busNumber)
{

}

std::string BusTrip::getBusNumber() const
{
    return mBusNumber;
}


std::string BusTrip::getTransportType() const
{
    // z.B. "Bus (Linie 42)"
    return "Bus (" + mBusNumber + ")";
}