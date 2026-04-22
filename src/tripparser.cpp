#include "tripparser.h"

#include <fstream>
#include <iostream>

#include "fernverkehr_traintrip.h"
#include "regionalverkehr_traintrip.h"
#include "s-bahn_traintrip.h"
#include "u-bahn_traintrip.h"
#include "tram_traintrip.h"
#include "bustrip.h"
#include "station.h"
#include "json.hpp"
#include "operator.h"

using json = nlohmann::json;

TripParser::TripParser(const std::string& filepath) : mFilepath(filepath)
{
}

std::vector<std::shared_ptr<Trip>> TripParser::parse()
{
    std::vector<std::shared_ptr<Trip>> result;

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

        // extract origin
        int originId = 0;
        std::string originName = "Unknown";
        if(userJourneyNode.contains("origin"))
        {
            originId = userJourneyNode["origin"].value("id", 0);
            originName = userJourneyNode["origin"].value("name", "Unknown");
        }
        Station origin(originId, originName);

        // extract destination
        int destId = 0;
        std::string destName = "Unknown";
        if(userJourneyNode.contains("destination"))
        {
            destId = userJourneyNode["destination"].value("id", 0);
            destName = userJourneyNode["destination"].value("name", "Unknown");
        }
        Station dest(destId, destName);

        if(category == "bus")
        {
            auto bus = std::make_shared<BusTrip>(statusId, origin, dest, distance, duration, lineName);
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
            if(category == "express")
            {
                train = std::make_shared<FernverkehrTrainTrip>(statusId, origin, dest, distance, duration, lineName, op);
            }
            else if(category == "regional")
            {
                train = std::make_shared<RegionalverkehrTrainTrip>(statusId, origin, dest, distance, duration, lineName, op);
            }
            else if(category == "suburban")
            {
                train = std::make_shared<SBahnTrainTrip>(statusId, origin, dest, distance, duration, lineName, op);
            }
            else if(category == "tram")
            {
                train = std::make_shared<TramTrainTrip>(statusId, origin, dest, distance, duration, lineName, op);
            }
            else if(category == "subway")
            {
                train = std::make_shared<UBahnTrainTrip>(statusId, origin, dest, distance, duration, lineName, op);
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
                    int stopId = stopNode.value("id", 0);
                    std::string stopName = stopNode.value("name", "Unknown");

                    if(stopId == originId)
                    {
                        isRecording = true;
                        continue;
                    }

                    if(stopId == destId)
                    {
                        break;
                    }

                    if(isRecording)
                    {
                        train->addStopover(Station(stopId, stopName));
                    }
                }
            }
            result.push_back(train);
        }
    }

    return result;
}