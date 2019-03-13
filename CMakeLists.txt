cmake_minimum_required(VERSION 3.0)
project(ConvexPolygons)


include_directories(include)

file(GLOB SOURCE "src/*.cc")
add_executable(ConvexPolygons ${SOURCE})
