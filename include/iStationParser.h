#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "valueObjects/coordinates.h"
#include "stringUtils.h"

struct ZHVData
{
    std::string dhid;
    std::string name;
    std::string municipality;
    Coordinates coordinates = Coordinates(0.0, 0.0);

    std::string formattedName;
    std::vector<std::string> nameTokens;

    ZHVData() = default;
    ZHVData(const std::string &dhid, const std::string &name, const std::string &municipality, const Coordinates &coordinates);
};

class IStationParser
{
    public:
        virtual ~IStationParser() = default;

        virtual std::unordered_map<std::string, ZHVData> parseStations() const = 0;

    protected:
        friend class ZHVData;
        static std::string formatStationName(const std::string &name, const std::string &municipality);
};