cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(
    calculator
    VERSION 1.0
    LANGUAGES C CXX
)

include_directories(src)
add_library(ipc_socket_lib STATIC src/ipc_socket.cpp)

add_executable(calculator_server src/calculator_server.cpp)
add_executable(calculator_client src/calculator_client.cpp)

target_link_libraries(calculator_server ipc_socket_lib)
target_link_libraries(calculator_client ipc_socket_lib)

install(
    TARGETS calculator_client calculator_server
    DESTINATION /usr/local/bin
)

install(
    FILES calculatord.service
    DESTINATION /etc/systemd/system
)