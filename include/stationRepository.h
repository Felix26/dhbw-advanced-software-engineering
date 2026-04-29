#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <optional>

#include "iStationParser.h"
#include "valueObjects/station.h"

class StationRepository
{
    public:
        StationRepository(const IStationParser &stationParser);

        std::shared_ptr<Station> getStation(const std::string &dhid) const;
        std::optional<std::shared_ptr<Station>> findStation(const std::string &dhid) const;

    private:
        std::unordered_map<std::string, ZHVData> mZHVData;

        friend class TripParser;
};