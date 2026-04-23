#include "statistics/transportTypeStatistic.h"

std::map<std::string, int> TransportTypeStatistic::evaluate(const std::vector<std::shared_ptr<Trip>>& trips) const
{
    std::map<std::string, int> transportTypeCounts;

    for (const auto& trip : trips)
    {
        std::string transportType = trip->getTransportType();
        transportTypeCounts[transportType]++;
    }

    return transportTypeCounts;
}