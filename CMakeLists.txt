cmake_minimum_required(VERSION 3.28)
project(cache_bin)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(cache)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        cache
)