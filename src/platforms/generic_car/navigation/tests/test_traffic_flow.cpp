#include <iostream>
#include <memory>

#include "navigation/map_analysis.hpp"
#include "road_network/road_map.hpp"
#include "navigation/traffic_flow.hpp"
#include "graph/algorithms/dijkstra_tr.hpp"

#include "lightviz/matrix_viz.hpp"
#include "lightviz/grid_viz.hpp"

#include "stopwatch/stopwatch.h"

using namespace librav;

int main()
{
    stopwatch::StopWatch timer;
    // std::shared_ptr<RoadMap> map = std::make_shared<RoadMap>("/home/rdu/Workspace/librav/data/road_map/intersection_single_lane_full_with_ref2.osm", 10);
    std::shared_ptr<RoadMap> map = std::make_shared<RoadMap>("/home/rdu/Workspace/librav/data/road_map/intersection_single_lane_full.osm", 10);
    std::cout << "loaded map in " << timer.toc() << " seconds" << std::endl;

    TrafficFlow tf;
    tf.SetRoadMap(map);

    // LightViz::ShowMatrixAsColorMap(map->GetFullDrivableAreaGrid()->GetGridMatrix(false), "driving", true);

    // std::vector<std::string> lanelets;
    // lanelets.push_back("s4");
    // lanelets.push_back("icm2");
    // lanelets.push_back("s1");
    // lanelets.push_back("im1");
    // lanelets.push_back("s3");
    // LightViz::ShowMatrixAsColorMap(map->GetLaneDrivableGrid(lanelets)->GetGridMatrix(false), "driving2", true);

    /////////////////////////////////////////////////////////////////////////////////

    // route planning
    auto lanelets = map->FindShortestRoute("s4", "s1");
    auto lanelets2 = map->FindShortestRoute("s4", "s3");
    Eigen::MatrixXd s4_matrix = map->GetLaneBoundGrid(lanelets)->GetGridMatrix(false) + map->GetLaneBoundGrid(lanelets2)->GetGridMatrix(false) + map->GetFullDrivableAreaGrid()->GetGridMatrix(false);
    LightViz::ShowMatrixAsColorMap(s4_matrix, "driving", true);

    // create square grid
    // auto matrix = map->GetFullLaneBoundaryGrid()->GetGridMatrix(false);
    // Eigen::MatrixXd matrix = map->GetFullLaneBoundaryGrid()->GetGridMatrix(false) + map->GetFullDrivableAreaGrid()->GetGridMatrix(false);
    // Eigen::MatrixXd matrix = map->GetLaneBoundGrid(lanelets)->GetGridMatrix(false) + map->GetFullDrivableAreaGrid()->GetGridMatrix(false);

    std::vector<std::string> test_lanelets;
    test_lanelets.push_back("s4");
    test_lanelets.push_back("icm2");
    test_lanelets.push_back("s1");
    test_lanelets.push_back("im1");
    test_lanelets.push_back("s3");
    Eigen::MatrixXd matrix = map->GetLaneDrivableGrid(test_lanelets)->GetGridMatrix(false);
    auto sgrid = std::make_shared<RoadSquareGrid>(matrix, 10);
    std::cout << "square grid size: " << sgrid->SizeX() << " , " << sgrid->SizeY() << std::endl;
    LightViz::ShowSquareGrid(sgrid.get(), 100, "Square Grid", true);

    timer.tic();
    // RoadSquareCell *tile_s = sgrid->GetCell(6, 0);
    RoadSquareCell *tile_s = sgrid->GetCell(51, 67);
    auto graph = DijkstraTraversal::IncSearch(tile_s, GetNeighbourFunc_t<RoadSquareCell *>(GetSquareGridNeighbour(sgrid)));
    std::cout << "traversal finished in " << timer.toc() << " seconds, vertex visited: " << graph.GetGraphVertexNumber() << std::endl;

    // LightViz::ShowSquareGridGraph(sgrid.get(), &graph, 100);

    // traffic flow analysis
    MapAnalysis::GenerateGraphCostMap(sgrid.get(), &graph);
    LightViz::ShowSquareGridGraphCost(sgrid.get(), &graph, 100, "distance", true);

    return 0;
}