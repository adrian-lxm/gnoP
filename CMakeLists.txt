cmake_minimum_required(VERSION 3.28.3)
project(gnoP)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

include_directories(header)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(gnoP ${SOURCES})
target_link_libraries(gnoP SDL2)
