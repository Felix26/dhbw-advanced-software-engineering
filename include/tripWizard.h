#pragma once

#include <cstdint>
#include <variant>
#include <iostream>

#include "filters/filter.h"
#include "trips/trip.h"

#include "valueObjects/allValueObjectHeaders.h"

#include "groupers/universalGrouper.h"

#include "aggregators/countAggregator.h"
#include "aggregators/distanceAggregator.h"
#include "aggregators/durationAggregator.h"
#include "aggregators/speedAggregator.h"

#include "statistic.h"

#include "printers/statisticPrinter.h"


enum class WizardState
{
    ConfiguringFilter,
    ConfiguringGrouping,
    ConfiguringAggregation,
    ConfiguringOutput,
    //ConfiguringOrder,
    Finalizing,
    Exit
};

enum class GroupingType { None, ByTransportType, ByMonth, ByOrigin, ByDestination, ByVisitedStations, ByPassedStops };
enum class AggregationType { None, ByCount, ByDistance, ByDuration, BySpeed };
enum class OutputType { AsTotalValues, AsAverages };
//enum class OrderType { KeyAscending, KeyDescending, ValueAscending, ValueDescending }

class TripWizard
{
    public:
        void run(const Trips &trips);

    private:
        std::vector<TripFilterFunction> mFilters; 
        GroupingType mGroupingType = GroupingType::None;
        AggregationType mAggregationType = AggregationType::None;
        OutputType mOutputType = OutputType::AsTotalValues;

        void handleFilter();
        void handleGrouping();
        void handleAggregation();
        void handleOutput();

        void execute(const Trips &trips);

        size_t getNumberFromCommandLine(size_t min, size_t max);

        WizardState mWizardState = WizardState::ConfiguringFilter;

        template<typename TKey, typename TValue>
        inline void renderStatistic(const TripBuckets<TKey>& buckets, const IAggregator<TValue> &agg)
        {
            // 1. Die Statistik-Klasse mit den sortierten Eimern und der Rechenlogik füttern
            auto stats = Statistic<TKey, TValue>(buckets, agg);

            // 2. Sortierung (Hier standardmäßig nach Key, z.B. Alphabetisch nach Station)
            stats.sortByValue(); 

            // 3. Die Ausgabe (Setzt voraus, dass der operator<< für Statistic überladen ist)
            std::cout << "\n--- Auswertung ---\n";
            std::cout << Printers::pretty(stats, mOutputType == OutputType::AsAverages) << std::endl;
            std::cout << "------------------\n";
        }

        template<typename TKey>
        inline void dispatchAggregation(const TripBuckets<TKey>& buckets)
        {
            switch(mAggregationType)
            {
                case AggregationType::ByDistance:
                    renderStatistic<TKey, Distance>(buckets, DistanceAggregator{});
                    break;
                case AggregationType::ByDuration:
                    renderStatistic<TKey, Duration>(buckets, DurationAggregator{});
                    break;
                case AggregationType::ByCount:
                    renderStatistic<TKey, Count>(buckets, CountAggregator{});
                    break;
                case AggregationType::BySpeed:
                    renderStatistic<TKey, Speed>(buckets, SpeedAggregator{});
                    break;
                default:
                    std::cout << "Diese Aggregation wird noch nicht unterstützt." << std::endl;
                    break;
            }
        }

        template<typename TKey>
        inline void processGrouping(const Trips& data, std::function<TKey(const Trip&)> extractor)
        {
            dispatchAggregation<TKey>(UniversalGrouper::groupTrips(data, extractor));
        }

        template<typename TKey>
        inline void processGrouping(const Trips& data, std::function<std::vector<TKey>(const Trip&)> extractor)
        {
            dispatchAggregation<TKey>(UniversalGrouper::groupTrips(data, extractor));
        }
};