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

add_executable(vec4-tests math/Vec4Tests.cpp)

target_link_libraries(vec4-tests
    PRIVATE
        engine
)

target_compile_options(vec4-tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)

add_test(NAME vec4-tests COMMAND vec4-tests)

add_executable(mat3-tests math/Mat3Tests.cpp)

target_link_libraries(mat3-tests
    PRIVATE
        engine
)

target_compile_options(mat3-tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)

add_test(NAME mat3-tests COMMAND mat3-tests)

add_executable(mat4-tests math/Mat4Tests.cpp)

target_link_libraries(mat4-tests
    PRIVATE
        engine
)

target_compile_options(mat4-tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)

add_test(NAME mat4-tests COMMAND mat4-tests)

add_executable(quaternion-tests math/QuaternionTests.cpp)

target_link_libraries(quaternion-tests
    PRIVATE
        engine
)

target_compile_options(quaternion-tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
)

add_test(NAME quaternion-tests COMMAND quaternion-tests)