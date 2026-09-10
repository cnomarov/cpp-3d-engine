add_executable(vec2-tests math/Vec2Tests.cpp)

target_link_libraries(vec2-tests
    PRIVATE
        engine
)

target_compile_options(vec2-tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)

add_test(NAME vec2-tests COMMAND vec2-tests)