#pragma once

#include "iparser.h"

class FakeTripParser : public IParser
{
    public:
        FakeTripParser() = default;
        ~FakeTripParser() override = default;

        Trips parse() override;
};