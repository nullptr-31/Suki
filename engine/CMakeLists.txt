cmake_minimum_required(VERSION 3.20)


# Add GLFW subdirectory
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Create the Suki library
add_library(Suki STATIC)

# Add source files
file(GLOB_RECURSE SUKI_ENGINE_SRC
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

target_sources(Suki
    PRIVATE
        ${SUKI_ENGINE_SRC}
        vendor/glad/src/glad.c
)

# Public include directories (accessible to projects using Suki)
target_include_directories(Suki
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Private include directories (only for building Suki itself)
target_include_directories(Suki
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)

# Link libraries
target_link_libraries(Suki
  PUBLIC 
    glfw
    OpenGL::GL
    spdlog::spdlog
)

# Require C++17
target_compile_features(Suki PUBLIC cxx_std_17)

# Compiler-specific warnings
if (MSVC)
  target_compile_options(Suki PRIVATE /W4)
else()
  target_compile_options(Suki PRIVATE -Wall -Wextra -Wpedantic)
endif()
