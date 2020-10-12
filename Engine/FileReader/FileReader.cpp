//
// Created by arthur on 10/10/2020.
//

#include "FileReader.hpp"

std::vector<char> FileReader::readFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error(std::string {"échec de l'ouverture du fichier "} + filename + "!");
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}
