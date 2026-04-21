#include "trip.h"

Trip::Trip(int id, const Station& origin, const Station& destination, int distance) : mId(id), mOrigin(origin), mDestination(destination), distance(distance)
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
    return distance;
}
