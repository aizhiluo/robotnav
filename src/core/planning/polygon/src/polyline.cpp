/* 
 * polyline.cpp
 * 
 * Created on: Aug 09, 2018 06:45
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "polygon/polyline.hpp"

using namespace librav;

void Polyline::AddPoint(double x, double y)
{
    points_.push_back(Point(x, y));
}

void Polyline::PrintInfo()
{
    std::cout << "Polyline with " << points_.size() << " points" << std::endl;
    for (auto &pt : points_)
        std::cout << "- (" << pt << ")" << std::endl;
}