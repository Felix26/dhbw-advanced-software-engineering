#include <cassert>

#include "stationRepository.h"
#include "fakeStationParser.h"

int main()
{
    FakeStationParser fakeParser = FakeStationParser();
    auto stationRepo = StationRepository(fakeParser);

    auto station1 = stationRepo.getStation("de:08311:6508");
    assert(station1->getName() == "Freiburg im Breisgau Hbf");
    assert(station1->getCoordinates().getLatitude() == 47.997458);
    assert(station1->getCoordinates().getLongitude() == 7.840954);

    auto station2 = stationRepo.findStation("de:08212:90");
    assert(station2);
    assert((*station2)->getName() == "Karlsruhe Hbf");
    assert((*station2)->getCoordinates().getLatitude() == 48.993349);
    assert((*station2)->getCoordinates().getLongitude() == 8.401036);

    auto station3 = stationRepo.findStation("nonexistent_id");
    assert(!station3); // Should return std::nullopt for non-existent ID

    return 0;
}