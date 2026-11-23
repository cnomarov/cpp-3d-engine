#pragma once

#include <engine/mesh/Mesh.hpp>
#include <string>

class MeshLoader
{
public:
    static Mesh loadFromFile(const std::string &filePath);
};
