#include <engine/mesh/MeshLoader.hpp>

#include <fstream>
#include <stdexcept>

Mesh MeshLoader::loadFromFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::runtime_error{"Failed to open mesh file: " + filePath};
    }
    return Mesh{};
}
