#include "groupers/tripGroupers.h"

#include "trips/trainTrip.h"

std::function<std::string(const Trip &)> TripGrouper::byTransportType()
{
    return [](const Trip& trip)
    {
        return trip.getTransportType();
    };
}

std::function<Station(const Trip &)> TripGrouper::byOrigin()
{
    return [](const Trip& trip)
    {
        return trip.getOrigin();
    };
}

std::function<Station(const Trip &)> TripGrouper::byDestination()
{
    return [](const Trip& trip)
    {
        return trip.getDestination();
    };
}


std::function<std::vector<Station>(const Trip &)> TripGrouper::byVisitedStations()
{
    return [](const Trip& trip)
    {
        return std::vector<Station>{TripGrouper::byDestination()(trip), TripGrouper::byOrigin()(trip)};
    };
}

std::function<std::vector<Station>(const Trip &)> TripGrouper::byPassedStops()
{
    return [](const Trip& trip)
    {
        std::vector<Station> stops;

        auto trainTrip = dynamic_cast<const TrainTrip*>(&trip);

        if (trainTrip != nullptr)
        {
            for (const auto& stop : trainTrip->getStopovers())
            {
                stops.push_back(stop);
            }
            
            stops.push_back(trip.getOrigin());
            stops.push_back(trip.getDestination());
        }
        else 
        {
            // For non-train trips, we only consider the origin and destination as "passed stops"
            stops.push_back(trip.getOrigin());
            stops.push_back(trip.getDestination());
        }

        return stops;
    };
}