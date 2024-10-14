cmake_minimum_required(VERSION 3.10)
project(bz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(RC STATIC
    src/RC/Vector.cpp
)

add_executable(bz src/main.cpp src/HTTP.cpp src/URL.cpp)
target_link_libraries(bz PRIVATE RC)
