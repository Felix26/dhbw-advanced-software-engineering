#include <cassert>

#include "filters/filter.h"
#include "filters/universalFilter.h"
#include "parser/parserFactory.h"

int main()
{
    auto parser = ParserFactory::createMockParser();
    auto trips = parser->parse();

    auto filter = Filter::filterByYear(2024);

    UniversalFilter::filterTrips(trips, filter);

    assert(trips.size() == 3); // 3 trips in 2024
    for(const auto& trip : trips)
    {
        auto dayPoint = std::chrono::floor<std::chrono::days>(trip->getStartTime());
        std::chrono::year_month_day ymd{dayPoint};
        assert(ymd.year() == std::chrono::year{2024}); // Check that the trip is from the year 2024
    }

    UniversalFilter::filterTrips(trips, Filter::filterByYear(2025));
    assert(trips.size() == 0); // No trips from 2025 should be left after filtering

    return 0;
}