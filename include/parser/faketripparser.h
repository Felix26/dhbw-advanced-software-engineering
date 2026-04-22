#pragma once

#include "iparser.h"

class FakeTripParser : public IParser
{
    public:
        FakeTripParser() = default;
        ~FakeTripParser() override = default;

        std::vector<std::shared_ptr<Trip>> parse() override;
};