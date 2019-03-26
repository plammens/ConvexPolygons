cmake_minimum_required(VERSION 3.0)

project(ConvexPolygons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -D NO_FREETYPE -O2")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -O0")

include_directories(include libs/include test/include)
link_directories(libs/lib)

set(PNGwriter_DIR libs/lib/cmake/PNGwriter)
find_package(PNGwriter)

file(GLOB Source "src/*.cc" "src/class/*.cc" "src/details/*.cc")
list(FILTER Source EXCLUDE REGEX main)
file(GLOB Tests "test/src/test*.cc")

add_executable(ConvexPolygons ${Source} src/main.cc)
target_link_libraries(ConvexPolygons PNGwriter png)

add_executable(Test ${Tests} ${Source})
target_link_libraries(Test PNGwriter png)
