/* 
 * quad_flattraj_handler.hpp
 * 
 * Created on: Oct 28, 2016
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef QUAD_FLATTRAJ_HANDLER_HPP
#define QUAD_FLATTRAJ_HANDLER_HPP

#include <memory>
#include <string>
#include <atomic>

// headers for lcm
#include <lcm/lcm-cpp.hpp>
#include "lcmtypes/librav.hpp"

#include "common/librav_types.hpp"
#include "common/quad_flattraj.hpp"

namespace librav
{

class QuadFlatTrajHandler
{
  public:
	QuadFlatTrajHandler(std::shared_ptr<lcm::LCM> lcm);
	QuadFlatTrajHandler(std::shared_ptr<lcm::LCM> lcm, std::string poly_traj_topic);
	~QuadFlatTrajHandler() = default;

	friend class MotionServer;

	void LcmPolyTrajMsgHandler(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const srcl_lcm_msgs::PolynomialCurve_t *msg);
	UAVTrajectoryPoint GetDesiredTrajectoryPoint(time_t tstamp);

	void ReportProgress(void);

  private:
	std::shared_ptr<lcm::LCM> lcm_;
	std::string poly_traj_topic_;

	std::atomic<bool> traj_available_;
	std::atomic<time_stamp> current_sys_time_;
	std::vector<Position3Dd> waypoints_;
	time_stamp traj_start_time_;
	double remaining_dist_;
	int next_wp_idx_;
	double scaling_factor_;
	int64_t traj_id_;

	QuadFlatTraj flat_traj_;

	double GetRefactoredTime(double ts, double te, double t);
	void UpdateSystemTime(double t) { current_sys_time_ = t; };
	int32_t FindFurthestPointWithinRadius(std::vector<Position3Dd> &path, int32_t current_idx, double radius) const;
};
}

#endif /* QUAD_FLATTRAJ_HANDLER_HPP */
