cmake_minimum_required(VERSION 3.14)
project(DragForceRealistic)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)

add_executable(drag main.cpp)
target_link_libraries(drag PRIVATE nlohmann_json::nlohmann_json)
