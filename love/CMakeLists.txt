add_executable(SukiGame)

target_sources(SukiGame
  PRIVATE
    src/main.cpp
)

target_link_libraries(SukiGame
  PRIVATE
    SukiEngine
)
