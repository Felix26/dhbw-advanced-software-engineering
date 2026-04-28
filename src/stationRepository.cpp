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
        std::string stationName = std::format("{} {}", data.municipality, data.name);
        return std::make_shared<Station>(stationName, data.coordinates);
    }
   
    throw std::runtime_error("Station with dhid " + dhid + " not found");
}
