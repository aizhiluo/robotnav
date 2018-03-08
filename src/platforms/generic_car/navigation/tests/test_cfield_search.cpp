#include <iostream>
#include <memory>

#include "field/collision_field.hpp"
#include "field/traffic_participant.hpp"
#include "field/threat_distribution.hpp"
#include "navigation/field_search.hpp"

#include "fastplot/fastplot.hpp"
#include "fastplot/field_plot.hpp"
#include "stopwatch/stopwatch.h"

using namespace librav;

int main()
{
    const int32_t fsize_x = 30;
    const int32_t fsize_y = 30;

    std::shared_ptr<CollisionField> cfield = std::make_shared<CollisionField>(fsize_x, fsize_y);
    cfield->SetOriginCoordinate(0, 0);

    GaussianPositionVelocityThreat gau(15, 15, 1, 1);

    std::shared_ptr<TrafficParticipant> pt0 = std::make_shared<TrafficParticipant>(fsize_x, fsize_y);
    pt0->SetThreatDistribution(gau);

    cfield->AddTrafficParticipant(0, pt0);
    cfield->UpdateCollisionField();

    std::cout << "collision field created" << std::endl;

    std::cout << "threat matrix size: " << cfield->collision_threat_matrix_.rows() << " , " << cfield->collision_threat_matrix_.cols() << std::endl;

    FieldTile tile_s(0, 0, cfield);
    FieldTile tile_g(29, 29, cfield);
    auto path = Dijkstra::IncSearch(tile_s, tile_g, GetNeighbourFunc_t<FieldTile>(GetFieldTileNeighbour(cfield)));
    std::cout << "path length: " << path.size() << std::endl;

    FastPlot::ShowMatrixAsColorMap(cfield->collision_threat_matrix_);

    return 0;
}