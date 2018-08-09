/* 
 * polygon.cpp
 * 
 * Created on: Aug 09, 2018 04:16
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "polygon/polygon.hpp"

#include <iterator>
#include <cassert>
#include <cmath>

#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/partition_2.h>
#include <CGAL/Boolean_set_operations_2.h>

using namespace librav;

Polygon::Polygon(std::vector<Point_2> pts)
{
    for (auto &pt : pts)
        data_.push_back(pt);
}

Polygon::Polygon(Polyline left_bound, Polyline right_bound)
{
    // add points from the right bound first
    for (auto &pt : right_bound.GetPoints())
        data_.push_back(pt);
    // add points from the left bound in the reversed order
    auto pts = left_bound.GetPoints();
    for (auto it = pts.rbegin(); it < pts.rend(); ++it)
        data_.push_back(*it);
}

bool Polygon::Intersect(const Polygon &other)
{
    return CGAL::do_intersect(data_, other.data_);
}

Polygon Polygon::Transform(double dx, double dy, double dtheta)
{
    Polygon new_polygon;
    for (auto it = data_.vertices_begin(); it != data_.vertices_end(); ++it)
    {
    //     double x = (*it).x() * std::cos(dtheta) - (*it).y() * std::sin(dtheta) + dx;
    //     double y = (*it).x() * std::sin(dtheta) + (*it).y() * std::cos(dtheta) + dy;
    //     new_polygon.AddPoint(x, y);
    std::cout << (*it).x();
    }
    return new_polygon;
}

void Polygon::PrintInfo()
{
    std::cout << "Polygon with " << data_.size() << " points" << std::endl;
    for (auto it = data_.vertices_begin(); it != data_.vertices_end(); ++it)
        std::cout << "- (" << *it << ")" << std::endl;
}

void Polygon::AddPoint(double x, double y)
{
    data_.push_back(Point(x, y));
}

void Polygon::AddPoint(Point pt)
{
    data_.push_back(pt);
}

bool Polygon::CheckInside(Point pt)
{
    if (CGAL::bounded_side_2(data_.vertices_begin(), data_.vertices_end(), pt, K()) == CGAL::ON_BOUNDED_SIDE)
        return true;
    return false;
}

int32_t Polygon::CheckRelativePosition(Point pt)
{
    switch (CGAL::bounded_side_2(data_.vertices_begin(), data_.vertices_end(), pt, K()))
    {
    case CGAL::ON_BOUNDED_SIDE:
        return 1;
    case CGAL::ON_BOUNDARY:
        return 0;
    case CGAL::ON_UNBOUNDED_SIDE:
        return -1;
    }
}

void Polygon::ConvexDecomposition()
{
    convex_partitions_.clear();

    if (data_.is_convex())
        convex_partitions_.push_back(Polygon(data_));

    CGAL::optimal_convex_partition_2(data_.vertices_begin(),
                                     data_.vertices_end(),
                                     std::back_inserter(partitions_),
                                     partition_traits_);

    assert(CGAL::partition_is_valid_2(data_.vertices_begin(),
                                      data_.vertices_end(),
                                      partitions_.begin(),
                                      partitions_.end(),
                                      validity_traits_));

    for (auto it = partitions_.begin(); it != partitions_.end(); ++it)
        convex_partitions_.push_back(Polygon(*it));
}