#pragma once

#include <unordered_map>
#include <string>

#include "valueObjects/coordinates.h"

struct ZHVData
{
    std::string dhid;
    std::string name;
    std::string municipality;
    Coordinates coordinates = Coordinates(0.0, 0.0);
};

class IStationParser
{
    public:
        virtual ~IStationParser() = default;

        virtual std::unordered_map<std::string, ZHVData> parseStations() const = 0;
};