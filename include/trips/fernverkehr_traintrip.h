#pragma once

#include "traintrip.h"

class FernverkehrTrainTrip : public TrainTrip
{
    public:
        using TrainTrip::TrainTrip;

        std::string getTransportName() const override;
        std::string getTransportType() const override;
};