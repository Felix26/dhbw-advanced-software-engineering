#pragma once

#include "iparser.h"

class TripParser : public IParser
{
    public:
        explicit TripParser(const std::string& filepath);
        ~TripParser() override = default;

        std::vector<std::shared_ptr<Trip>> parse() override;

    private:
        std::string mFilepath;
};