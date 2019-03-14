cmake_minimum_required(VERSION 3.0)

project(ConvexPolygons)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(include)

file(GLOB UTILS src/commands.cc src/handlers.cc src/utils.cc)
file(GLOB CLASSES src/class/Vector2D.cc src/class/Point.cc src/class/ConvexPolygon.cc)

add_executable(ConvexPolygons ${UTILS} ${CLASSES} src/main.cc)
