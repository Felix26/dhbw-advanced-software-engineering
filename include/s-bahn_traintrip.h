#pragma once

#include "traintrip.h"

class SBahnTrainTrip : public TrainTrip
{
    using TrainTrip::TrainTrip;

    public:
        std::string getTransportType() const override;
};