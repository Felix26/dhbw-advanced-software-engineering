#pragma once

#include <format>
#include <iomanip>

#include "printers/core.h"
#include "trips/trip.h"
#include "trips/traintrip.h"
#include "trips/bustrip.h"
#include "valueObjects/duration.h"
#include "valueObjects/distance.h"
#include "valueObjects/speed.h"

namespace Printers
{
    /* This formats a collection of trips in the style of
        Trip: Zug RE7 (Emmendingen -> Freiburg)
        | ID:			    283475
        | Länge: 		    2345,3789245km
        | Dauer:		    234154min
        | Geschwindigkeit	läne/dauer
        | Datum:		    34. April 3095
        | Betreiber:		DB InfraNoGo*/
    inline std::ostream& operator<<(std::ostream& os, const PrettyWrapper<Trips>& wrapper)
    {
        for (const auto& trip : wrapper.value)
        {
            // Header
            os << "Trip: " << trip->getTransportName();

            // prigin and destination
            os << ": " << trip->getOrigin().getName() << " -> " << trip->getDestination().getName() << "\n";

            // generic data (id, length, duration, speed, date)
            os << " | " << std::format("{:<20}", "ID:") << trip->getId() << "\n";
            os << " | " << std::format("{:<20}", "Länge:") << trip->getDistance() << "\n";
            os << " | " << std::format("{:<20}", "Dauer:") << trip->getDuration() << "\n";

            auto speed = trip->getDistance() / trip->getDuration();
            os << " | " << std::format("{:<20}", "Geschwindigkeit:") << speed << "\n";
            
            os << " | " << std::format("{:<20}", "Datum:") << std::format("{:%d. %B %Y}", trip->getStartTime()) << "\n";

            // for trains, print the operator
            if (auto train = dynamic_cast<TrainTrip*>(trip.get())) 
            {
                os << " | " << std::format("{:<20}", "Betreiber:") << train->getOperator().getName() << "\n";
            }
            
            os << "\n";
        }
        return os;
    }
}