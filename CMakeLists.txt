cmake_minimum_required(VERSION 3.24)
project(Alg_Graph_Bin)

set(CMAKE_CXX_STANDARD 20)

add_executable(Alg_Graph_Bin main.cpp Graph.cpp Graph.h Node.cpp Node.h GraphFileReader.cpp GraphFileReader.h)
