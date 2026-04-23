#pragma once

#include <vector>
#include <memory>

#include "trips/trip.h"

template<typename T>
class IStatistic
{
    public:
        virtual ~IStatistic() = default;

        virtual T evaluate(const std::vector<std::shared_ptr<Trip>>& trips) const = 0;
};