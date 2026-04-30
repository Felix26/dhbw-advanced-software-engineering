#include "fakeStationParser.h"

std::unordered_map<std::string, ZHVData> FakeStationParser::parseStations() const
{
    std::unordered_map<std::string, ZHVData> stationDataMap;

    // Faked Stations: Freiburg Hbf; Offenburg; Karlsruhe Hbf; Mannheim Hbf; Denzlingen; Emmendingen; Freiburg Bertoldsbrunnen; Freiburg Stadttheater, Freiburg im Breisgau
    stationDataMap["de:08311:6508"] = ZHVData{"de:08311:6508", "Freiburg Hbf", "Freiburg im Breisgau", Coordinates{47.997458, 7.840954}};
    stationDataMap["de:08317:14506"] = ZHVData{"de:08317:14506", "Offenburg", "Offenburg", Coordinates{48.476388, 7.946587}};
    stationDataMap["de:08212:90"] = ZHVData{"de:08212:90", "Karlsruhe Hbf", "Karlsruhe", Coordinates{48.993349, 8.401036}};
    stationDataMap["de:08222:2417"] = ZHVData{"de:08222:2417", "Mannheim Hbf", "Mannheim", Coordinates{49.479747, 8.469936}};
    stationDataMap["de:08316:6505"] = ZHVData{"de:08316:6505", "Denzlingen", "Denzlingen", Coordinates{48.06896, 7.881782}};
    stationDataMap["de:08316:90"] = ZHVData{"de:08316:90", "Emmendingen", "Emmendingen", Coordinates{48.119671, 7.846982}};
    stationDataMap["de:08311:30100"] = ZHVData{"de:08311:30100", "Freiburg Bertoldsbrunnen", "Freiburg im Breisgau", Coordinates{47.994867, 7.849856}};
    stationDataMap["de:08311:30106"] = ZHVData{"de:08311:30106", "Freiburg Stadttheater", "Freiburg im Breisgau", Coordinates{47.995414, 7.845913}};

    return stationDataMap;
}