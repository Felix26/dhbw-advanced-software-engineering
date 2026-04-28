#include "zhvStationParser.h"

#include <fstream>
#include <sstream>

/*
zHV data looks like:
DHID,Name,Latitude,Longitude,Municipality
de:08111:100,Stammheim,"48,850055","9,156231",Stuttgart
de:08111:102,Korntaler Straße,"48,846732","9,157121",Stuttgart
de:08111:103,Heutingsheimer Straße,"48,842452","9,159312",Stuttgart
de:08111:104,Wimpfener Straße,"48,838249","9,161037",Stuttgart
*/
std::unordered_map<std::string, ZHVData> ZHVStationParser::parseStations() const
{
    std::unordered_map<std::string, ZHVData> stationDataMap;

    std::ifstream file(mFilePath);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + mFilePath);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string dhid, name, municipality;
        double latitude, longitude;

        if (std::getline(ss, dhid, ';') && std::getline(ss, name, ';') && std::getline(ss, municipality, ';') && ss >> latitude && ss.get() && ss >> longitude)
        {
            ZHVData data{dhid, name, municipality, Coordinates(latitude, longitude)};
            stationDataMap[dhid] = data;
        }
    }

    return stationDataMap;
}