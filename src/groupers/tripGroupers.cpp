#include "groupers/tripGroupers.h"

std::function<std::string(const Trip &)> TripGrouper::byTransportType()
{
    return [](const Trip& trip)
    {
        return trip.getTransportType();
    };
}