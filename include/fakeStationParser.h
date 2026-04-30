#pragma once

#include "iStationParser.h"

class FakeStationParser : public IStationParser
{
    public:
        FakeStationParser() = default;

        std::unordered_map<std::string, ZHVData> parseStations() const override;
};