#pragma once

#include "trips/trip.h"
#include "iparser.h"
#include "stationRepository.h"

class FolderTripParser : public IParser
{
    public:
        explicit FolderTripParser(const std::string& folderPath, const std::shared_ptr<StationRepository>& stationRepo) : mFolderPath(folderPath), mStationRepo(stationRepo) {}

        Trips parse() override;

    private:
        std::string mFolderPath;
        std::shared_ptr<StationRepository> mStationRepo;
};