#pragma once

#include <ostream>

#include "groupers/universalGrouper.h"
#include "aggregators/iaggregator.h"

template<typename KeyType, typename ValueType>
class Statistic
{
    public:
        Statistic(const TripBuckets<KeyType> &buckets, const IAggregator<ValueType> &aggregator)
        {
            for(const auto& [key, trips] : buckets)
            {
                auto aggregatorResult = aggregator.aggregate(trips);
                data.emplace_back(key, aggregatorResult);
            }
        }

        void sortByKey(bool ascending = true)
        {
            std::sort(data.begin(), data.end(), [ascending](const auto &a, const auto &b)
            {
                return ascending ? a.first < b.first : a.first > b.first;
            });
        }

        void sortByValue(bool ascending = true)
        {
            std::sort(data.begin(), data.end(), [ascending](const auto &a, const auto &b)
            {
                return ascending ? a.second.aggregationValue < b.second.aggregationValue : a.second.aggregationValue > b.second.aggregationValue;
            });
        }

        friend std::ostream& operator<<(std::ostream &os, const Statistic &statistic)
        {
            for(const auto& [key, value] : statistic.data)
            {
                auto average = value.getAverage();
                if(average)
                {
                    os << key << ": " << value.aggregationValue << " (Average: " << *average << ")" << std::endl;
                }
                else
                {
                    os << key << ": " << value.aggregationValue << std::endl;
                }
            }
            return os;
        }
         
    private:
        std::vector<std::pair<KeyType, AggregatorResult<ValueType>>> data;
};