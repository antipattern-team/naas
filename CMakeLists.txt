cmake_minimum_required(VERSION 3.10)
project(test_two_sockets)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(scripts)

file(GLOB SRCS
        "src/*.cpp"
        )

file(GLOB HDRS
        "include/*.h"
        )


add_executable(client main.cpp ${SRCS} ${HDRS} )


add_executable(auth auth.cpp)

add_executable(serv serv.cpp)