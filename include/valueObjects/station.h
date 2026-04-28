#pragma once
#include <string>
#include <ostream>

#include "valueObjects/coordinates.h"

class Station
{
    public:
        Station(const std::string &name, const Coordinates &coordinates) : mName(name), mCoordinates(coordinates) {}


        bool operator==(const Station& other) const;
        auto operator<=>(const Station& other) const = default;
        friend std::ostream& operator<<(std::ostream& os, const Station& station);


        std::string getName() const { return mName; }
        Coordinates getCoordinates() const { return mCoordinates; }

        static std::string getKeyTypeName();
    private:
        std::string mName;
        Coordinates mCoordinates;
};