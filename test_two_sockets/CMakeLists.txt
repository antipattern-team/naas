cmake_minimum_required(VERSION 3.13)
project(test_two_sockets)

set(CMAKE_CXX_STANDARD 14)

add_executable(client main.cpp)
add_executable(auth auth.cpp)
add_executable(serv serv.cpp)