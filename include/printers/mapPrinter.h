#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "printers/core.h"
#include "statistic.h"
#include "valueObjects/station.h"

#include "germanyBoundary.h"

namespace Printers
{
    inline bool isInsideGermany(double lat, double lon)
    {
        bool inside = false;
        for(size_t i = 0, j = Printers::borders.size() - 1; i < Printers::borders.size(); j = i++)
        {
            double xi = Printers::borders[i].first, yi = Printers::borders[i].second;
            double xj = Printers::borders[j].first, yj = Printers::borders[j].second;

            // Strahlensatz: Schneidet der Strahl die Kante?
            bool intersect = ((yi > lat) != (yj > lat)) && (lon < (xj - xi) * (lat - yi) / (yj - yi) + xi);
            if(intersect) inside = !inside;
        }
        return inside;
    }

    inline std::string getHeatmapCell(double ratio)
    {
        ratio = std::clamp(ratio, 0.0, 1.0);

        int r = 0, g = 0, b = 0;

        if (ratio < 0.25)
        {
            // blue (0,255,255) to cyan (0,255,255)
            r = 0;
            g = static_cast<int>(255.0 * (ratio / 0.25));
            b = 255;
        } 
        else if (ratio < 0.5)
        {
            // cyan (0,255,255) to green (0,255,0)
            r = 0;
            g = 255;
            b = static_cast<int>(255.0 * (1.0 - ((ratio - 0.25) / 0.25)));
        } 
        else if (ratio < 0.75)
        {
            // green (0,255,0) to yellow (255,255,0)
            r = static_cast<int>(255.0 * ((ratio - 0.5) / 0.25));
            g = 255;
            b = 0;
        } 
        else
        {
            // yellow (255,255,0) to red (255,0,0)
            r = 255;
            g = static_cast<int>(255.0 * (1.0 - ((ratio - 0.75) / 0.25)));
            b = 0;
        }

        // alpha channel by block character:
        std::string block;
        if (ratio < 0.15)
        {
            block = "\xE2\x96\x91"; // 25% coverage
        } 
        else if (ratio < 0.40)
        {
            block = "\xE2\x96\x92"; // 50% coverage
        } 
        else if (ratio < 0.75)
        {
            block = "\xE2\x96\x93"; // 75% coverage
        } 
        else
        {
            block = "\xE2\x96\x88"; // full block
        }

        // some terminal ansi magic
        return std::format("\x1B[38;2;{};{};{}m{}\x1B[0m", r, g, b, block);
    }

    template <typename ValueType>
    inline std::ostream& operator<<(std::ostream& os, const MapWrapper<Statistic<Station, ValueType>> &wrapper)
    {
        const auto &stats = wrapper.value;
        const size_t width = wrapper.width;
        const size_t height = wrapper.height;

        if (stats.getData().empty())
        {
            os << "No data to display on map." << std::endl;
            return os;
        }

        bool useAverage = wrapper.useAverage;
        if(useAverage)
        {
            useAverage = existsAverage(stats.getData().front().second);
        }

        // bouding box for germany
        const double MIN_LAT = 47.2; // south
        const double MAX_LAT = 55.0; // north
        const double MIN_LON = 5.8;  // west
        const double MAX_LON = 15.0; // east

        std::vector<std::vector<ValueType>> grid(height, std::vector<ValueType>(width, ValueType{}));
        ValueType maxGridValue = ValueType{};
        size_t stationsOnMap = 0;
        size_t stationsIgnored = 0;

        for (const auto& [station, value] : stats.getData())
        {
            double lat = station.getCoordinates().getLatitude();
            double lon = station.getCoordinates().getLongitude();

            if (lat < MIN_LAT || lat > MAX_LAT || lon < MIN_LON || lon > MAX_LON)
            {
                stationsIgnored++;
                continue;
            }

            auto val = getAggregationValue(value, useAverage);

            // map coordinates to grid indices
            size_t x = static_cast<size_t>(std::round(((lon - MIN_LON) / (MAX_LON - MIN_LON)) * (width - 1)));
            size_t y = static_cast<size_t>(std::round(((MAX_LAT - lat) / (MAX_LAT - MIN_LAT)) * (height - 1)));

            x = std::clamp(x, size_t(0), width - 1);
            y = std::clamp(y, size_t(0), height - 1);

            grid[y][x] += val; 
            maxGridValue = std::max(maxGridValue, grid[y][x]);
            stationsOnMap++;
        }

        if (stationsOnMap == 0)
        {
            os << "Keine der Stationen liegt innerhalb von Deutschland.\n";
            return os;
        }
        
        os << "\n=== Deutschland-Karte (" << width << "x" << height << ") ===\n";
        os << std::string(width + 2, '-') << '\n';

        for (size_t y = 0; y < height; ++y)
        {
            os << "|"; 
            for (size_t x = 0; x < width; ++x)
            {
                if (grid[y][x] == ValueType{}) 
                {
                    double cellLon = MIN_LON + (static_cast<double>(x) / (width - 1)) * (MAX_LON - MIN_LON);
                    double cellLat = MAX_LAT - (static_cast<double>(y) / (height - 1)) * (MAX_LAT - MIN_LAT);

                    if (isInsideGermany(cellLat, cellLon)) 
                    {
                        // print a light gray dot for empty cells on land, otherwise print a space
                        os << "\x1B[38;5;243m\xE2\x96\x91\x1B[0m"; 
                    } 
                    else 
                    {
                        os << ' ';
                    }
                }
                else
                {
                    double ratio = grid[y][x] / maxGridValue; 
                    ratio = std::pow(ratio, 1.0/4.0);

                    os << getHeatmapCell(ratio);
                }
            }
            os << "|\n";
        }
        
        os << std::string(width + 2, '-') << '\n';
        os << "Stationen auf Karte: " << stationsOnMap << " (Ausgeblendet: " << stationsIgnored << ")\n";

        return os;
    }
}