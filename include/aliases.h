// Some shared typedefs

#ifndef CONVEXPOLYGONS_ALIASES_H
#define CONVEXPOLYGONS_ALIASES_H


#include <boost/range/any_range.hpp>


template <typename T>
using Range = boost::any_range<const T, boost::bidirectional_traversal_tag>;


#endif //CONVEXPOLYGONS_ALIASES_H
