find_package(SDL2 REQUIRED)

add_executable(sandbox main.cpp)

target_link_libraries(sandbox
    PRIVATE
        engine
        SDL2::SDL2
)

target_compile_options(sandbox
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)