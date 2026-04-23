#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "parser/iparser.h"
#include "parser/parserFactory.h"
#include "trips/trip.h"
#include "trips/traintrip.h"
#include "station.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    std::unique_ptr<IParser> tripParser = ParserFactory::createParserFromFile("../data/testdata.json");
    //std::unique_ptr<IParser> tripParser = ParserFactory::createMockParser();

    std::cout << "--- Traewelling Statistik Tool: Datenimport-Test ---" << std::endl;

    // 2. Parse-Vorgang starten
    std::vector<std::shared_ptr<Trip>> loadedTrips = tripParser->parse();

    if (loadedTrips.empty())
    {
        std::cerr << "Keine Fahrten geladen oder Datei nicht gefunden." << std::endl;
        return 1;
    }

    std::cout << "Erfolgreich " << loadedTrips.size() << " Fahrten geladen." << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (const auto& trip : loadedTrips)
    {
        std::cout << "[" << trip->getTransportName() << "]" << std::endl;
        std::cout << "  Von:  " << trip->getOrigin().getName() << std::endl;
        std::cout << "  Nach: " << trip->getDestination().getName() << std::endl;
        std::cout << "  Distanz: " << std::fixed << std::setprecision(2) << (trip->getDistance() / 1000.0) << " km" << std::endl;
        std::cout << "  Dauer: " << trip->getDuration() << " min" << std::endl;

        auto train = std::dynamic_pointer_cast<TrainTrip>(trip);
        if (train)
        {
            std::cout << "  Betreiber: " << train->getOperator().getName() << std::endl;
            std::cout << "  Zwischenhalte (" << train->getStopoverCount() << "): ";
            
            const auto& stops = train->getStopovers();
            for (size_t i = 0; i < stops.size(); ++i)
            {
                std::cout << stops[i].getName() << (i < stops.size() - 1 ? ", " : "");
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Test erfolgreich abgeschlossen." << std::endl;

    return 0;
}