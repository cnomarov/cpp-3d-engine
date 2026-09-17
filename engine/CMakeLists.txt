add_library(engine STATIC)

target_sources(engine
    PRIVATE
        src/math/Vec2.cpp
        src/math/Vec3.cpp
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