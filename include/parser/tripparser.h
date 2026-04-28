#pragma once

#include "iparser.h"

#include "stationRepository.h"

class TripParser : public IParser
{
    public:
        explicit TripParser(const std::string& filepath, const std::shared_ptr<StationRepository>& stationRepo);
        ~TripParser() override = default;

        Trips parse() override;

    private:
        std::string mFilepath;
        std::shared_ptr<StationRepository> mStationRepo;
};