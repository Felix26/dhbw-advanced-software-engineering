#pragma once

#include "iStationParser.h"

class ZHVStationParser : public IStationParser
{
    public:
        ZHVStationParser(const std::string &filePath) : mFilePath(filePath) {}

        std::unordered_map<std::string, ZHVData> parseStations() const override;

    private:
        std::string mFilePath;
};