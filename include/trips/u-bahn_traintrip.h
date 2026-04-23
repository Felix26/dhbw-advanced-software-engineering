#pragma once

#include "traintrip.h"

class UBahnTrainTrip : public TrainTrip
{
    public:
        using TrainTrip::TrainTrip;

        virtual std::string getTransportType() const override;
};