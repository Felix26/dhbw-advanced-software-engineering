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

    /*
    e.g. for the entry:
    de:08316:11220,Sasbach Winzergenossenschaft,"48,137965","7,613581",Sasbach am Kaiserstuhl
    Should become:
    Sasbach am Kaiserstuhl Winzergenossenschaft
    */
    size_t firstSpacePos = data.name.find(' ');
    if (firstSpacePos != std::string::npos)
    {
        // Isolate the first word of the station name, which is often the same as the municipality name (e.g., "Sasbach" in "Sasbach Winzergenossenschaft").
        std::string firstWord = data.name.substr(0, firstSpacePos);
        
        // does the municipality start with eg "Sasbach "? 
        // (using "Sasbach "(!) with space, to differentiate between eg "Sasbach" and "Sasbachwalden")
        if (data.municipality.starts_with(firstWord + " "))
        {
            // combine: "Sasbach am Kaiserstuhl" + " Winzergenossenschaft"
            return data.municipality + data.name.substr(firstSpacePos);
        }
    }

    return std::format("{} {}", data.municipality, data.name);
}