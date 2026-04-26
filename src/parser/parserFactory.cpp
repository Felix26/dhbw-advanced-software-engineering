#include "parser/parserFactory.h"

#include "parser/tripparser.h"
#include "parser/faketripparser.h"
#include "parser/folderTripParser.h"

std::unique_ptr<IParser> ParserFactory::createParserFromFile(const std::string &filePath)
{
    return std::make_unique<TripParser>(filePath);
}

std::unique_ptr<IParser> ParserFactory::createParserFromFolder(const std::string &folderPath)
{
    return std::make_unique<FolderTripParser>(folderPath);
}

std::unique_ptr<IParser> ParserFactory::createMockParser()
{
    return std::make_unique<FakeTripParser>();
}
