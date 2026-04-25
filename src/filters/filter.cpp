#include "filters/filter.h"

#include <chrono>
#include "filter.h"
#include "trips/trip.h"
#include "valueObjects/transportType.h"

std::function<bool(const Trip&)> Filter::filterByTransportType(const TransportType transportType)
{
    return [transportType](const Trip& trip)
    {
        return trip.getTransportType() == transportType;
    };
}

std::function<bool(const Trip&)> Filter::filterByYear(int year)
{
    return [year](const Trip& trip)
    {
        auto startTime = trip.getStartTime();
        auto tripYear = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(startTime)).year();
        return year == static_cast<int>(tripYear);
    };
}

std::function<bool(const Trip &)> Filter::onlyTrainTrips()
{
    return [](const Trip& trip)
    {
        return trip.getTransportType().isTrain();
    };
}