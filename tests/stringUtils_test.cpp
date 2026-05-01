#include <cassert>

#include <iostream>

#include "stringUtils.h"

int main()
{
    std::string testString = "  Hello, World!  ";
    std::vector<std::string> expectedTokens = {"hello", "world"};
    assert(StringUtils::tokenize(testString) == expectedTokens);

    std::string testString2 = "This is a test.";
    std::string testSTRING2 = "THIS IS A TEST.";
    assert(StringUtils::tokenize(testString2) == StringUtils::tokenize(testSTRING2)); // Tokenization should be case-insensitive

    std::string testString3 = "This is a test string";
    std::string testString3WithPunctuation = "This, test string is a!";
    std::string textString3withspellingerror = "String Text this is a";
    assert(StringUtils::calculateSimilarity(StringUtils::tokenize(testString3), StringUtils::tokenize(testString3)) == 1.0); // Should be the same
    assert(StringUtils::calculateSimilarity(StringUtils::tokenize(testString3), StringUtils::tokenize(testString3WithPunctuation)) == 1.0); // Punctuation should not affect similarity
    std::cout << "Similarity: " << StringUtils::calculateSimilarity(StringUtils::tokenize(testString3), StringUtils::tokenize(textString3withspellingerror)) << std::endl;
    assert(StringUtils::calculateSimilarity(StringUtils::tokenize(testString3), StringUtils::tokenize(textString3withspellingerror)) > 0.6); // Should be quite similar, only one word is different and order should not matter
    assert(StringUtils::calculateSimilarity(StringUtils::tokenize(testString3), StringUtils::tokenize(testString)) == 0.0); // Should be very different

    return 0;
}