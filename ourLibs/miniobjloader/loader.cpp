//
// Created by Black Moustache on 21/10/2020.
//

#include "loader.hpp"


bool miniobj::loader::load(attrib_t *attrib, std::vector<miniobj::shape_t> *shape, std::string path)
{
    std::string line;
    std::ifstream myfile(path);
    _attrib = attrib;
    _shapes = shape;

    if (myfile) {
        while (getline( myfile, line )) {
            hadleLine(line);
        }
        _shapes->emplace_back(currentShape);
        myfile.close();
    }
    else {
        std::cerr << "couldn't open : " << path << std::endl;
    }
    return true;
}

void miniobj::loader::hadleLine(std::string line)
{
    std::vector<std::string> tokens;
    int indice;

    if (line[0] == '#') {
        return;
    }
    tokens = split(line, ' ');
    if (line[0] == 'o' && tokens.size() == 2) {
        std::cout << "object: " << tokens[1] << std::endl;
        currentShape.name = std::string(tokens[1]);
    } else if (tokens[0] == "v" && tokens.size() == 4) {
        _attrib->vertices.emplace_back(std::stof(tokens[1]));
        _attrib->vertices.emplace_back(std::stof(tokens[2]));
        _attrib->vertices.emplace_back(std::stof(tokens[3]));
    } else if (tokens[0] == "vt" && tokens.size() == 3) {
        _attrib->texcoords.emplace_back(std::stof(tokens[1]));
        _attrib->texcoords.emplace_back(std::stof(tokens[2]));
    } else if (tokens[0] == "vn" && tokens.size() == 4) {
        _attrib->normal.emplace_back(std::stof(tokens[1]));
        _attrib->normal.emplace_back(std::stof(tokens[2]));
        _attrib->normal.emplace_back(std::stof(tokens[3]));
    } else if (tokens[0] == "f" && tokens.size() == 4) {
        fillIndex(tokens[1]);
        fillIndex(tokens[2]);
        fillIndex(tokens[3]);
    } else if (tokens[0] == "f" && tokens.size() == 5) {
        fillIndex(tokens[1]);
        fillIndex(tokens[2]);
        fillIndex(tokens[3]);
        fillIndex(tokens[1]);
        fillIndex(tokens[3]);
        fillIndex(tokens[4]);
    }
}

void miniobj::loader::fillIndex(std::string token) {
    std::vector<std::string> tokens = split(token, '/');
    index_t index;

    index.vertex_index = std::stoi(tokens[0]) - 1;
    index.texcoord_index = std::stoi(tokens[1]) - 1;
    index.normal_index = std::stoi(tokens[2]) - 1;
    currentShape.mesh.indices.emplace_back(index);
}
