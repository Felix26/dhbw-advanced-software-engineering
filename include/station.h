#pragma once
#include <string>

class Station
{
    public:
        Station(int id, const std::string& name) : mID(id), mName(name) {}


        bool operator==(const Station& other) const;

        int getId() const { return mID; }
        std::string getName() const { return mName; }

    private:
        int mID;
        std::string mName;
};