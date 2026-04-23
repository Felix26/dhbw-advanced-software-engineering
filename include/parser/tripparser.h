#pragma once

#include "iparser.h"

class TripParser : public IParser
{
    public:
        explicit TripParser(const std::string& filepath);
        ~TripParser() override = default;

        Trips parse() override;

    private:
        std::string mFilepath;
};