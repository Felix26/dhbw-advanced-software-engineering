#pragma once

#include <string>
#include <vector>
#include <memory>

#include "station.h"

class Trip
{
    public:
        Trip(int id, const Station& origin, const Station& destination, int distance, int duration);
        virtual ~Trip() = default;

        int getId() const;
        Station getOrigin() const;
        Station getDestination() const;
        int getDistance() const;
        int getDuration() const;

        virtual std::string getTransportName() const = 0;
        virtual std::string getTransportType() const = 0;

    protected:
        int mId;
        Station mOrigin;
        Station mDestination;
        int distance; // m
        int duration; // min
};

using Trips = std::vector<std::shared_ptr<Trip>>;