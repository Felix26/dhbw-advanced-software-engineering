#include "stationRepository.h"

#include <format>
#include <sstream>

StationRepository::StationRepository(const IStationParser &stationParser)
{
    mZHVData = stationParser.parseStations();
}

std::shared_ptr<Station> StationRepository::getStation(const std::string &dhid) const
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
        std::string stationName = formatStationName(data);
        return std::make_shared<Station>(stationName, data.coordinates);
    }
   
    throw std::runtime_error("Station with dhid " + usedDhid + " not found");
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