#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "trips/trip.h"

template<typename T>
struct AggregatorResult
{
    T aggregationValue;
    std::optional<size_t> aggregationCount;

    static constexpr bool supportsAverage = requires(T t, int i) { t / i; };

    std::optional<T> getAverage() const
    {
        if constexpr (supportsAverage)
        {
            if(aggregationCount && *aggregationCount > 0)
            {
                return aggregationValue / *aggregationCount;
            }
        }
        return std::nullopt;
    }
};

template<typename T>
class IAggregator
{
    public:
        virtual ~IAggregator() = default;

        virtual AggregatorResult<T> aggregate(const Trips& trips) const = 0;
};