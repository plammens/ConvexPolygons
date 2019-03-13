cmake_minimum_required(VERSION 3.0)

project(ConvexPolygons)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

include_directories(include)

file(GLOB SOURCE "src/*.cc")
add_executable(ConvexPolygons ${SOURCE})