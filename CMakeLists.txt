cmake_minimum_required(VERSION 3.22)
project(sockets)

set(CMAKE_CXX_STANDARD 20)

add_executable(Server Server.cpp)
add_executable(Client Client.cpp)
