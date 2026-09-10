add_executable(sandbox main.cpp)

target_link_libraries(sandbox
    PRIVATE
        engine
)

target_compile_options(sandbox
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)