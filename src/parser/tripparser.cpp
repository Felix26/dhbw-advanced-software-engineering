#include "parser/tripparser.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <regex>

#include "trips/traintrip.h"
#include "trips/bustrip.h"
#include "valueObjects/station.h"
#include "json.hpp"
#include "valueObjects/operator.h"
#include "valueObjects/transportType.h"

using json = nlohmann::json;

TripParser::TripParser(const std::string& filepath, const std::shared_ptr<StationRepository>& stationRepo) : mFilepath(filepath), mStationRepo(stationRepo)
{
}

Trips TripParser::parse()
{
    Trips result;

    std::ifstream file(mFilepath);
    if(!file.is_open())
    {
        std::cerr << "Error: Could not open file!\n";
        return result;
    }

    json root;
    try
    {
        file >> root;
    }
    catch(const json::parse_error& e)
    {
        std::cerr << "JSON parse error: " << e.what() << '\n';
        return result;
    }

    if(!root.contains("data") || !root["data"].is_array())
    {
        return result;
    }

    for(const auto& item : root["data"])
    {
        if(!item.contains("status")) continue;
        int statusId = item["status"].value("id", 0);

        if(!item["status"].contains("train") || item["status"]["train"].is_null()) continue;
        const auto& userJourneyNode = item["status"]["train"];

        std::string lineName = userJourneyNode.value("lineName", "Unknown");
        int distance = userJourneyNode.value("distance", 0);
        int duration = userJourneyNode.value("duration", 0);
        std::string category = userJourneyNode.value("category", "");

        
        // extract origin and start time
        std::string origindhid = "Unknown";
        std::string originName = "Unknown";
        std::string startTimeStr;
        Station origin(originName);
        try
        {
            if(userJourneyNode.contains("origin"))
            {
                originName = userJourneyNode["origin"].value("name", "Unknown");
                origindhid = extractDHID(userJourneyNode["origin"]);

                // If departureReal is empty, use departurePlanned
                startTimeStr = (!userJourneyNode["origin"]["departureReal"].is_null()) ? userJourneyNode["origin"].value("departureReal", "") : userJourneyNode["origin"].value("departurePlanned", "");
            }
            origin = *(mStationRepo->getStation(origindhid));
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning: " << e.what() << ". Using station name from trip data: " << originName << '\n';
        }
        

        // extract destination
        std::string destdhid = "Unknown";
        std::string destName = "Unknown";
        Station dest(destName);

        try
        {
            if(userJourneyNode.contains("destination"))
            {
                destName = userJourneyNode["destination"].value("name", "Unknown");
                destdhid = extractDHID(userJourneyNode["destination"]);
            }
            dest = *(mStationRepo->getStation(destdhid));
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning: " << e.what() << ". Using station name from trip data: " << destName << '\n';
        }
        

        std::chrono::system_clock::time_point startTime;
        if(!startTimeStr.empty())
        {
            // Data format is eg "2026-04-02T10:20:00+00:00"
            std::istringstream ss(startTimeStr);
            std::chrono::system_clock::time_point tp;
            ss >> std::chrono::parse("%Y-%m-%dT%H:%M:%S", tp);
            startTime = tp;
        }

        if(category == "bus")
        {
            auto bus = std::make_shared<BusTrip>(statusId, origin, dest, distance, duration, startTime, lineName);
            result.push_back(bus);
        }
        else
        {
            int opId = 0;
            std::string opName = "Unknown";
            
            if(userJourneyNode.contains("operator") && userJourneyNode["operator"].is_object())
            {
                opId = userJourneyNode["operator"].value("id", 0);
                opName = userJourneyNode["operator"].value("name", "Unknown");
            }
            Operator op(opId, opName);

            std::shared_ptr<TrainTrip> train;
            if(category == "express" || category == "regionalExp" || (category == "nationalExpress" && lineName.find("IC") != std::string::npos)) // "regionalExp" is used for FlixTrains, "nationalExpress" is used for ICEs
            {
                train = std::make_shared<TrainTrip>(statusId, origin, dest, distance, duration, startTime, TransportType::Fernverkehr, lineName, op);
            }
            else if(category == "regional" || category == "nationalExpress") // "nationalExpress" is used for french regional trains
            {
                train = std::make_shared<TrainTrip>(statusId, origin, dest, distance, duration, startTime, TransportType::Regionalverkehr, lineName, op);
            }
            else if(category == "suburban")
            {
                train = std::make_shared<TrainTrip>(statusId, origin, dest, distance, duration, startTime, TransportType::SBahn, lineName, op);
            }
            else if(category == "tram")
            {
                train = std::make_shared<TrainTrip>(statusId, origin, dest, distance, duration, startTime, TransportType::Tram, lineName, op);
            }
            else if(category == "subway")
            {
                train = std::make_shared<TrainTrip>(statusId, origin, dest, distance, duration, startTime, TransportType::UBahn, lineName, op);
            }
            else
            {
                std::cerr << "Unknown category: " << category << '\n';
                continue;
            }

            // extract stopovers from global trip node
            if(item.contains("trip") && item["trip"].contains("stopovers") && item["trip"]["stopovers"].is_array())
            {
                bool isRecording = false;

                for(const auto& stopNode : item["trip"]["stopovers"])
                {
                    std::string stopName = stopNode.value("name", "Unknown");

                    if(stopName == origin.getName())
                    {
                        isRecording = true;
                        continue;
                    }

                    if(stopName == dest.getName())
                    {
                        break;
                    }

                    if(isRecording)
                    {
                        train->addStopover(Station(stopName));
                    }
                }
            }
            result.push_back(train);
        }
    }

    return result;
}

std::string TripParser::extractDHIDFromIdentifiers(const json &identifiersNode) const
{
    for(const auto& idNode : identifiersNode)
    {
        if(idNode.value("type", "") == "ifopt")
        {
            std::string id = idNode.value("identifier", "Unknown");
            id.erase(id.find_last_not_of(" \n\r\t") + 1);
            return id;
        }
    }

    // If no identifier with type "ifopt" is found, try to extract any identifier that matches the DHID pattern (e.g., "de:08215:1221")
    std::regex dhidRegex(R"(de:\d{5}:\d{1,5})");
    std::smatch match;

    for(const auto& idNode : identifiersNode)
    {
        std::string identifier = idNode.value("identifier", "");
        
        // Sucht im String nach dem Muster
        if(std::regex_search(identifier, match, dhidRegex))
        {
            // match.str(0) returns the part of the string that matched the regex
            // "de-DELFI_de:08215:1221:3" -> "de:08215:1221"
            return match.str(0); 
        }
    }
    throw std::runtime_error("No dhid identifier found");
}

std::string TripParser::extractDHID(const json &destinationNode) const
{
    if(destinationNode.contains("identifiers"))
    {
        return extractDHIDFromIdentifiers(destinationNode["identifiers"]);
    }
    
    
    throw std::runtime_error("Destination node does not contain identifiers");
}