/* 
 * virtual_controller.cpp
 * 
 * Created on: Dec 09, 2018 04:41
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "cav_motion/cav_virtual_controller.hpp"

namespace librav
{
CAVVirtualController::CAVVirtualController(std::shared_ptr<LCMLink> link) : data_link_(link)
{
        // data_link_->subscribe(CAV_SIM_CHANNELS::SIM_SYNC_TRIGGER_CHANNEL, &TrafficSimManager::HandleLCMMessage_SyncTrigger, this);
}
} // namespace librav
