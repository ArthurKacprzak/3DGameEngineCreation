cmake_minimum_required(VERSION 3.17)
project(3DGameEngineCreation)





cmake_minimum_required(VERSION 3.17)
project(DemoProject)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./Engine)

add_executable(DemoProject ./Demo/main.cpp)

target_link_libraries(DemoProject Engine)





