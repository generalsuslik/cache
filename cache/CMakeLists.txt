set(TARGET cache)

set(SOURCES
        cache.cpp
        shard.cpp
)

add_library(cache
        ${SOURCES}
)

add_subdirectory(lru_cache)

target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${TARGET}
    PRIVATE
        lru_cache
)