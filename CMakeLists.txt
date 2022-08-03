cmake_minimum_required(VERSION 3.23)
project(cpp_sort_algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_sort_algorithms
        SortAlgorithms/Private/SortAlgorithms.cpp SortAlgorithms/Private/Tools.cpp SortAlgorithms/Public/Tools.h SortAlgorithms/Public/SortAlgorithms.h)
