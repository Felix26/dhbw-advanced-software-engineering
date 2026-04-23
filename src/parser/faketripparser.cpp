#include <chrono>

#include "parser/faketripparser.h"
#include "trips/fernverkehr_traintrip.h"
#include "trips/regionalverkehr_traintrip.h"
#include "trips/s-bahn_traintrip.h"
#include "trips/u-bahn_traintrip.h"
#include "trips/tram_traintrip.h"
#include "trips/bustrip.h"
#include "station.h"
#include "operator.h"

auto mockTime(int y, int m, int d, int h, int min)
{
    using namespace std::chrono;
    return sys_days{year{y} / m / d} + hours{h} + minutes{min};
}

Trips FakeTripParser::parse()
{
    Trips result;

    Station freiburg(1, "Freiburg (Breisgau) Hbf");
    Station offenburg(2, "Offenburg");
    Station karlsruhe(3, "Karlsruhe Hbf");
    Station mannheim(4, "Mannheim Hbf");
    Station denzlingen(5, "Denzlingen");
    Station emmendingen(6, "Emmendingen");
    Station bertoldsbrunnen(7, "Bertoldsbrunnen");
    Station stadttheater(8, "Stadttheater");

    Operator dbFern(10, "DB Fernverkehr AG");
    Operator dbRegio(11, "DB Regio Baden-Wuerttemberg");
    Operator vagfr(12, "VAG Freiburg");

    auto time1 = mockTime(2024, 6, 1, 8, 0);
    auto time2 = mockTime(2024, 6, 1, 9, 0);
    auto time3 = mockTime(2024, 6, 1, 10, 0);
    auto time4 = mockTime(2025, 6, 1, 11, 0);
    auto time5 = mockTime(2026, 6, 1, 12, 0);

    // 1. Fernverkehr: ICE von Freiburg nach Mannheim
    auto ice = std::make_shared<FernverkehrTrainTrip>(1001, freiburg, mannheim, 200000, 90, time1, "ICE 75", dbFern);
    ice->addStopover(offenburg);
    ice->addStopover(karlsruhe);
    result.push_back(ice);

    // 2. Regionalverkehr: RE7 von Offenburg nach Freiburg
    auto re7 = std::make_shared<RegionalverkehrTrainTrip>(1002, offenburg, freiburg, 63000, 45, time2, "RE7", dbRegio);
    re7->addStopover(emmendingen);
    re7->addStopover(denzlingen);
    result.push_back(re7);

    // 3. Regionalverkehr: RB26 von Freiburg nach Denzlingen
    auto rb26 = std::make_shared<SBahnTrainTrip>(1003, freiburg, denzlingen, 12000, 15, time3, "S4", dbRegio);
    result.push_back(rb26);

    // 4. Tram: Linie 1 in Freiburg
    auto tram = std::make_shared<TramTrainTrip>(1004, bertoldsbrunnen, stadttheater, 800, 2, time4, "Linie 1", vagfr);
    result.push_back(tram);

    // 5. Bus: Bus in Freiburg
    auto bus = std::make_shared<BusTrip>(1005, stadttheater, bertoldsbrunnen, 800, 2, time5, "Bus 10");
    result.push_back(bus);

    return result;
}