#include <iostream>

#include "statistics/transportTypeStatistic.h"
#include "parser/parserFactory.h"
#include "trips/trip.h"


int main()
{
    auto parser = ParserFactory::createParserFromFile("../data/testdata.json");

    // 1. Statistik ausführen
    TransportTypeStatistic typeStat;
    auto transportDistribution = typeStat.evaluate(parser->parse());

    // 2. Wunderschön formatierte Ausgabe
    std::cout << "\n=== GENUTZTE VERKEHRSMITTEL ===\n";
    
    // C++17 Structured Binding für Maps (Schlüssel und Wert direkt entpacken!)
    for (const auto& [transportType, count] : transportDistribution) 
    {
        std::cout << "- " << transportType << ": " << count << "x\n";
    }

    return 0;
}