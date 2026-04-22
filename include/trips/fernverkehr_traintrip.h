#pragma once

#include "traintrip.h"

class FernverkehrTrainTrip : public TrainTrip
{
    public:
        using TrainTrip::TrainTrip;

        std::string getTransportType() const override;
};