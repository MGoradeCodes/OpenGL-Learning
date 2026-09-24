cmake_minimum_required(VERSION 4.3)

project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)

add_executable(OpenGL
        main.cpp

        glad/src/gl.c

        shaderClass.cpp
        VAO.cpp
        VBO.cpp
        EBO.cpp
        stb_image.cpp
        Texture.cpp
)

target_include_directories(OpenGL PRIVATE
        glad/include
)

target_include_directories(OpenGL PRIVATE
        glm-1.0.3/glm
)

target_include_directories(OpenGL PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(OpenGL PRIVATE
        glfw
        opengl32
)

# Copy shader files to the executable's directory
configure_file(
        ${CMAKE_SOURCE_DIR}/default.vert
        ${CMAKE_BINARY_DIR}/default.vert
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/default.frag
        ${CMAKE_BINARY_DIR}/default.frag
        COPYONLY
)

# Copy resources folder to the executable's directory
add_custom_command(TARGET OpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        ${CMAKE_BINARY_DIR}/textures
)