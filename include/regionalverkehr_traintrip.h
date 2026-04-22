#pragma once

#include "traintrip.h"

class RegionalverkehrTrainTrip : public TrainTrip
{
    using TrainTrip::TrainTrip;

    public:
        std::string getTransportType() const override;
};