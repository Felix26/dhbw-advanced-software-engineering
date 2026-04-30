#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

namespace Printers
{
    template <typename T>
    struct BarChartWrapper
    {
        const T &value;
        bool useAverage = false;
        size_t width;

        BarChartWrapper(const T &value, bool useAverage = false, size_t width = 80) : value(value), useAverage(useAverage), width(width) {}
    };

    template <typename T>
    inline BarChartWrapper<T> barChart(const T &value, bool useAverage = false, size_t width = 80)
    {
        return BarChartWrapper<T>{value, useAverage, width};
    }

    template <typename T>
    struct MapWrapper
    {
        const T &value;
        bool useAverage = false;
        size_t width;
        size_t height;

        MapWrapper(const T &value, bool useAverage = false, size_t width = 200, size_t height = 75) : value(value), width(width), height(height), useAverage(useAverage) {}
    };

    template <typename T>
    inline MapWrapper<T> map(const T &value, bool useAverage = false, size_t width = 200, size_t height = 75)
    {
        return MapWrapper<T>{value, useAverage, width, height};
    }

    struct TripsWrapper
    {
        const Trips &trips;

        TripsWrapper(const Trips &trips) : trips(trips) {}
    };

    inline TripsWrapper trips(const Trips &trips)
    {
        return TripsWrapper(trips);
    }

    template <typename ValueType>
    constexpr bool existsAverage(const AggregatorResult<ValueType> &result)
    {
        auto average = result.getAverage();
        if(average) return true;
        return false;
    }

    template <typename ValueType>
    inline ValueType getAggregationValue(const AggregatorResult<ValueType> &result, bool useAverage)
    {
        auto average = result.getAverage();
        if(average && useAverage)
        {
            return *average;
        }
        return result.aggregationValue;
    }

    template <typename ValueType>
    inline double calculateRatio(const ValueType &value, const ValueType &maxValue)
    {
        if constexpr (std::is_arithmetic_v<ValueType>)
        {
            return static_cast<double>(value) / static_cast<double>(maxValue);
        }
        else
        {
            return value / maxValue;
        }
    }

    template <typename ValueType>
    inline std::string createBar(ValueType value, ValueType maxValue, size_t maxBarLength = 20)
    {
        const std::string fullBlock = "\xE2\x94\x81"; // Unicode character for a full block
        const std::string halfBlock = "\xE2\x95\xB8"; // Unicode character for a half block

        double ratio = calculateRatio(value, maxValue);
        ratio = std::clamp(ratio, 0.0, 1.0);

        double barLength = ratio * maxBarLength;
        size_t fullBlocks = static_cast<size_t>(std::floor(barLength));
        double partialBlock = barLength - fullBlocks;

        bool drawHalfBlock;
        if(partialBlock >= 0.75)
        {
            fullBlocks++;
        }
        else if(partialBlock >= 0.25)
        {
            drawHalfBlock = true;
        }

        std::string bar;

        for(size_t i = 0; i < fullBlocks; ++i)
        {
            bar += fullBlock;
        }

        if(drawHalfBlock)
        {
            bar += halfBlock;
        }
        
        return bar;
    }

    template <typename ValueType>
    std::string getValueString(ValueType value)
    {
        std::ostringstream valueStream;
        valueStream << value;
        return valueStream.str();
    }

    template <typename KeyType>
    std::string getKeyString(KeyType key, size_t maxLength = 0)
    {
        std::ostringstream keyStream;
        keyStream << key;
        std::string keyStr = keyStream.str();

        if (maxLength > 0 && keyStr.length() > maxLength)
        {
            keyStr = keyStr.substr(0, maxLength - 3) + "...";
        }
        return keyStr;
    }

    template <typename ValueType>
    concept HasValueName = requires
    {
        { ValueType::getValueTypeName() } -> std::convertible_to<std::string>;
    };

    template <typename KeyType>
    concept HasKeyName = requires
    {
        { KeyType::getKeyTypeName() } -> std::convertible_to<std::string>;
    };

    template <typename ValueType>
    std::string getSafeValueHeader()
    {
        if constexpr (HasValueName<ValueType>)
        {
            return ValueType::getValueTypeName();
        }
        else
        {
            return "Wert";
        }
    }

    template <typename KeyType>
    std::string getSafeKeyHeader()
    {
        if constexpr (HasKeyName<KeyType>)
        {
            return KeyType::getKeyTypeName();
        }
        else
        {
            return "Kategorie";
        }
    }
}