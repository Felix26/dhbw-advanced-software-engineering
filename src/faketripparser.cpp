#include "faketripparser.h"
#include "trips/fernverkehr_traintrip.h"
#include "trips/regionalverkehr_traintrip.h"
#include "trips/s-bahn_traintrip.h"
#include "trips/u-bahn_traintrip.h"
#include "trips/tram_traintrip.h"
#include "trips/bustrip.h"
#include "station.h"
#include "operator.h"

std::vector<std::shared_ptr<Trip>> FakeTripParser::parse()
{
    std::vector<std::shared_ptr<Trip>> result;

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

    // 1. Fernverkehr: ICE von Freiburg nach Mannheim
    auto ice = std::make_shared<FernverkehrTrainTrip>(1001, freiburg, mannheim, 200000, 90, "ICE 75", dbFern);
    ice->addStopover(offenburg);
    ice->addStopover(karlsruhe);
    result.push_back(ice);

    // 2. Regionalverkehr: RE7 von Offenburg nach Freiburg
    auto re7 = std::make_shared<RegionalverkehrTrainTrip>(1002, offenburg, freiburg, 63000, 45, "RE7", dbRegio);
    re7->addStopover(emmendingen);
    re7->addStopover(denzlingen);
    result.push_back(re7);

    // 3. Regionalverkehr: RB26 von Freiburg nach Denzlingen
    auto rb26 = std::make_shared<SBahnTrainTrip>(1003, freiburg, denzlingen, 12000, 15, "S4", dbRegio);
    result.push_back(rb26);

    // 4. Tram: Linie 1 in Freiburg
    auto tram = std::make_shared<TramTrainTrip>(1004, bertoldsbrunnen, stadttheater, 800, 2, "Linie 1", vagfr);
    result.push_back(tram);

    // 5. Bus: Bus in Freiburg
    auto bus = std::make_shared<BusTrip>(1005, stadttheater, bertoldsbrunnen, 800, 2, "Bus 10");
    result.push_back(bus);

    return result;
}