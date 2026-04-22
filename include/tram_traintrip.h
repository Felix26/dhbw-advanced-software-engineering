#pragma once

#include "traintrip.h"

class TramTrainTrip : public TrainTrip
{
    using TrainTrip::TrainTrip;

    public:
        std::string getTransportType() const override;
};