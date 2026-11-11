
cmake_minimum_required(VERSION 3.16)

project(PhysicsEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(PhysicsEngine
    src/main.cpp
)

target_include_directories(PhysicsEngine PRIVATE
    include
)

target_link_libraries(PhysicsEngine PRIVATE
    SDL2::SDL2
)

