#pragma once

#include "traintrip.h"

class SBahnTrainTrip : public TrainTrip
{
    public:
        using TrainTrip::TrainTrip;

        std::string getTransportType() const override;
};