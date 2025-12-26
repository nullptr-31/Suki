add_subdirectory(vendor/glfw)

add_library(SukiEngine STATIC)

target_sources(SukiEngine
  PRIVATE
    src/engine.cpp
)

target_include_directories(SukiEngine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SukiEngine
  PUBLIC glfw
)

target_compile_features(SukiEngine PUBLIC cxx_std_17)

if (MSVC)
  target_compile_options(SukiEngine PRIVATE /W4)
else()
  target_compile_options(SukiEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()

