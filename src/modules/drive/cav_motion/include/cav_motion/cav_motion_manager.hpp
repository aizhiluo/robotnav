/* 
 * cav_motion_manager.hpp
 * 
 * Created on: Dec 06, 2018 03:19
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef CAV_MOTION_MANAGER_HPP
#define CAV_MOTION_MANAGER_HPP

#include <memory>

#include "cav_motion/cav_datalink.hpp"
#include "cav_motion/vehicle_state.hpp"
#include "cav_motion/route_planner.hpp"
#include "traffic_map/map_loader.hpp"

namespace librav
{
class CAVMotionManager
{
  public:
    explicit CAVMotionManager(std::string map_file);

    bool IsReady();
    void Run();

  private:
    std::shared_ptr<LCMLink> data_link_;
    bool data_link_ready_ = false;

    MapLoader map_loader_;
    std::shared_ptr<RoadMap> road_map_;
    std::shared_ptr<TrafficMap> traffic_map_;

    std::shared_ptr<RoutePlanner> route_planner_;

    bool new_mission_request_received_ = false;
    bool abort_mission_request_received_ = false;
    bool new_veh_est_received_ = false;

    SimplePoint position_s_;
    SimplePoint position_g_;
    VehicleState ego_vehicle_state_;
    std::vector<VehicleState> surrounding_vehicles_;

    ReferenceRoute current_route_;

    void ResetTask();
    void HandleMissionInfoMsg(const librav::ReceiveBuffer *rbuf, const std::string &chan, const librav_lcm_msgs::CAVMissionInfo *msg);
    void HandleEgoVehicleStateMsg(const librav::ReceiveBuffer *rbuf, const std::string &chan, const librav_lcm_msgs::VehicleState *msg);
    void HandleVehicleEstimationsMsg(const librav::ReceiveBuffer *rbuf, const std::string &chan, const librav_lcm_msgs::VehicleEstimations *msg);
};
} // namespace librav

#endif /* CAV_MOTION_MANAGER_HPP */
