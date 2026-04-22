#include "parserFactory.h"

#include "tripparser.h"
#include "faketripparser.h"

std::unique_ptr<IParser> ParserFactory::createParserFromFile(const std::string &filePath)
{
    return std::make_unique<TripParser>(filePath);
}

std::unique_ptr<IParser> ParserFactory::createMockParser()
{
    return std::make_unique<FakeTripParser>();
}
