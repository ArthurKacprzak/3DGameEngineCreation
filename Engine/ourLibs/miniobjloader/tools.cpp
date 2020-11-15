//
// Created by Black Moustache on 21/10/2020.
//

#include "tools.hpp"

std::vector<std::string> split(const std::string& str, char sep)
{
    std::vector<std::string> tokens_vector;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tokens;

    while(getline(ss, tokens, sep)) {
        tokens_vector.push_back(tokens);
    }

    return tokens_vector;
}
