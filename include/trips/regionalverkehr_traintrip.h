#pragma once

#include "traintrip.h"

class RegionalverkehrTrainTrip : public TrainTrip
{
    public:
        using TrainTrip::TrainTrip;

        std::string getTransportName() const override;
        std::string getTransportType() const override;
};