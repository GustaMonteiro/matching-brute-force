cmake_minimum_required(VERSION 3.10)

project(Brute_Force_Matching)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB source_files ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(matching ${source_files})

target_include_directories(matching PUBLIC ${CMAKE_SOURCE_DIR}/include)

file(COPY ${CMAKE_SOURCE_DIR}/inputs/ DESTINATION ${CMAKE_BINARY_DIR})
