#pragma once

#include "traintrip.h"

class TramTrainTrip : public TrainTrip
{
    public:
        using TrainTrip::TrainTrip;

        std::string getTransportType() const override;
};