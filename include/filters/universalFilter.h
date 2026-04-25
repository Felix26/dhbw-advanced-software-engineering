#pragma once

#include <functional>
#include <vector>

#include <trips/trip.h>

class UniversalFilter
{
    public:
        static void filterTrips(Trips &trips, const std::function<bool(const Trip&)>& filterFunc);
};