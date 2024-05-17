cmake_minimum_required(VERSION 3.16)
project(RayLibTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES src/*.cpp)

file(GLOB HEADERS src/*.h)

add_executable(RayLibTemplate ${SOURCES} ${HEADERS})
# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib-4.1 ./libs/raylib)
target_link_libraries(RayLibTemplate PRIVATE raylib)
