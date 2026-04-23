#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>

#include "station.h"

class Trip
{
    public:
        Trip(int id, const Station& origin, const Station& destination, int distance, int duration, const std::chrono::system_clock::time_point startTime);
        virtual ~Trip() = default;

        int getId() const;
        Station getOrigin() const;
        Station getDestination() const;
        int getDistance() const;
        int getDuration() const;
        std::chrono::system_clock::time_point getStartTime() const;

        virtual std::string getTransportName() const = 0;
        virtual std::string getTransportType() const = 0;

    protected:
        int mId;
        Station mOrigin;
        Station mDestination;
        int mDistance; // m
        int mDuration; // min
        std::chrono::system_clock::time_point mStartTime;
};

using Trips = std::vector<std::shared_ptr<Trip>>;