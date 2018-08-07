/* 
 * lattice_planner.cpp
 * 
 * Created on: Aug 07, 2018 09:37
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "state_lattice/lattice_planner.hpp"

#include <cmath>

using namespace librav;

int64_t LatticeNode::instance_count = 0;

Path_t<LatticeNode> LatticePlanner::Search(LatticeNode start_state, LatticeNode goal_state)
{
    using GraphVertexType = Vertex_t<LatticeNode, MotionPrimitive>;

    // create a new graph with only start and goal vertices
    Graph_t<LatticeNode, MotionPrimitive> graph;
    graph.AddVertex(start_state);
    graph.AddVertex(goal_state);

    GraphVertexType *start_vtx = graph.GetVertex(start_state);
    GraphVertexType *goal_vtx = graph.GetVertex(goal_state);

    // open list - a list of vertices that need to be checked out
    PriorityQueue<GraphVertexType *> openlist;

    // begin with start vertex
    openlist.put(start_vtx, 0);
    start_vtx->is_in_openlist_ = true;
    start_vtx->g_cost_ = 0;

    // start search iterations
    bool found_path = false;
    GraphVertexType *current_vertex;
    while (!openlist.empty() && found_path != true)
    {
        current_vertex = openlist.get();
        if (current_vertex->is_checked_)
            continue;

        if (CalculateDistance(current_vertex->state_, goal_vtx->state_) < threshold_)
        {
            found_path = true;
            break;
        }

        current_vertex->is_in_openlist_ = false;
        current_vertex->is_checked_ = true;

        // std::vector<std::tuple<LatticeNode>> neighbours;// = get_neighbours(current_vertex->state_);
        // for (auto &nb : neighbours)
        //     graph.AddEdge(current_vertex->state_, std::get<0>(nb), std::get<1>(nb));

        // check all adjacent vertices (successors of current vertex)
        for (auto &edge : current_vertex->edges_to_)
        {
            auto successor = edge.dst_;

            // check if the vertex has been checked (in closed list)
            if (successor->is_checked_ == false)
            {
                // first set the parent of the adjacent vertex to be the current vertex
                auto new_cost = current_vertex->g_cost_ + edge.cost_;

                // if the vertex is not in open list
                // or if the vertex is in open list but has a higher cost
                if (successor->is_in_openlist_ == false || new_cost < successor->g_cost_)
                {
                    successor->search_parent_ = current_vertex;
                    successor->g_cost_ = new_cost;

                    openlist.put(successor, successor->g_cost_);
                    successor->is_in_openlist_ = true;
                }
            }
        }
    }

    // reconstruct path from search
    Path_t<LatticeNode> path;
    if (found_path)
    {
        std::cout << "path found with cost " << goal_vtx->g_cost_ << std::endl;
        auto path_vtx = ReconstructPath(start_vtx, goal_vtx);
        for (const auto &wp : path_vtx)
            path.push_back(wp->state_);
    }
    else
        std::cout << "failed to find a path" << std::endl;

    return path;
};

double LatticePlanner::CalculateDistance(LatticeNode node0, LatticeNode node1)
{
    return std::hypot(node0.x - node1.x, node0.y - node1.y);
}

std::vector<Vertex_t<LatticeNode> *> LatticePlanner::ReconstructPath(Vertex_t<LatticeNode> *start_vtx, Vertex_t<LatticeNode> *goal_vtx)
{
    std::vector<Vertex_t<LatticeNode> *> path;
    Vertex_t<LatticeNode> *waypoint = goal_vtx;
    while (waypoint != start_vtx)
    {
        path.push_back(waypoint);
        waypoint = waypoint->search_parent_;
    }
    // add the start node
    path.push_back(waypoint);
    std::reverse(path.begin(), path.end());

#ifndef MINIMAL_PRINTOUT
    auto traj_s = path.begin();
    auto traj_e = path.end() - 1;
    std::cout << "starting vertex id: " << (*traj_s)->vertex_id_ << std::endl;
    std::cout << "finishing vertex id: " << (*traj_e)->vertex_id_ << std::endl;
    std::cout << "path length: " << path.size() << std::endl;
    std::cout << "total cost: " << path.back()->g_cost_ << std::endl;
#endif
    return path;
}