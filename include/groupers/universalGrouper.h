#pragma once

#include <vector>
#include <memory>
#include <map>
#include <functional>

#include "trips/trip.h"

template<typename KeyType>
using TripBuckets = std::map<KeyType, Trips>;

class UniversalGrouper
{
    public:
        template<typename KeyType>
        static TripBuckets<KeyType> groupTrips(const Trips& trips, const std::function<KeyType(const Trip&)>& keyExtractor)
        {
            TripBuckets<KeyType> buckets;
            for (const auto& trip : trips)
            {
                KeyType key = keyExtractor(*trip);
                buckets[key].push_back(trip);
            }
            return buckets;
        }
};