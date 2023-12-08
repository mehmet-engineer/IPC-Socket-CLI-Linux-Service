cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

project(
    uds_lectures
    VERSION 1.0
    LANGUAGES C CXX
)

add_executable(server server.cpp)
add_executable(client client.cpp)