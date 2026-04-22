#pragma once

#include "traintrip.h"

class UBahnTrainTrip : public TrainTrip
{
    using TrainTrip::TrainTrip;

    public:
        virtual std::string getTransportType() const override;
};