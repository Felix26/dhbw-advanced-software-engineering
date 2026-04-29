#pragma once

#include <optional>
#include <memory>

#include "iparser.h"
#include "json.hpp"

#include "stationRepository.h"
#include "valueObjects/allValueObjectHeaders.h"

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

        Station parseStationNode(const json &stationNode) const;
        std::chrono::system_clock::time_point parseTime(const std::string &timeStr) const;
        std::optional<std::shared_ptr<Trip>> createTrip(int statusId, const Station &origin, const Station &dest, int distance, int duration, const std::chrono::system_clock::time_point &startTime, const std::string &category, const std::string &lineName, const Operator &op) const;
};