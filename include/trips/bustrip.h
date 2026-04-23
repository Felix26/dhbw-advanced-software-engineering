#pragma once

#include "trip.h"

#include <string>

class BusTrip : public Trip
{
    public:
        BusTrip(int id, const Station& origin, const Station& destination, int distance, int duration, const std::chrono::system_clock::time_point startTime, const std::string& busNumber);
        ~BusTrip() override = default;

        std::string getBusNumber() const;

        std::string getTransportName() const override;
        std::string getTransportType() const override;

    private:
        std::string mBusNumber;
};
