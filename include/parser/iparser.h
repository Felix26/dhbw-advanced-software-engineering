#pragma once

#include <vector>
#include <memory>

#include "trips/trip.h"

class IParser
{
    public:
        virtual ~IParser() = default;

        virtual Trips parse() = 0;
};