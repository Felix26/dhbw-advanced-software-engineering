#pragma once
#include <string>
#include <ostream>

class Station
{
    public:
        Station(int id, const std::string& name) : mID(id), mName(name) {}


        bool operator==(const Station& other) const;
        auto operator<=>(const Station& other) const = default;
        friend std::ostream& operator<<(std::ostream& os, const Station& station);


        int getId() const { return mID; }
        std::string getName() const { return mName; }

    private:
        int mID;
        std::string mName;
};