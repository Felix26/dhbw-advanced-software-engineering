#include "stationRepository.h"

#include <format>

StationRepository::StationRepository(std::unique_ptr<IStationParser> stationParser)
{
    mZHVData = stationParser->parseStations();
}

std::shared_ptr<Station> StationRepository::getStation(const std::string &dhid) const
{
    auto it = mZHVData.find(dhid);
    if(it != mZHVData.end())
    {
        const ZHVData &data = it->second;
        std::string stationName = formatStationName(data);
        return std::make_shared<Station>(stationName, data.coordinates);
    }
   
    throw std::runtime_error("Station with dhid " + dhid + " not found");
}

std::string StationRepository::formatStationName(const ZHVData &data) const
{
    if(data.municipality.empty())
    {
        return data.name;
    }

    if(data.name.find(data.municipality) != std::string::npos)
    {
        return data.name;
    }

    return std::format("{} {}", data.municipality, data.name);
}