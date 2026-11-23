#include <engine/mesh/MeshLoader.hpp>

#include <cassert>
#include <stdexcept>

void testMissingFileThrows()
{
    bool errorThrown = false;

    try
    {
        MeshLoader::loadFromFile("missing-mesh-file-for-test.mesh");
    }
    catch (const std::runtime_error &)
    {
        errorThrown = true;
    }

    assert(errorThrown);
}

int main()
{
    testMissingFileThrows();
    return 0;
}
