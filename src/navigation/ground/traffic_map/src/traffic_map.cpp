/* 
 * traffic_map.cpp
 * 
 * Created on: Oct 18, 2018 08:37
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "traffic_map/traffic_map.hpp"

using namespace librav;

TrafficMap::TrafficMap(std::shared_ptr<RoadMap> map) : road_map_(map)
{
    IdentifyTrafficElements();
}

void TrafficMap::IdentifyTrafficElements()
{
    // look for traffic channels
    for (auto &source : road_map_->GetSources())
    {
        for (auto &sink : road_map_->GetSinks())
        {
            auto path = road_map_->FindShortestRouteName(source, sink);
            if (!path.empty())
            {
                traffic_channels_.insert(std::make_pair(std::make_pair(source, sink), std::make_shared<TrafficChannel>(road_map_, source, sink, path)));
            }
        }
    }
    for (auto &lane : road_map_->GetIsolatedLanes())
    {
        traffic_channels_.insert(std::make_pair(std::make_pair(lane, lane), std::make_shared<TrafficChannel>(road_map_, lane)));
    }
    // std::cout << "traffic channel num: " << traffic_channels_.size() << std::endl;
}

std::vector<std::shared_ptr<TrafficChannel>> TrafficMap::GetAllTrafficChannels()
{
    std::vector<std::shared_ptr<TrafficChannel>> chns;
    for (auto &tchn : traffic_channels_)
        chns.push_back(tchn.second);
    return chns;
}

std::vector<std::shared_ptr<TrafficChannel>> TrafficMap::FindTrafficChannels(SimplePoint pos)
{
    std::vector<std::shared_ptr<TrafficChannel>> chns;
    for (auto &tchn : traffic_channels_)
    {
        if (tchn.second->CheckInside(pos))
            chns.push_back(tchn.second);
    }
    return chns;
}