cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

project(learningzmq VERSION 1.0.0)

add_executable(${PROJECT_NAME} main.cpp)

find_package(cppzmq)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} cppzmq)

