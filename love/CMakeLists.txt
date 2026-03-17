add_executable(Love)

target_sources(Love
    PRIVATE
        src/main.cpp
)

target_link_libraries(Love
    PRIVATE
        Suki
)
