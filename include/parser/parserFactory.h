#pragma once

#include "memory"
#include "stationRepository.h"
#include "iparser.h"

class ParserFactory
{
    public:
        static std::unique_ptr<IParser> createParserFromFile(const std::string& filePath, const std::shared_ptr<StationRepository>& stationRepo);
        static std::unique_ptr<IParser> createParserFromFolder(const std::string& folderPath, const std::shared_ptr<StationRepository>& stationRepo);

        static std::unique_ptr<IParser> createMockParser();
};