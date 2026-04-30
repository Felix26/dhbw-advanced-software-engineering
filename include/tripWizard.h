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
#include "printers/mapPrinter.h"


enum class WizardState
{
    ConfiguringFilter,
    ConfiguringGrouping,
    ConfiguringAggregation,
    ConfiguringOutput,
    ConfiguringOutputStyle,
    Finalizing,
    Exit
};

enum class GroupingType { None, ByTransportType, ByMonth, ByOrigin, ByDestination, ByVisitedStations, ByPassedStops };
enum class AggregationType { None, ByCount, ByDistance, ByDuration, BySpeed };
enum class OutputType { AsTotalValues, AsAverages };
enum class OutputStyle { AsChart, AsMap };
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
        OutputStyle mOutputStyle = OutputStyle::AsChart;

        void handleFilter();
        void handleGrouping();
        void handleAggregation();
        void handleOutput();
        void handleOutputStyle();

        void execute(const Trips &trips);

        size_t getNumberFromCommandLine(size_t min, size_t max);

        WizardState mWizardState = WizardState::ConfiguringFilter;

        template<typename KeyType, typename ValueType>
        inline void renderStatistic(const TripBuckets<KeyType>& buckets, const IAggregator<ValueType> &agg)
        {
            // 1. Die Statistik-Klasse mit den sortierten Eimern und der Rechenlogik füttern
            auto stats = Statistic<KeyType, ValueType>(buckets, agg);

            // 2. Sortierung (Hier standardmäßig nach Key, z.B. Alphabetisch nach Station)
            
            if(mOutputType == OutputType::AsAverages)
            {
                if constexpr (AggregatorResult<ValueType>::supportsAverage)
                {
                    stats.sortByAverage();
                }
            }
            else
            {
                stats.sortByValue();
            }
            size_t consoleWidth = getConsoleWidth() - 10;
            if(mOutputStyle == OutputStyle::AsMap)
            {
                if constexpr (std::is_same_v<Station, KeyType>)
                {   
                    std::cout << "\n--- Auswertung ---\n";
                    std::cout << Printers::map(stats, mOutputType == OutputType::AsAverages, consoleWidth, consoleWidth / 2.5) << std::endl;
                    std::cout << "------------------\n";
                }
                else
                {
                    std::cout << "Die Ausgabe als Karte ist nur für Stationen möglich." << std::endl;
                }
                return;
            }
            // 3. Die Ausgabe (Setzt voraus, dass der operator<< für Statistic überladen ist)
            std::cout << "\n--- Auswertung ---\n";
            std::cout << Printers::barChart(stats, mOutputType == OutputType::AsAverages, consoleWidth) << std::endl;
            std::cout << "------------------\n";
        }

        template<typename KeyType>
        inline void dispatchAggregation(const TripBuckets<KeyType>& buckets)
        {
            switch(mAggregationType)
            {
                case AggregationType::ByDistance:
                    renderStatistic<KeyType, Distance>(buckets, DistanceAggregator{});
                    break;
                case AggregationType::ByDuration:
                    renderStatistic<KeyType, Duration>(buckets, DurationAggregator{});
                    break;
                case AggregationType::ByCount:
                    renderStatistic<KeyType, Count>(buckets, CountAggregator{});
                    break;
                case AggregationType::BySpeed:
                    renderStatistic<KeyType, Speed>(buckets, SpeedAggregator{});
                    break;
                default:
                    std::cout << "Diese Aggregation wird noch nicht unterstützt." << std::endl;
                    break;
            }
        }

        template<typename KeyType>
        inline void processGrouping(const Trips& data, std::function<KeyType(const Trip&)> extractor)
        {
            dispatchAggregation<KeyType>(UniversalGrouper::groupTrips(data, extractor));
        }

        template<typename KeyType>
        inline void processGrouping(const Trips& data, std::function<std::vector<KeyType>(const Trip&)> extractor)
        {
            dispatchAggregation<KeyType>(UniversalGrouper::groupTrips(data, extractor));
        }

        static size_t getConsoleWidth();
};