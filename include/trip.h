#pragma once

#include <string>

#include "station.h"

class Trip
{
    public:
        Trip(int id, const Station& origin, const Station& destination, int distance);
        virtual ~Trip() = default;

        int getId() const;
        Station getOrigin() const;
        Station getDestination() const;
        int getDistance() const;

        virtual std::string getTransportType() const = 0;

    protected:
        int mId;
        Station mOrigin;
        Station mDestination;
        int distance;
};