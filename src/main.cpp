#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "parser/iparser.h"
#include "parser/parserFactory.h"
#include "trips/trip.h"
#include "trips/traintrip.h"

#include "printers/statisticPrinter.h"
#include "statistic.h"
#include "aggregators/countAggregator.h"

#include "groupers/tripGroupers.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    std::unique_ptr<IParser> tripParser = ParserFactory::createParserFromFolder("C:\\Users\\Felix\\Nextcloud\\Advanced SWE");
    //std::unique_ptr<IParser> tripParser = ParserFactory::createMockParser();

    Trips trips = tripParser->parse();

    Statistic statistic(UniversalGrouper::groupTrips(trips, TripGrouper::byTransportType()), CountAggregator());

    std::cout << Printers::PrettyWrapper(statistic) << std::endl;
    //std::cout << statistic << std::endl;
    

    return 0;
}