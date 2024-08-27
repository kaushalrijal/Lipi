cmake_minimum_required(VERSION 3.10)
project(Lipi)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(lipi ${SOURCES})