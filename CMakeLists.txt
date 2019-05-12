cmake_minimum_required(VERSION 3.13)
project(naas)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


include_directories(.)
add_subdirectory(Client)