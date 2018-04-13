/* 
 * traffic_flow_map.cpp
 * 
 * Created on: Apr 10, 2018 17:35
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "navigation/traffic_flow_map.hpp"
#include "navigation/road_grid_traversal.hpp"

using namespace librav;

void TrafficFlowMap::BuildRoadGrid(int32_t size_per_side)
{
    assert(road_map_.get() != nullptr);

    Eigen::MatrixXd matrix = road_map_->GetFullDrivableAreaGrid()->GetGridMatrix(false);
    road_grid_ = std::make_shared<RoadSquareGrid>(matrix, 10);
    std::cout << "square grid size: " << road_grid_->SizeX() << " , " << road_grid_->SizeY() << std::endl;
}

void TrafficFlowMap::AddTrafficFlowSource(std::string source)
{
    flow_sources_.push_back(source);
}

void TrafficFlowMap::AddTrafficFlowSink(std::string sink)
{
    flow_sinks_.push_back(sink);
}

void TrafficFlowMap::IdentifyTrafficFlow()
{
    traffic_channels_.clear();

    for (const auto &src : flow_sources_)
    {
        std::set<std::string> dsts;
        for (const auto &dst : flow_sinks_)
        {
            auto path = road_map_->FindShortestRouteName(src, dst);
            if (!path.empty())
            {
                for (auto &wp : path)
                    dsts.insert(wp);
                // std::cout << "connected: " << src << " , " << dst << std::endl;
            }
        }
        if (!dsts.empty())
        {
            traffic_channels_.insert(std::make_pair(src, dsts));

            std::vector<std::string> drivable;
            for (auto &lanelet : dsts)
                drivable.push_back(lanelet);
            channel_grids_[src] = road_map_->GetLaneDrivableGrid(drivable);
        }
    }
    std::cout << "total traffic channels:" << traffic_channels_.size() << std::endl;
}

std::vector<std::string> TrafficFlowMap::GetTrafficChannelSources() const
{
    std::vector<std::string> channel_sources;
    for (auto &src : traffic_channels_)
        channel_sources.push_back(src.first);
    return channel_sources;
}

Eigen::MatrixXd TrafficFlowMap::GetTrafficChannelMatrix(std::string source)
{
    return channel_grids_[source]->GetGridMatrix(false);
}

void TrafficFlowMap::GenerateTrafficFlowMap()
{
    for (auto &grid_entry : channel_grids_)
    {
        auto grid = grid_entry.second;
    }
}

void TrafficFlowMap::TraverseTrafficChannel(std::string channel)
{
    RoadSquareCell *tile_s = road_grid_->GetCell(51, 67);
    RoadGridTraversal::Traverse(channel, tile_s, road_grid_.get(), GetNeighbourFunc_t<RoadSquareCell *>(GetRoadSquareGridNeighbour(road_grid_, channel_grids_[channel])));
}