#include "debug.h"
#include <doctest.h>
#include <algorithm>
#include <random>
#include <cmath>

#include "class/ConvexPolygon.h"
#include "errors.h"



// Cache some repeatedly used polygons:
const ConvexPolygon
        emptyPol,
        vertex({{0, 0}}),
        line(Points{{0, 0}, {1, 1}}),
        line2(Points{{0, 0}, {0, 1}}),
        triangle({{0, 0}, {1, 0}, {0, 1}}),
        square({{0, 0}, {0, 1}, {1, 1}, {1, 0}}),
        square2({{0.5, 0.5}, {1.5, 1.5}, {1.5, 0.5}, {0.5, 1.5}}),
        rectangle1({{0, -1}, {0, 2}, {1, 2}, {1, -1}}),
        rectangle2({{-1, 0}, {-1, 1}, {2, 1}, {2, 0}}),
        smallSquare(Points{{0.5, 0.5}, {1, 0.5}, {0.5, 1}, {1, 1}}),
        squareUnion({{0, 0}, {0, 1}, {0.5, 1.5}, {1.5, 1.5}, {1.5, 0.5}, {1, 0}}),
        hexagon({{1, 2}, {2, 0}, {1, -2}, {-1, -2}, {-2, 0}, {-1, 2}});


TEST_SUITE("ConvexPolygon") {

    TEST_CASE("constructors") {
        CHECK(ConvexPolygon().getVertices() == Points());

        CHECK(ConvexPolygon({{0, 0}, {0, 0}, {0, 0}}).getVertices()
              == Points{{0, 0}, {0, 0}});

        CHECK(ConvexPolygon({{0, 0}, {0, 1}, {0, 2}}).getVertices()
              == Points{{0, 0}, {0, 2}, {0, 0}});

        CHECK(ConvexPolygon(Points{{0, 0}, {1, 0}, {0.5, 0.5}, {1, 1}, {0, 1}}).getVertices()
              == Points{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}});

        SUBCASE("first vertex") {
            CHECK(ConvexPolygon({{2, 0}, {1, 0}, {-1, 0}}).getVertices().front() == Point{-1, 0});
            CHECK(ConvexPolygon({{0, 2}, {0, 1}, {0, -1}}).getVertices().front() == Point{0, -1});
            CHECK(ConvexPolygon({{1, 2}, {0, 1}, {1, 0}}).getVertices().front() == Point{0, 1});
        }

        SUBCASE("octagon random shuffle") {
            Points points = {
                    {0, 1},
                    {0, 3},
                    {1, 4},
                    {1, 4},
                    {3, 4},
                    {4, 3},
                    {4, 1},
                    {1, 1},
                    {1, 1},
                    {1, 1},
                    {1, 3},
                    {3, 2},
                    {2, 2},
                    {3, 1}
            };

            std::mt19937 randGen(42);  // seed a generator for reproducible results
            std::shuffle(points.begin(), points.end(), randGen);

            CHECK(ConvexPolygon(points).getVertices()
                  == Points{{0, 1}, {0, 3}, {1, 4}, {3, 4}, {4, 3}, {4, 1}, {0, 1}});
        }

        SUBCASE("from Box") {
            Box box({0, 0}, {1, 1});
            ConvexPolygon pol = box;
            CHECK(pol.getVertices() == Points{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}});
        }
    }


    TEST_CASE("info members") {

        SUBCASE("vertexCount") {
            CHECK(emptyPol.vertexCount() == 0);
            CHECK(vertex.vertexCount() == 1);
            CHECK(line.vertexCount() == 2);
            CHECK(square.vertexCount() == 4);
            CHECK(hexagon.vertexCount() == 6);
        }
        SUBCASE("empty") {
            CHECK(emptyPol.empty());
            CHECK(not vertex.empty());
            CHECK(not square.empty());
        }
        SUBCASE("area") {
            REQUIRE(emptyPol.area() == 0);
            CHECK(vertex.area() == 0);
            CHECK(line.area() == 0);
            CHECK(square.area() == 1);
            CHECK(triangle.area() == 0.5);
            CHECK(hexagon.area() == 12);
        }
        SUBCASE("perimeter") {
            CHECK(emptyPol.perimeter() == 0);
            CHECK(vertex.perimeter() == 0);
            CHECK(line.perimeter() == std::sqrt(2));
            CHECK(square.perimeter() == 4);
        }
        SUBCASE("centroid") {
            CHECK_THROWS_AS(emptyPol.centroid(), ValueError);
            CHECK(vertex.centroid() == Point{0, 0});
            CHECK(line.centroid() == Point{0.5, 0.5});
            CHECK(hexagon.centroid() == Point{0, 0});
        }
        SUBCASE("bbox") {
            CHECK_THROWS_AS(emptyPol.boundingBox(), ValueError);
            CHECK(vertex.boundingBox() == Box({0, 0}, {0, 0}));
            CHECK(line.boundingBox() == Box({{0, 0}, {1, 1}}));
        }
    }
}


TEST_SUITE("Polygon operations") {

    TEST_CASE("isInside") {
        SUBCASE("single point") {
            CHECK(not isInside({0, 0}, emptyPol));
            CHECK(isInside({0, 0}, vertex));
            CHECK(not isInside({0, 0.1}, line));
            CHECK(isInside({0, 0.1}, square));
            CHECK(isInside({0, 0.1}, hexagon));

            CHECK(not isInside({-1, -1}, vertex));
            CHECK(not isInside({-1, -1}, line));
            CHECK(not isInside({-1, -1}, square));

            CHECK(not isInside({3, 0.5}, line));
            CHECK(not isInside({3, 0.5}, square));
            CHECK(not isInside({3, 0.5}, hexagon));
            CHECK(not isInside({3, 0.5}, triangle));
        }
        SUBCASE("polygons") {
            SUBCASE("trivial") {
                CHECK(isInside(emptyPol, emptyPol));
                CHECK(isInside(emptyPol, vertex));
                CHECK(isInside(vertex, vertex));
                CHECK(isInside(line, line));
                CHECK(isInside(square, square));
                CHECK(isInside(hexagon, hexagon));
            }

            CHECK(isInside(line, square));
            CHECK(not isInside(line, smallSquare));

            CHECK(isInside(smallSquare, square));
            CHECK(isInside(smallSquare, hexagon));
            CHECK(isInside(square, hexagon));
        }
    }


    TEST_CASE("union") {
        SUBCASE("trivial") {
            CHECK(convexUnion(emptyPol, emptyPol) == emptyPol);
            CHECK(convexUnion(emptyPol, line) == line);
            CHECK(convexUnion(emptyPol, square) == square);
        }

        CHECK(convexUnion(square, square2) == squareUnion);
    }


    TEST_CASE("intersection") {
        SUBCASE("trivial") {
            CHECK(intersection(emptyPol, emptyPol) == emptyPol);
            CHECK(intersection(emptyPol, line) == emptyPol);
            CHECK(intersection(emptyPol, square) == emptyPol);
        }
        SUBCASE("small") {
            CHECK(intersection(square, square2) == smallSquare);
            CHECK(intersection(square, hexagon) == square);
            CHECK(intersection(line, square) == line);
            CHECK(intersection(rectangle1, rectangle2) == square);
        }
        SUBCASE("rotated") {
            const double s = std::sqrt(2)/2;
            const ConvexPolygon
                a({{0, 1}, {-1, 0}, {0, -1}, {1, 0}}),
                b({{s, s}, {-s, s}, {-s, -s}, {s, -s}});

            CHECK(intersection(a, b).vertexCount() == 8);
        }
    }

}
