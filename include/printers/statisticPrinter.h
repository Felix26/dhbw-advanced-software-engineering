#pragma once

#include <iostream>
#include <format>

#include "printers/core.h"
#include "statistic.h"

namespace Printers
{
    template <typename KeyType, typename ValueType>
    inline std::ostream& operator<<(std::ostream& os, const PrettyWrapper<Statistic<KeyType, ValueType>> &wrapper)
    {
        const auto &stats = wrapper.value;
        const size_t maxLineLength = 120;

        if (stats.getData().empty())
        {
            os << "No data to display." << std::endl;
            return os;
        }

        size_t maxKeyLength = 0;
        ValueType maxValue = stats.getData().front().second.aggregationValue;

        for (const auto& [key, value] : stats.getData())
        {
            std::string keyString = getKeyString(key);

            maxKeyLength = std::min(std::max(maxKeyLength, keyString.length()), size_t(20));

            maxValue = std::max(maxValue, value.aggregationValue);
        }

        size_t maxValueLength = getValueString(maxValue).length();
        const size_t availableBarLength = maxLineLength - maxKeyLength - maxValueLength - 5; // 5 for spacing and separator

        for (const auto& [key, value] : stats.getData())
        {
            std::string keyString = getKeyString(key, maxKeyLength);
            std::string valueString = getValueString(value.aggregationValue);

            std::string bar = createBar(value.aggregationValue, maxValue, availableBarLength);

            os << std::format("{:<{}} | {:>{}} | {}", keyString, maxKeyLength, valueString, maxValueLength, bar) << std::endl;
        }

        return os;
    }
}