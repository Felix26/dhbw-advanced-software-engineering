#include "parser/folderTripParser.h"

#include <filesystem>

#include "parser/tripparser.h"

Trips FolderTripParser::parse()
{
    Trips allTrips;

    for (const auto& entry : std::filesystem::directory_iterator(mFolderPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".json")
        {
            TripParser parser(entry.path().string());
            Trips trips = parser.parse();
            allTrips.insert(allTrips.end(), trips.begin(), trips.end());
        }
    }

    return allTrips;
}