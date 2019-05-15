cmake_minimum_required(VERSION 3.10)
project(naas)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)


add_executable(microServer microServer.cpp include/server/NetworkPool.h src/server/NetworkPool.cpp src/server/Router.cpp)
target_link_libraries(microServer pthread)
