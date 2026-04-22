#pragma once

#include <vector>
#include <memory>

#include "trips/trip.h"

class IParser
{
    public:
        virtual ~IParser() = default;

        virtual std::vector<std::shared_ptr<Trip>> parse() = 0;
};