#pragma once

#include <unordered_map>
#include <memory>

#include "iStationParser.h"
#include "valueObjects/station.h"

class StationRepository
{
    public:
        StationRepository(const IStationParser &stationParser);

        std::shared_ptr<Station> getStation(const std::string &idOrName) const;

    private:
        std::unordered_map<std::string, ZHVData> mZHVData;

        std::string formatStationName(const ZHVData &data) const;
};