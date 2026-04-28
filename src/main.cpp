#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "zhvStationParser.h"
#include "parser/iparser.h"
#include "parser/parserFactory.h"
#include "trips/trip.h"
#include "trips/traintrip.h"

#include "tripWizard.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    auto stationRepo = StationRepository(ZHVStationParser("C:\\Users\\Felix\\Desktop\\dhbw-advanced-software-engineering\\data\\zHV.csv"));
    std::unique_ptr<IParser> tripParser = ParserFactory::createParserFromFolder("C:\\Users\\Felix\\Nextcloud\\Advanced SWE", std::make_shared<StationRepository>(stationRepo));
    //std::unique_ptr<IParser> tripParser = ParserFactory::createMockParser();

    Trips trips = tripParser->parse();

    // Statistic statistic(UniversalGrouper::groupTrips(trips, TripGrouper::byVisitedStations()), CountAggregator());

    // statistic.sortByValue();

    // std::cout << Printers::PrettyWrapper(statistic) << std::endl;
    // //std::cout << statistic << std::endl;

    TripWizard{}.run(trips);
    

    return 0;
}