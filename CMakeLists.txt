cmake_minimum_required(VERSION 3.0)

project(ConvexPolygons)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -D NO_FREETYPE -O0")

include_directories(include libs/include test/include)
link_directories(libs/lib)

set(PNGwriter_DIR libs/lib/cmake/PNGwriter)
find_package(PNGwriter)

file(GLOB UTILS "src/*.cc")
file(GLOB CLASSES "src/class/*.cc")

add_executable(ConvexPolygons ${UTILS} ${CLASSES} src/main.cc)
target_link_libraries(ConvexPolygons PNGwriter png)
