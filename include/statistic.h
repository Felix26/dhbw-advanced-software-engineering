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
                ValueType aggregatedValue = aggregator.aggregate(trips).aggregationValue;
                data.emplace_back(key, aggregatedValue);
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
                return ascending ? a.second < b.second : a.second > b.second;
            });
        }

        friend std::ostream& operator<<(std::ostream &os, const Statistic &statistic)
        {
            for(const auto& [key, value] : statistic.data)
            {
                os << key << ": " << value << std::endl;
            }
            return os;
        }
         
    private:
        std::vector<std::pair<KeyType, ValueType>> data;
};