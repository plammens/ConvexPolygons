/**
 * @file
 * Interface and operations for convex polygons.
 */

#ifndef CONVEXPOLYGONS_CONVEXPOLYGONS_H
#define CONVEXPOLYGONS_CONVEXPOLYGONS_H

#include <vector>
#include "class/Point.h"
#include "class/RGBColor.h"
#include "class/Box.h"
#include "details/range.h"


//-------- TYPEDEFS --------//

typedef std::vector<Point> Points;




//-------- CONVEXPOLYGON CLASS --------//

/**
 * Interface for planar convex polygons. Can be constructed from a sequence of points.
 */
class ConvexPolygon {
public:
    ConvexPolygon() = default;

    /**
     * Constructs a convex polygon from a sequence of points. Calculates
     * and stores the convex hull of the points. This is the main constructor.
     *
     * @param points  points to take the convex hull of
     * @post `this->getVertices()` is the sequence of points corresponding
     * to the convex hull of `points`, starting with the one with lowest `x`
     * coordinate (and lowest `y` coordinate in case of equality), ordered clockwise.
     *
     * @complexity quasilinear in the size of `points`, \f$ O(n\log(n)) \f$
     */
    ConvexPolygon(const Points &points);
    ConvexPolygon(Points &&points);  ///< rvalue reference overload of ConvexPolygon(const Points &)

    /**
     * Implicit conversion from a Box.
     * @param box  the box to be interpreted as a convex polygon
     */
    ConvexPolygon(const Box &box);



    /**
     * Number of vertices in the polygon.
     * @return  the number of vertices in the polygon
     * @complexity constant
     */
    unsigned long vertexCount() const;

    /**
     * Indicates whether the polygon is a 0-gon (empty polygon).
     * @return whether the polygon is a empty
     * @complexity constant
     */
    bool empty() const { return vertices.empty(); }

    /**
     * Calculates the area of the polygon. If the polygon is empty, returns 0.
     * @return area of the polygon
     * @complexity linear in the number of vertices
     */
    double area() const;

    /**
     * Calculates the perimeter of the polygon. If the polygon is empty, returns 0.
     * @return perimeter of the polygon
     * @complexity linear in the number of vertices
     */
    double perimeter() const;

    /**
     * Calculates the centroid (equibarycenter) of the polygon.
     * @return centroid of the polygon
     * @complexity  linear in the number of vertices
     *
     * @pre the polygon is not empty
     *
     * @throws ValueError if the polygon is empty
     */
    Point centroid() const;


    /**
     * Calculates the bounding box of the polygon.
     * @return  bounding box of the polygon
     *
     * @pre  the polygon isn't empty (i.e., `not this->empty()`)
     *
     * @post every vertex is within the space delimited by the returned box.
     * That is, every vertex \f$ p \f$ of the polygon satisfies:
     * \f$  SW_x \leq p_x \leq NE_x  \ \land \  SW_y \leq p_y \leq NE_y \f$
     * where \f$ SW \f$ is \link #Box::SW() `B.SW()` \endlink and \f$ NE \f$ is
     * \link #Box::NE() `B.NE()` \endlink (`B` is the returned box).
     * Moreover, \f$ SW = (\min_{p\in P} p_x, \min_{p\in P} p_y) \f$ and
     * \f$ NE = (\max_{p\in P} p_x, \max_{p\in P} p_y) \f$ where \f$ P \f$ is the set of vertices.
     *
     * @complexity  linear in the number of vertices
     *
     * @throws ValueError if the polygon is empty.
     */
    Box boundingBox() const;


    //! @name Getters
    ///@{

    /**
     * Getter for the polygon's vertices. The vertices are laid out in
     * a cyclic manner, in that the first element is repeated at the end
     * to facilitate the use and implementation of algorithms involving,
     * for example, a loop in the edges of the polygon.
     *
     * @return a const-reference to the internal vertex vector.
     */
    const Points &getVertices() const { return vertices; }

    const RGBColor &getColor() const { return color; }

    ///@}

    /**
     * Sets the color of the polygon to the specified value.
     * @param col  new color
     */
    void setColor(const RGBColor &col) { color = col; }


private:
    Points vertices;
    RGBColor color;

    static
    Points ConvexHull(Points points);
};




//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//


//! @name Polygon operations
///@{

/**
 * Bounding box of a set of polygons.
 * @param polygons  any forward-traversal range of polygons
 * @return   the bounding box of the whole set of polygons.
 *
 * @pre  `polygons` contains at least one non-empty polygon
 * @post  every vertex of every polygon is within the returned box (see
 * the documentation for ConvexPolygon::boundingBox() for more details)
 *
 * @throws  ValueError if the total number of vetices is 0
 * @complexity: linear in the total number of vertices
 */
Box boundingBox(ConstRange<ConvexPolygon> polygons);

/**
 * Determines whether a point is inside a polygon.
 * @param P  point whose position (inside/outside) is to be determined
 * @param pol  the polygon under consideration
 * @return  whether `P` is inside `pol`
 *
 * @complexity  logarithmic in the number of vertices
 */
bool isInside(const Point &P, const ConvexPolygon &pol);

/**
 * Determines whether a polygon is inside another polygon.
 * @param pol1  polygon whose position (inside/outside) is to be determined
 * @param pol2  the polygon under consideration
 * @return  whether `pol1` is inside `pol2`
 *
 * @complexity  \f$ O(m\log(n)) \f$, where `m` and `n` are the number of
 * vertices in `pol1` and `pol2`, respectively
 */
bool isInside(const ConvexPolygon &pol1, const ConvexPolygon &pol2);


/**
 * Calculates the convex union of two polygons.
 * @return the convex union of the first and second argument
 *
 * @complexity quasilinear in the total number of vertices
 */
ConvexPolygon convexUnion(const ConvexPolygon &, const ConvexPolygon &);

//! Just syntactic sugar for convexUnion(const ConvexPolygon &, const ConvexPolygon &)
ConvexPolygon operator|(const ConvexPolygon &polA, const ConvexPolygon &polB);


/**
 * Calculates the intersection of two polygons.
 * @return the intersection of the first and second argument
 *
 * @complexity quasilinear in the total number of vertices
 */
ConvexPolygon intersection(const ConvexPolygon &, const ConvexPolygon &);

//! Just syntactic sugar for intersection(const ConvexPolygon &, const ConvexPolygon &)
ConvexPolygon operator&(const ConvexPolygon &, const ConvexPolygon &);

///@}



//! @name Equality operators
//! Vertex-wise equality of polygons.
///@{
bool operator==(const ConvexPolygon &lhs, const ConvexPolygon &rhs);
bool operator!=(const ConvexPolygon &lhs, const ConvexPolygon &rhs);
///@}


#endif //CONVEXPOLYGONS_CONVEXPOLYGONS_H
