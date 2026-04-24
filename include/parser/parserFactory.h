#pragma once

#include "memory"

#include "iparser.h"

class ParserFactory
{
    public:
        static std::unique_ptr<IParser> createParserFromFile(const std::string& filePath);
        static std::unique_ptr<IParser> createParserFromFolder(const std::string& folderPath);

        static std::unique_ptr<IParser> createMockParser();
};