#pragma once

#include "istatistic.h"
#include <map>
#include <string>

class TransportTypeStatistic : public IStatistic<std::map<std::string, int>>
{
    public:
        ~TransportTypeStatistic() override = default;

        std::map<std::string, int> evaluate(const std::vector<std::shared_ptr<Trip>>& trips) const override;
};