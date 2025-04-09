cmake_minimum_required(VERSION 3.16)
project(bipartite)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")

enable_testing()

add_executable(
  bipartite
  bipartite.cpp
  Graph.cpp
)
