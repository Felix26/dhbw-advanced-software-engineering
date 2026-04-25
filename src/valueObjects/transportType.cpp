#include "valueObjects/transportType.h"

std::string TransportType::toString(Value type)
{
    switch(type)
    {
        case Fernverkehr: return "Fernverkehr";
        case Regionalverkehr: return "Regionalverkehr";
        case SBahn: return "S-Bahn";
        case UBahn: return "U-Bahn";
        case Bus: return "Bus";
        case Tram: return "Tram";
        default: return "Unknown";
    }
}

std::string TransportType::getKeyTypeName()
{
    return "Verkehrsmittel";
}

std::ostream& operator<<(std::ostream& os, const TransportType& transportType)
{
    os << TransportType::toString(transportType.mType);
    return os;
}