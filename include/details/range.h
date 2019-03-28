// Shared typedefs for Boost.Range

#ifndef CONVEXPOLYGONS_ALIASES_H
#define CONVEXPOLYGONS_ALIASES_H


#include <boost/range/any_range.hpp>


template <typename T>
using ConstRange = boost::any_range<T, boost::forward_traversal_tag, const T &>;


#endif //CONVEXPOLYGONS_ALIASES_H
