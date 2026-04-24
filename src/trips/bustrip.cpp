#include "trips/bustrip.h"

BusTrip::BusTrip(int id, const Station& origin, const Station& destination, int distance, int duration, const std::chrono::system_clock::time_point startTime, const std::string& busNumber) : Trip(id, origin, destination, distance, duration, startTime, TransportType::Bus), mBusNumber(busNumber)
{

}

std::string BusTrip::getBusNumber() const
{
    return mBusNumber;
}


std::string BusTrip::getTransportName() const
{
    // z.B. "Bus (Linie 42)"
    return getTransportType().toString() + " (" + mBusNumber + ")";
}