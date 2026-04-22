#pragma once

#include "traintrip.h"

class FernverkehrTrainTrip : public TrainTrip
{
    using TrainTrip::TrainTrip;
    public:
        FernverkehrTrainTrip(int id, const Station& origin, const Station& destination, int distanceKm, const std::string& lineName, const Operator& op);
        ~FernverkehrTrainTrip() override = default;

        std::string getTransportType() const override;
};