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

int main(int argc, char* argv[])
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_data_folder>" << std::endl;
        return 1;
    }

    auto stationRepo = StationRepository(ZHVStationParser(argv[1] + std::string("/zHV.csv")));
    std::unique_ptr<IParser> tripParser = ParserFactory::createParserFromFolder(argv[1], std::make_shared<StationRepository>(stationRepo));

    Trips trips = tripParser->parse();

    TripWizard{}.run(trips);
    

    return 0;
}