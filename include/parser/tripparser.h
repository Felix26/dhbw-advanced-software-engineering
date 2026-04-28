#pragma once

#include "iparser.h"
#include "json.hpp"

#include "stationRepository.h"

using json = nlohmann::json;

class TripParser : public IParser
{
    public:
        explicit TripParser(const std::string& filepath, const std::shared_ptr<StationRepository>& stationRepo);
        ~TripParser() override = default;

        Trips parse() override;

    private:
        std::string mFilepath;
        std::shared_ptr<StationRepository> mStationRepo;

        std::string extractDHIDFromIdentifiers(const json &identifiersNode) const;
        std::string extractDHID(const json &stationNode) const;
};