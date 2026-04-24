#pragma once

#include "trips/trip.h"
#include "iparser.h"

class FolderTripParser : public IParser
{
    public:
        explicit FolderTripParser(const std::string& folderPath) : mFolderPath(folderPath) {}

        Trips parse() override;

    private:
        std::string mFolderPath;
};