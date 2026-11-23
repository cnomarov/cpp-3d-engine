#pragma once

#include <engine/math/Vec3.hpp>
#include <vector>
#include <cstdint>

struct Mesh
{
    std::vector<Vec3> vertices;
    std::vector<std::uint16_t> indexList;
};
