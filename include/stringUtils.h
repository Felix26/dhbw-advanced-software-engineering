#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
    std::vector<std::string> tokenize(const std::string &str);
    double calculateSimilarity(const std::vector<std::string> &tokens1, const std::vector<std::string> &tokens2);
}