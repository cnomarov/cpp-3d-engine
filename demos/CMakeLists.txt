find_package(SDL2 REQUIRED)

function(add_engine_demo target source)
    add_executable(${target} ${source})

    target_link_libraries(${target}
        PRIVATE
            engine
            SDL2::SDL2
    )

    target_compile_options(${target}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
    )
endfunction()

add_engine_demo(triangle-demo triangle_demo.cpp)
add_engine_demo(quaternion-demo quaternion_demo.cpp)
add_engine_demo(wireframe-cube-demo wireframe_cube_demo.cpp)
