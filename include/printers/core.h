#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

namespace Printers
{
    template <typename T>
    struct PrettyWrapper
    {
        const T &value;
    };

    template <typename T>
    inline PrettyWrapper<T> pretty(const T &value)
    {
        return PrettyWrapper<T>{value};
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
        const std::string fullBlock = "\xE2\x96\x88"; // Unicode character for a full block
        const std::string halfBlock = "\xE2\x96\x8C"; // Unicode character for a half block

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
}