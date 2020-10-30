//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_FILEREADER_HPP
#define INC_3DGAMEENGINECREATION_FILEREADER_HPP

#include <vector>
#include <string>
#include <fstream>

class FileReader
{
public:
    static std::vector<char> readFile(const std::string& filename);
};


#endif //INC_3DGAMEENGINECREATION_FILEREADER_HPP
