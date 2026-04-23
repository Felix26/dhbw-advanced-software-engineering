#include "trips/trip.h"

Trip::Trip(int id, const Station& origin, const Station& destination, int distance, int duration, const std::chrono::system_clock::time_point startTime) : mId(id), mOrigin(origin), mDestination(destination), mDistance(distance), mDuration(duration), mStartTime(startTime)
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

int Trip::getDistance() const
{
    return mDistance;
}

int Trip::getDuration() const
{
    return mDuration;
}

std::chrono::system_clock::time_point Trip::getStartTime() const
{
    return mStartTime;
}
