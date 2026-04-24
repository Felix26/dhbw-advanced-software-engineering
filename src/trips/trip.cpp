#include "trips/trip.h"

Trip::Trip(int id, const Station& origin, const Station& destination, int distance, int duration, const std::chrono::system_clock::time_point startTime, const TransportType& transportType) : mId(id), mOrigin(origin), mDestination(destination), mDistance(Distance::fromMeters(distance)), mDuration(Duration::fromMinutes(duration)), mStartTime(startTime), mTransportType(transportType)
{

}

int Trip::getId() const
{
    return mId;
}

Station Trip::getOrigin() const
{
    return mOrigin;
}

Station Trip::getDestination() const
{
    return mDestination;
}

Distance Trip::getDistance() const
{
    return mDistance;
}

Duration Trip::getDuration() const
{
    return mDuration;
}

std::chrono::system_clock::time_point Trip::getStartTime() const
{
    return mStartTime;
}

TransportType Trip::getTransportType() const
{
    return mTransportType;
}
