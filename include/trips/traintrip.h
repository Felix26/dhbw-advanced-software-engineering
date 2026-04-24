#pragma once

#include "trip.h"

#include <vector>
#include <string>

#include "operator.h"

class TrainTrip : public Trip
{
    public:
        TrainTrip(int id, const Station& origin, const Station& destination, int distanceKm, int duration, const std::chrono::system_clock::time_point startTime, const TransportType& transportType, const std::string& lineName, const Operator& op);
        ~TrainTrip() override = default;

        std::string getLineName() const;
        Operator getOperator() const;


        void addStopover(const Station& station);
        const std::vector<Station>& getStopovers() const;
        int getStopoverCount() const;

        std::string getTransportName() const override;

    protected:
        std::string mLineName;
        Operator mOperator;
        std::vector<Station> mStopovers;
};