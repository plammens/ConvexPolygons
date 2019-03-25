cmake_minimum_required(VERSION 3.0)

project(ConvexPolygons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -D NO_FREETYPE -O2")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -O0")

include_directories(include libs/include test/include)
link_directories(libs/lib)

set(PNGwriter_DIR libs/lib/cmake/PNGwriter)
find_package(PNGwriter)

file(GLOB Utils "src/*.cc")
list(FILTER Utils EXCLUDE REGEX main)
file(GLOB Classes "src/class/*.cc")
file(GLOB Tests "test/src/test*.cc")

add_executable(ConvexPolygons ${Utils} ${Classes} src/main.cc)
target_link_libraries(ConvexPolygons PNGwriter png)

add_executable(Test ${Tests} ${Utils} ${Classes})
target_link_libraries(Test PNGwriter png)
