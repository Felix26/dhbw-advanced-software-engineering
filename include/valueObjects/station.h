#pragma once
#include <string>
#include <ostream>

class Station
{
    public:
        Station(const std::string& name) : mName(name) {}


        bool operator==(const Station& other) const;
        auto operator<=>(const Station& other) const = default;
        friend std::ostream& operator<<(std::ostream& os, const Station& station);


        std::string getName() const { return mName; }

        static std::string getKeyTypeName();
    private:
        std::string mName;
};