#include "iStationParser.h"

#include <format>

ZHVData::ZHVData(const std::string &dhid, const std::string &name, const std::string &municipality, const Coordinates &coordinates) : dhid(dhid), name(name), municipality(municipality), coordinates(coordinates)
{
    formattedName = IStationParser::formatStationName(name, municipality);
    nameTokens = StringUtils::tokenize(formattedName);
}

std::string IStationParser::formatStationName(const std::string &name, const std::string &municipality)
{
    if(municipality.empty())
    {
        return name;
    }

    if(name.find(municipality) != std::string::npos)
    {
        return name;
    }

    /*
    e.g. for the entry:
    de:08316:11220,Sasbach Winzergenossenschaft,"48,137965","7,613581",Sasbach am Kaiserstuhl
    Should become:
    Sasbach am Kaiserstuhl Winzergenossenschaft
    */
    size_t firstSpacePos = name.find(' ');
    if (firstSpacePos != std::string::npos)
    {
        // Isolate the first word of the station name, which is often the same as the municipality name (e.g., "Sasbach" in "Sasbach Winzergenossenschaft").
        std::string firstWord = name.substr(0, firstSpacePos);
        
        // does the municipality start with eg "Sasbach "? 
        // (using "Sasbach "(!) with space, to differentiate between eg "Sasbach" and "Sasbachwalden")
        if (municipality.starts_with(firstWord + " "))
        {
            // combine: "Sasbach am Kaiserstuhl" + " Winzergenossenschaft"
            return municipality + name.substr(firstSpacePos);
        }
    }

    return std::format("{} {}", municipality, name);
}