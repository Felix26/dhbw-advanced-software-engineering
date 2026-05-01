#include <cassert>

#include <sstream>

#include "valueObjects/allValueObjectHeaders.h"

int main()
{
    Coordinates coords(47.997458, 7.840954);
    assert(coords.getLatitude() == 47.997458);
    assert(coords.getLongitude() == 7.840954);
    std::ostringstream ss;
    ss << coords;
    assert(ss.str() == "Coordinates(47.9974580, 7.8409540)");

    Operator op(1, "DB InfraNoGo");
    Operator op2(1, "DB InfraGo");
    Operator op3(2, "Another Operator");
    assert(op.getName() == "DB InfraNoGo");
    assert(op == op2); // Same ID, should be equal
    assert(op != op3); // Different ID, should not be equal
    assert(Operator::getKeyTypeName() == "Betreiber");
    
    Station station("Freiburg (Breisgau) Hbf", coords);
    assert(station.getName() == "Freiburg (Breisgau) Hbf");
    assert(station.getCoordinates().getLatitude() == coords.getLatitude());
    assert(station.getCoordinates().getLongitude() == coords.getLongitude());
    assert(station == Station("Freiburg (Breisgau) Hbf", Coordinates(0.0, 0.0))); // Same name, should be equal
    assert(station != Station("Offenburg", coords)); // Different name, should not be equal
    assert(Station::getKeyTypeName() == "Station");
    ss.str("");
    ss << station;
    assert(ss.str() == "Freiburg (Breisgau) Hbf");

    TransportType type = TransportType::Fernverkehr;
    assert(type == TransportType::Fernverkehr);
    assert(TransportType::getKeyTypeName() == "Verkehrsmittel");
    assert(type.toString() == "Fernverkehr");
    type = TransportType::Regionalverkehr;
    assert(type.toString() == "Regionalverkehr");
    type = TransportType::SBahn;
    assert(type.toString() == "S-Bahn");
    type = TransportType::UBahn;
    assert(type.toString() == "U-Bahn");
    type = TransportType::Bus;
    assert(type.toString() == "Bus");
    type = TransportType::Tram;
    assert(type.toString() == "Tram");
    type = TransportType::Unknown;
    assert(type.toString() == "Unknown");

    ss.str("");
    ss << type;
    assert(ss.str() == "Unknown");

    return 0;
}