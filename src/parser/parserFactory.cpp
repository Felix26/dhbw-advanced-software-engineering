#include "parser/parserFactory.h"

#include "parser/tripparser.h"
#include "parser/faketripparser.h"
#include "parser/folderTripParser.h"

std::unique_ptr<IParser> ParserFactory::createParserFromFile(const std::string &filePath, const std::shared_ptr<StationRepository> &stationRepo)
{
    return std::make_unique<TripParser>(filePath, stationRepo);
}

std::unique_ptr<IParser> ParserFactory::createParserFromFolder(const std::string &folderPath, const std::shared_ptr<StationRepository> &stationRepo)
{
    return std::make_unique<FolderTripParser>(folderPath, stationRepo);
}

std::unique_ptr<IParser> ParserFactory::createMockParser()
{
    return std::make_unique<FakeTripParser>();
}
