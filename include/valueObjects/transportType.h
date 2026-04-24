#pragma once

#include <string>

class Trip;

class TransportType
{
    public:
        enum Value { Fernverkehr, Regionalverkehr, SBahn, UBahn, Bus, Tram };

        constexpr TransportType(Value type) : mType(type) {}

        static std::string toString(Value type);
        std::string toString() const { return toString(mType); }

        friend std::ostream& operator<<(std::ostream& os, const TransportType& transportType);
        auto operator<=>(const TransportType& other) const = default;

        
    private:
        Value mType;
};