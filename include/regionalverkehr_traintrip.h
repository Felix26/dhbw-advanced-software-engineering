#pragma once

#include "traintrip.h"

class RegionalverkehrTrainTrip : public TrainTrip
{
    public:
        using TrainTrip::TrainTrip;

        std::string getTransportType() const override;
};