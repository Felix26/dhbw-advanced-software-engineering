#include "trips/bustrip.h"

BusTrip::BusTrip(int id, const Station& origin, const Station& destination, int distance, int duration, const std::string& busNumber) : Trip(id, origin, destination, distance, duration), mBusNumber(busNumber)
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