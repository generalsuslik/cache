set(TARGET lru_cache)

set(SOURCES
        lru_cache.cpp
)

add_library(lru_cache
        ${SOURCES}
)

target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)