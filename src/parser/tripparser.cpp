#include "parser/tripparser.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <regex>
#include <memory>

#include "trips/traintrip.h"
#include "trips/bustrip.h"
#include "json.hpp"
#include "stringUtils.h"
#include "valueObjects/allValueObjectHeaders.h"

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
        std::string startTimeStr = (!userJourneyNode["origin"]["departureReal"].is_null()) ? userJourneyNode["origin"].value("departureReal", "") : userJourneyNode["origin"].value("departurePlanned", "");
        std::cout << "Parsing trip with start time: " << startTimeStr << std::endl;
        std::chrono::system_clock::time_point startTime = parseTime(startTimeStr);
        std::string originName = userJourneyNode["origin"].value("name", "Unknown");
        Station origin = parseStationNode(userJourneyNode["origin"]);

        // extract destination
        std::string destName = userJourneyNode["destination"].value("name", "Unknown");
        Station dest = parseStationNode(userJourneyNode["destination"]);
        
        Operator op(0, "Unknown");
        if (userJourneyNode.contains("operator") && userJourneyNode["operator"].is_object())
        {
            op = Operator(userJourneyNode["operator"].value("id", 0), userJourneyNode["operator"].value("name", "Unknown"));
        }

        // 4. Trip-Objekt erzeugen (Factory)
        auto trip = createTrip(statusId, origin, dest, distance, duration, startTime, category, lineName, op);
        if (!trip)
        {
            continue;
        }

        // extract stopovers from global trip node
        if(item.contains("trip") && item["trip"].contains("stopovers") && item["trip"]["stopovers"].is_array())
        {
            bool isRecording = false;
            
            // Wir müssen casten, da Stopovers aktuell anscheinend nur bei TrainTrip unterstützt werden
            auto trainTrip = std::dynamic_pointer_cast<TrainTrip>(*trip);
            
            if(trainTrip) 
            {
                for(const auto &stopNode : item["trip"]["stopovers"])
                {
                    std::string stopName = stopNode.value("name", "Unknown");

                    if(stopName == originName)
                    {
                        isRecording = true;
                        continue;
                    }
                    if(stopName == destName)
                    {
                        break;
                    }

                    if(isRecording)
                    {
                        Station stopoverStation = parseStationNode(stopNode);
                        trainTrip->addStopover(stopoverStation);
                    }
                }
            }
        }

        result.push_back(*trip);
    }

    return result;
}

std::optional<std::string> TripParser::extractDHIDFromIdentifiers(const json &identifiersNode) const
{
    for(const auto &idNode : identifiersNode)
    {
        if(idNode.value("type", "") == "ifopt")
        {
            std::string id = idNode.value("identifier", "Unknown");
            id.erase(id.find_last_not_of(" \n\r\t") + 1);
            return id;
        }
    }

    // If no identifier with type "ifopt" is found, try to extract any identifier that matches the DHID pattern (e.g., "de:08215:1221")
    static const std::regex dhidRegex(R"(de:\d{5}:\d{1,6})");
    std::smatch match;

    for(const auto &idNode : identifiersNode)
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

    return std::nullopt;
}

std::optional<std::string> TripParser::extractDHIDFromName(const std::string &name) const
{
    for(const auto &[dhid, data] : mStationRepo->mZHVData)
    {
        if(data.formattedName == name)
        {
            return dhid;
        }
    }

    // If no exact match is found, try to find the station with the highest similarity based on the station name
    double highestSimilarity = 0.0;
    std::string bestMatchDhid;

    std::vector<std::string> nameTokens = StringUtils::tokenize(name);

    for(const auto &[dhid, data] : mStationRepo->mZHVData)
    {
        double similarity = StringUtils::calculateSimilarity(nameTokens, data.nameTokens);
        if(similarity > highestSimilarity)
        {
            highestSimilarity = similarity;
            bestMatchDhid = dhid;
        }
        if(highestSimilarity > 0.8)
        {
            return bestMatchDhid;
        }
    }

    if(!bestMatchDhid.empty() && highestSimilarity > 0.7)
    {
        return bestMatchDhid;
    }

    return std::nullopt;
}

std::optional<std::string> TripParser::extractDHID(const json &destinationNode, const std::string &name) const
{
    static std::unordered_map<std::string, std::string> cache;
    if(cache.contains(name))
    {
        return cache[name];
    }

    if(destinationNode.contains("identifiers"))
    {
        auto result = extractDHIDFromIdentifiers(destinationNode["identifiers"]);
        if(result)
        {
            cache[name] = *result;
            return *result;
        }
    }

    auto result = extractDHIDFromName(name);
    if(result)
    {
        cache[name] = *result;
        return *result;
    }
    return std::nullopt;
}

Station TripParser::parseStationNode(const json &stationNode) const
{
    std::string name = stationNode.value("name", "Unknown");
    std::optional<std::string> dhid = extractDHID(stationNode, name);

    if(dhid && mStationRepo->findStation(*dhid))
    {
        auto stationOpt = mStationRepo->findStation(*dhid);
        return **stationOpt;
    }
    
    //std::cerr << "Warning: Could not extract DHID for station. Using station name from trip data: " << name << '\n';
    return Station(name);
}

std::chrono::system_clock::time_point TripParser::parseTime(const std::string &timeStr) const
{
    if(timeStr.empty())
    {
        return std::chrono::system_clock::time_point();
    }

    std::istringstream ss(timeStr);
    std::chrono::system_clock::time_point tp;
    ss >> std::chrono::parse("%Y-%m-%dT%H:%M:%S", tp);
    return tp;
}

std::optional<std::shared_ptr<Trip>> TripParser::createTrip(int statusId, const Station &origin, const Station &dest, int distance, int duration, const std::chrono::system_clock::time_point &startTime, const std::string &category, const std::string &lineName, const Operator &op) const
{
    if(category == "bus")
    {
        return std::make_shared<BusTrip>(statusId, origin, dest, distance, duration, startTime, lineName);
    }
    else
    {
        TransportType type = TransportType::Unknown;
        if(category == "express" || category == "regionalExp" || (category == "nationalExpress" && lineName.find("IC") != std::string::npos)) // "regionalExp" is used for FlixTrains, "nationalExpress" is used for ICEs
        {
            type = TransportType::Fernverkehr;
        }
        else if(category == "regional" || category == "nationalExpress") // "nationalExpress" is used for french regional trains
        {
            type = TransportType::Regionalverkehr;
        }
        else if(category == "suburban")
        {
            type = TransportType::SBahn;
        }
        else if(category == "tram")
        {
            type = TransportType::Tram;
        }
        else if(category == "subway")
        {
            type = TransportType::UBahn;
        }
        else
        {
            std::cerr << "Unknown category: " << category << '\n';
            return std::nullopt;
        }

        return std::make_shared<TrainTrip>(statusId, origin, dest, distance, duration, startTime, type, lineName, op);
    }
}