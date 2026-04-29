#include "stringUtils.h"

#include <sstream>
#include <algorithm>

namespace StringUtils
{
    std::vector<std::string> tokenize(const std::string &name)
    {
        std::vector<std::string> tokens;
        
        std::string processedName = name;
        
        // replace punctuation with spaces
        std::replace_if(processedName.begin(), processedName.end(), [](unsigned char c) { return std::ispunct(c); }, ' ');

        // tokenize by whitespace
        std::istringstream iss(processedName);
        std::string token;
        while (iss >> token)
        {
            // convert to lowercase
            std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){ return std::tolower(c); });
            
            tokens.push_back(token);
        }

        // sort alphabetically
        std::sort(tokens.begin(), tokens.end());

        return tokens;
    }

    // Use the Jaccard similarity coefficient based on the tokens of the station names to determine how similar two station names are
    // tokens1 and tokens2 should be preprocessed with tokenizeStationName, must be sorted alphabetically
    double calculateSimilarity(const std::vector<std::string> &tokens1, const std::vector<std::string> &tokens2)
    {
        if(tokens1.empty() && tokens2.empty()) return 1;

        size_t matches = 0;
        size_t totalNoMatchTokenLength = 0;
        
        size_t i = 0, j = 0;
        while(i < tokens1.size() && j < tokens2.size())
        {
            if(tokens1[i] == tokens2[j])
            {
                matches += tokens1[i].length(); // weight longer tokens higher
                i++;
                j++;
            }
            else if(tokens1[i] < tokens2[j])
            {
                totalNoMatchTokenLength += tokens1[i].length();
                i++;
            }
            else
            {
                totalNoMatchTokenLength += tokens2[j].length();
                j++;
            }
        }

        while(i < tokens1.size())
        {
            totalNoMatchTokenLength += tokens1[i].length();
            i++;
        }

        // 3. Den "Rest" von tokens2 aufaddieren (falls tokens1 früher zu Ende war)
        while(j < tokens2.size())
        {
            totalNoMatchTokenLength += tokens2[j].length();
            j++;
        }

        // jaccard similarity coefficient
        return static_cast<double>(matches) / (totalNoMatchTokenLength + matches);
    }
}