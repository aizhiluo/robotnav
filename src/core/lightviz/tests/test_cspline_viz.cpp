#include <iostream>
#include <vector>
#include <cmath>

#include "geometry/cspline.hpp"

#include "lightviz/lightviz.hpp"
#include "lightviz/details/geometry_draw.hpp"
#include "lightviz/polygon_viz.hpp"
#include "geometry/polygon.hpp"

using namespace librav;

int main()
{
    std::vector<CSpline::Knot> knots;

    for (int i = 0; i < 10; i++)
        knots.emplace_back(i + 0.5 * std::sin(i), i + std::cos(i * i));

    CSpline spline(knots);

    LightViz::ShowCubicSpline(spline, 0.01, 10);

    return 0;
}