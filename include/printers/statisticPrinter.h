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
        // PREPARING:
    
        const auto &stats = wrapper.value;
        const size_t maxAllowedLineLength = 120;
        const size_t maxAllowedKeyLength = 50;

        if (stats.getData().empty())
        {
            os << "No data to display." << std::endl;
            return os;
        }

        std::string keyHeader = getSafeKeyHeader<KeyType>();
        std::string valueHeader = getSafeValueHeader<ValueType>();

        size_t maxKeyLength = keyHeader.length();
        ValueType maxValue = stats.getData().front().second.aggregationValue;

        for (const auto& [key, value] : stats.getData())
        {
            std::string keyString = getKeyString(key);

            maxKeyLength = std::min(std::max(maxKeyLength, keyString.length()), maxAllowedKeyLength);

            maxValue = std::max(maxValue, value.aggregationValue);
        }

        size_t maxValueLength = std::max(getValueString(maxValue).length(), valueHeader.length());
        const size_t availableBarLength = maxAllowedLineLength - maxKeyLength - maxValueLength - 5; // 5 for spacing and separator

        // PRINTING:

        // Header:
        os << "\n" << std::format("{:<{}} | {:>{}} | {}", keyHeader, maxKeyLength, valueHeader, maxValueLength, "Diagramm") << std::endl;

        // Trennlinie:
        os << std::string(maxKeyLength, '-') << "-+-" << std::string(maxValueLength, '-') << "-+-" << std::string(availableBarLength, '-') << std::endl;

        // Diagramm:
        size_t lineCount = 0;
        const size_t maxLineCount = 50;


        for (const auto& [key, value] : stats.getData())
        {
            if(lineCount >= maxLineCount)
            {
                size_t remaining = stats.getData().size() - lineCount;

                os << std::format("... [{} weitere Datensätze ausgeblendet] ...", remaining);
                break;
            }

            std::string keyString = getKeyString(key, maxKeyLength);
            std::string valueString = getValueString(value.aggregationValue);

            std::string bar = createBar(value.aggregationValue, maxValue, availableBarLength);

            os << std::format("{:<{}} | {:>{}} | {}", keyString, maxKeyLength, valueString, maxValueLength, bar) << std::endl;
            lineCount++;
        }

        return os;
    }
}