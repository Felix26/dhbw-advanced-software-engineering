#include "zhvStationParser.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "stringUtils.h"

std::vector<std::string> parseCSVLine(const std::string& line)
{
    std::vector<std::string> tokens;
    std::string currentToken;
    bool insideQuotes = false;

    for(char c : line)
    {
        if (c == '"')
        {
            insideQuotes = !insideQuotes; // Status umschalten
        }
        else if (c == ',' && !insideQuotes)
        {
            tokens.push_back(currentToken);
            currentToken.clear();
        }
        else
        {
            currentToken += c;
        }
    }
    tokens.push_back(currentToken); // Letztes Token hinzufügen
    return tokens;
}

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
        
        if(line.empty()) continue;

        auto tokens = parseCSVLine(line);

        // expect 5 tokens (DHID, Name, Lat, Lon, Municipality)
        if(tokens.size() >= 5)
        {
            std::string dhid = tokens[0];
            std::string name = tokens[1];
            std::string latStr = tokens[2];
            std::string lonStr = tokens[3];
            std::string municipality = tokens[4];

            // replace comma with dot for conversion to double
            std::replace(latStr.begin(), latStr.end(), ',', '.');

            try 
            {
                double latitude = std::stod(latStr);
                double longitude = std::stod(lonStr);

                ZHVData data(dhid, name, municipality, Coordinates(latitude, longitude));
                stationDataMap[dhid] = data;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Skipping invalid coords for " << dhid << "\n";
                continue;
            }
        }
    }

    return stationDataMap;
}