add_library(engine STATIC)

target_sources(engine
    PRIVATE
        src/math/Vec2.cpp
        src/math/Vec3.cpp
        src/math/Vec4.cpp
        src/math/Mat3.cpp
        src/math/Mat4.cpp
        src/math/Quaternion.cpp
        src/renderer/SoftwareRenderer.cpp
)

target_include_directories(engine
    PUBLIC
        include
)

target_compile_options(engine
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)