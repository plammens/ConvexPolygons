cmake_minimum_required(VERSION 3.0)

project(ConvexPolygons)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -D NO_FREETYPE -O0")

include_directories(include libs/include test/include)
link_directories(libs/lib)

set(PNGwriter_DIR libs/lib/cmake/PNGwriter)
find_package(PNGwriter)

file(GLOB UTILS "src/*.cc")
list(FILTER UTILS EXCLUDE REGEX main)
file(GLOB CLASSES "src/class/*.cc")
file(GLOB TESTS "test/src/test_*.cc")

add_executable(ConvexPolygons ${UTILS} ${CLASSES} src/main.cc)
target_link_libraries(ConvexPolygons PNGwriter png)

add_executable(Test ${TESTS} ${UTILS} ${CLASSES})
target_link_libraries(Test PNGwriter png)
