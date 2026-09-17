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

add_executable(software-renderer-tests renderer/SoftwareRendererTests.cpp)

target_link_libraries(software-renderer-tests
    PRIVATE
        engine
)

target_compile_options(software-renderer-tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)

add_test(NAME software-renderer-tests COMMAND software-renderer-tests)

add_executable(vec3-tests math/Vec3Tests.cpp)

target_link_libraries(vec3-tests
    PRIVATE
        engine
)

target_compile_options(vec3-tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)

add_test(NAME vec3-tests COMMAND vec3-tests)