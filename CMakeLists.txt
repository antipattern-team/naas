cmake_minimum_required(VERSION 3.13)
project(test_two_sockets)

set(CMAKE_CXX_STANDARD 14)

add_executable(client main.cpp src/Config.cpp include/Config.h src/ViModules.cpp include/ViModules.h cmake-build-debug/configFile.txt)
add_executable(auth auth.cpp)
add_executable(serv serv.cpp)