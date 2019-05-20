cmake_minimum_required(VERSION 3.13)
project(test_two_sockets)

set(CMAKE_CXX_STANDARD 14)

find_library(PTHREAD_LIBRARY pthread)

add_executable(client main.cpp src/Config.cpp include/Config.h src/ViModules.cpp include/ViModules.h
        cmake-build-debug/configFile.txt src/Authentification.cpp include/Authentification.h src/ThreadTun.cpp
        include/ThreadTun.h include/simpletun.h src/simpletun.cpp include/rwr.h src/rwr.cpp )
target_link_libraries(client ${PTHREAD_LIBRARY})

add_executable(auth auth.cpp)

add_executable(serv serv.cpp)