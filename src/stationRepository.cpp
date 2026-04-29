#include "stationRepository.h"

#include <format>
#include <sstream>
#include <vector>

StationRepository::StationRepository(const IStationParser &stationParser)
{
    mZHVData = stationParser.parseStations();
}

std::shared_ptr<Station> StationRepository::getStation(const std::string &dhid) const
{
    auto result = findStation(dhid);
    if(result)
    {
        return *result;
    }
   
    throw std::runtime_error("Station with dhid " + dhid + " not found");
}

std::optional<std::shared_ptr<Station>> StationRepository::findStation(const std::string &dhid) const
{
    // if second part of dhid (de:8212:13) is only 4 chars long, try to find station with leading zero (de:08212:13)
    std::string usedDhid = dhid;
    std::stringstream ss(dhid);
    std::string part1, part2, part3;

    if(std::getline(ss, part1, ':') && std::getline(ss, part2, ':') && std::getline(ss, part3))
    {
        if(part2.length() == 4)
        {
            usedDhid = std::format("{}:{:05}:{}", part1, std::stoi(part2), part3);
        }
    }

    auto it = mZHVData.find(usedDhid);
    if(it != mZHVData.end())
    {
        const ZHVData &data = it->second;
        return std::make_shared<Station>(data.formattedName, data.coordinates);
    }

    return std::nullopt;
}
