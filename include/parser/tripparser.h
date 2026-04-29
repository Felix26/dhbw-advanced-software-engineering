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

        std::optional<std::string> extractDHIDFromIdentifiers(const json &identifiersNode) const;
        std::optional<std::string> extractDHIDFromName(const std::string &name) const;
        std::optional<std::string> extractDHID(const json &stationNode, const std::string &name) const;
};