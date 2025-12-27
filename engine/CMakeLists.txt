cmake_minimum_required(VERSION 3.15)

# Add GLFW subdirectory
add_subdirectory(vendor/glfw)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Create the SukiEngine library
add_library(SukiEngine STATIC)

# Add source files
target_sources(SukiEngine
  PRIVATE
    src/Suki/Core/Application.cpp
    vendor/glad/src/glad.c
)

# Public include directories (accessible to projects using SukiEngine)
target_include_directories(SukiEngine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Private include directories (only for building SukiEngine itself)
target_include_directories(SukiEngine
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)

# Link libraries
target_link_libraries(SukiEngine
  PUBLIC 
    glfw
    OpenGL::GL
)

# Require C++17
target_compile_features(SukiEngine PUBLIC cxx_std_17)

# Compiler-specific warnings
if (MSVC)
  target_compile_options(SukiEngine PRIVATE /W4)
else()
  target_compile_options(SukiEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()
