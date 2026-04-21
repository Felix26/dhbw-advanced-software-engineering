#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "iparser.h"
#include "tripparser.h"
#include "trip.h"
#include "traintrip.h"
#include "station.h"

int main()
{
    // 1. Parser-Instanz erstellen (Pfad zu deinem echten Export)
    // Wir nutzen das Interface IParser, um DIP einzuhalten.
    std::unique_ptr<IParser> tripParser = std::make_unique<TripParser>("../data/testdata.json");

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

    // 3. Durch die Fahrten iterieren und Polymorphismus testen
    for (const auto& trip : loadedTrips)
    {
        // Nutzt die virtuelle Methode getTransportType()
        std::cout << "[" << trip->getTransportType() << "]" << std::endl;
        std::cout << "  Von:  " << trip->getOrigin().getName() << std::endl;
        std::cout << "  Nach: " << trip->getDestination().getName() << std::endl;
        std::cout << "  Distanz: " << std::fixed << std::setprecision(2) 
                  << (trip->getDistance() / 1000.0) << " km" << std::endl;

        // 4. Test der Klassentrennung (Nur Züge haben Stopovers)
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